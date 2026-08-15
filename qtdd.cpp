#include "qtdd.h"
#include "./ui_qtdd.h"
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRegularExpression>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>

qtdd::qtdd(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::qtdd)
{
    ui->setupUi(this);

    process = new QProcess(this);
    connect(process, &QProcess::readyReadStandardError, this, &qtdd::readProcessOutput);
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &qtdd::processFinished);

    connect(ui->actionGitHub, &QAction::triggered, []() {
        QDesktopServices::openUrl(QUrl("https://github.com/itsflameee/qtdd"));
    });

    connect(ui->actionExit, &QAction::triggered, this, &qtdd::on_btn_exit_clicked);

    refreshDevices();
}

qtdd::~qtdd()
{
    delete ui;
}

void qtdd::on_btn_exit_clicked()
{
    close();
}

void qtdd::on_btn_refreshdev_clicked()
{
    refreshDevices();
}

void qtdd::on_checkBox_alldev_toggled(bool checked)
{
    if (checked) {
        ui->checkBox_alldev->setText("Show all devices (unlimited size, any drive type)");
    } else {
        ui->checkBox_alldev->setText("Show all devices (<256GB, USB flash drives only)");
    }
    refreshDevices();
}

void qtdd::refreshDevices()
{
    ui->comboBox_device->clear();

    QProcess process;
    process.start("lsblk", QStringList() << "-J" << "-o" << "NAME,SIZE,MODEL,TRAN,RM,HOTPLUG,LABEL");
    process.waitForFinished();

    QByteArray jsonData = process.readAllStandardOutput();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonObject root = doc.object();
    QJsonArray devices = root["blockdevices"].toArray();

    bool showAll = ui->checkBox_alldev->isChecked();

    for (const auto &devRef : devices) {
        QJsonObject dev = devRef.toObject();

        QString name = dev["name"].toString();
        QString sizeStr = dev["size"].toString();
        QString tran = dev["tran"].toString();
        bool rm = dev["rm"].toBool();

        if (!showAll) {
            if (tran != "usb" && !rm) continue;

            if (sizeStr.contains('T')) continue;
            if (sizeStr.contains('G')) {
                QString numPart = sizeStr;
                numPart.replace(',', '.').remove(QRegularExpression("[^\\d.]"));
                if (numPart.toDouble() > 256.0) continue;
            }
        }

        QStringList labels;
        if (dev.contains("label") && !dev["label"].toString().isEmpty()) {
            labels.append(dev["label"].toString());
        }

        if (dev.contains("children")) {
            QJsonArray children = dev["children"].toArray();
            for (const auto &childRef : children) {
                QJsonObject child = childRef.toObject();
                QString childLabel = child["label"].toString();
                if (!childLabel.isEmpty()) {
                    labels.append(childLabel);
                }
            }
        }

        QString labelsFormatted = labels.isEmpty() ? "No label" : labels.join(", ");
        QString displayText = QString("[%1] %2 (%3)").arg(sizeStr, labelsFormatted, name);

        ui->comboBox_device->addItem(displayText, QString("/dev/" + name));
    }

    if (ui->comboBox_device->count() == 0) {
        ui->comboBox_device->addItem("No suitable devices found");
    }
}

void qtdd::on_btn_select_bootsel_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Select Boot Image"),
        QDir::homePath(),
        tr("Disk Images (*.iso *.img);;All Files (*)")
        );

    if (filePath.isEmpty()) {
        return;
    }

    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();
    QString dirPath = fileInfo.absolutePath();

    QString ext = fileInfo.suffix().toUpper();
    QString tag = (ext == "IMG") ? "[IMG]" : "[ISO]";

    QString displayDir = dirPath;
    if (displayDir.length() > 35) {
        displayDir = "..." + displayDir.right(32);
    }

    QString displayText = QString("%1 %2 (%3)").arg(tag, fileName, displayDir);

    int existingIndex = ui->comboBox_bootsel->findData(filePath);
    if (existingIndex != -1) {
        ui->comboBox_bootsel->setCurrentIndex(existingIndex);
        return;
    }

    ui->comboBox_bootsel->insertItem(0, displayText, filePath);
    ui->comboBox_bootsel->setCurrentIndex(0);
}

void qtdd::on_comboBox_part_schem_currentIndexChanged(int index)
{
    QString scheme = ui->comboBox_part_schem->currentText();

    ui->comboBox_targetsys->clear();

    if (scheme == "GPT") {
        ui->comboBox_targetsys->addItem("UEFI (non-CSM)");
    }
    else if (scheme == "MBR") {
        ui->comboBox_targetsys->addItem("BIOS (or UEFI-CSM)");
    }

    ui->comboBox_targetsys->setEnabled(false);
}

void qtdd::on_comboBox_imageopt_currentIndexChanged(int index)
{
    QString mode = ui->comboBox_imageopt->currentText();

    bool isDdMode = mode.contains("dd", Qt::CaseInsensitive);

    ui->comboBox_fs->setEnabled(!isDdMode);
    ui->checkBox_quickformat->setEnabled(!isDdMode);
    ui->vol_label->setEnabled(!isDdMode);
    ui->comboBox_part_schem->setEnabled(!isDdMode);
}

void qtdd::on_btn_start_clicked()
{
    QString imagePath = ui->comboBox_bootsel->currentData().toString();
    QString devicePath = ui->comboBox_device->currentData().toString();
    QString mode = ui->comboBox_imageopt->currentText();

    if (imagePath.isEmpty() || devicePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a valid image file and target device.");
        return;
    }

    if (!QFile::exists(imagePath) || !devicePath.startsWith("/dev/")) {
        QMessageBox::critical(this, "Error", "Selected file or target device path is invalid!");
        return;
    }

    if (QMessageBox::warning(this, "Warning",
                             QString("All data on %1 will be destroyed!\nAre you sure you want to continue?").arg(devicePath),
                             QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    if (mode.contains("dd", Qt::CaseInsensitive)) {
        QStringList arguments;
        arguments << "dd"
                  << QString("if=%1").arg(imagePath)
                  << QString("of=%1").arg(devicePath)
                  << "bs=4M"
                  << "status=progress"
                  << "oflag=sync";

        ui->btn_start->setEnabled(false);
        ui->btn_exit->setEnabled(false);
        ui->btn_cancel->setEnabled(true);
        ui->comboBox_device->setEnabled(false);
        ui->comboBox_bootsel->setEnabled(false);
        ui->btn_refreshdev->setEnabled(false);
        ui->checkBox_alldev->setEnabled(false);

        QFileInfo imageInfo(imagePath);
        totalBytes = imageInfo.size();

        ui->progressBar->setValue(0);

        process->start("pkexec", arguments);

    } else {
        QMessageBox::information(this, "ISO Mode", "ISO extraction mode is coming soon!");
        return;
    }
}

void qtdd::readProcessOutput()
{
    QByteArray data = process->readAllStandardError();
    QString output = QString::fromUtf8(data);

    // dd выдает информацию с возвратом каретки (\r), разбиваем по строкам
    QStringList lines = output.split(QRegularExpression("[\r\n]"), Qt::SkipEmptyParts);

    for (const QString &line : lines) {
        // Ищем количество байт в начале строки (например, "104857600 bytes...")
        static QRegularExpression re("^(\\d+)\\s+bytes");
        QRegularExpressionMatch match = re.match(line.trimmed());

        if (match.hasMatch() && totalBytes > 0) {
            qint64 bytesCopied = match.captured(1).toLongLong();
            int progress = static_cast<int>((bytesCopied * 100) / totalBytes);

            ui->progressBar->setValue(qMin(progress, 100));
        }
    }
}

void qtdd::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    ui->btn_start->setEnabled(true);
    ui->btn_exit->setEnabled(true);
    ui->btn_cancel->setEnabled(false);
    ui->comboBox_device->setEnabled(true);
    ui->comboBox_bootsel->setEnabled(true);
    ui->btn_refreshdev->setEnabled(true);
    ui->checkBox_alldev->setEnabled(true);

    if (exitCode == 0 && exitStatus == QProcess::NormalExit) {
        ui->progressBar->setValue(100);
        QMessageBox::information(this, "Success", "Image successfully written to device!");
    } else {
        QMessageBox::warning(this, "Operation Canceled / Failed", "Writing process was stopped or failed.");
    }
}

void qtdd::on_btn_cancel_clicked()
{
    if (process && process->state() == QProcess::Running) {
        if (QMessageBox::question(this, "Cancel Operation",
                                  "Are you sure you want to cancel the writing process?",
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {

            process->terminate();

            if (!process->waitForFinished(2000)) {
                process->kill();
            }
        }
    } else {
        close();
    }
}