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
    connect(process, &QProcess::readyReadStandardOutput, this, &qtdd::readProcessOutput);
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

    QProcess proc;
    proc.start("lsblk", QStringList() << "-J" << "-o" << "NAME,SIZE,MODEL,TRAN,RM,HOTPLUG,LABEL");
    proc.waitForFinished();

    QByteArray jsonData = proc.readAllStandardOutput();
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

    if (filePath.isEmpty()) return;

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
    Q_UNUSED(index);
    QString scheme = ui->comboBox_part_schem->currentText();

    ui->comboBox_targetsys->clear();

    if (scheme == "GPT") {
        ui->comboBox_targetsys->addItem("UEFI (non-CSM)");
    } else if (scheme == "MBR") {
        ui->comboBox_targetsys->addItem("BIOS (or UEFI-CSM)");
    }

    ui->comboBox_targetsys->setEnabled(false);
}

void qtdd::on_comboBox_imageopt_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    QString mode = ui->comboBox_imageopt->currentText();
    bool isDdMode = mode.contains("dd", Qt::CaseInsensitive);

    ui->comboBox_fs->setEnabled(!isDdMode);
    ui->checkBox_quickformat->setEnabled(!isDdMode);
    ui->vol_label->setEnabled(!isDdMode);
    ui->comboBox_part_schem->setEnabled(!isDdMode);

    if (!isDdMode) {
        on_comboBox_part_schem_currentIndexChanged(ui->comboBox_part_schem->currentIndex());
    }
}

void qtdd::on_btn_start_clicked()
{
    currentImagePath = ui->comboBox_bootsel->currentData().toString();
    currentDevicePath = ui->comboBox_device->currentData().toString();
    QString mode = ui->comboBox_imageopt->currentText();

    if (currentImagePath.isEmpty() || currentDevicePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a valid image file and target device.");
        return;
    }

    if (!QFile::exists(currentImagePath) || !currentDevicePath.startsWith("/dev/")) {
        QMessageBox::critical(this, "Error", "Selected file or target device path is invalid!");
        return;
    }

    if (QMessageBox::warning(this, "Warning",
                             QString("All data on %1 will be destroyed!\nAre you sure you want to continue?").arg(currentDevicePath),
                             QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    ui->btn_start->setEnabled(false);
    ui->btn_exit->setEnabled(false);
    ui->btn_cancel->setEnabled(true);
    ui->comboBox_device->setEnabled(false);
    ui->comboBox_bootsel->setEnabled(false);
    ui->btn_refreshdev->setEnabled(false);
    ui->checkBox_alldev->setEnabled(false);
    ui->progressBar->setValue(0);

    if (mode.contains("dd", Qt::CaseInsensitive)) {
        currentIsoStep = IsoStep::None;
        QStringList arguments;
        arguments << "dd"
                  << QString("if=%1").arg(currentImagePath)
                  << QString("of=%1").arg(currentDevicePath)
                  << "bs=4M"
                  << "status=progress"
                  << "oflag=sync";

        QFileInfo imageInfo(currentImagePath);
        totalBytes = imageInfo.size();

        process->start("pkexec", arguments);
    } else {
        startIsoPipeline();
    }
}

void qtdd::startIsoPipeline()
{
    if (currentDevicePath.contains("loop") || currentDevicePath.contains("nvme")) {
        targetPartitionPath = currentDevicePath + "p1";
    } else {
        targetPartitionPath = currentDevicePath + "1";
    }

    currentIsoStep = IsoStep::Unmount;
    executeNextIsoStep();
}

void qtdd::executeNextIsoStep()
{
    QStringList args;

    switch (currentIsoStep) {
    case IsoStep::Unmount:
        args << "bash" << "-c" << QString("umount %1* || true").arg(currentDevicePath);
        process->start("pkexec", args);
        break;

    case IsoStep::Partition: {
        QString scheme = ui->comboBox_part_schem->currentText();
        QString labelType = (scheme == "GPT") ? "gpt" : "dos";

        args << "bash" << "-c"
             << QString("echo 'label: %1\ntype=7' | sfdisk --force --wipe always %2").arg(labelType, currentDevicePath);
        process->start("pkexec", args);
        break;
    }

    case IsoStep::Format: {
        QString fs = ui->comboBox_fs->currentText();
        QString label = ui->vol_label->text().trimmed();
        if (label.isEmpty()) label = "BOOT_USB";

        if (fs == "FAT32") {
            args << "mkfs.vfat" << "-F" << "32" << "-n" << label << targetPartitionPath;
        } else {
            args << "mkfs.ntfs" << "-f" << "-L" << label << targetPartitionPath;
        }
        process->start("pkexec", args);
        break;
    }

    case IsoStep::MountISO:
        args << "bash" << "-c"
             << QString("mkdir -p /tmp/qtdd_iso /tmp/qtdd_target && mount -o loop '%1' /tmp/qtdd_iso").arg(currentImagePath);
        process->start("pkexec", args);
        break;

    case IsoStep::MountTarget:
        args << "mount" << targetPartitionPath << "/tmp/qtdd_target";
        process->start("pkexec", args);
        break;

    case IsoStep::CopyFiles:
        args << "rsync" << "-a" << "--info=progress2" << "/tmp/qtdd_iso/" << "/tmp/qtdd_target/";
        process->start("pkexec", args);
        break;

    case IsoStep::Cleanup:
        args << "bash" << "-c" << "umount /tmp/qtdd_iso /tmp/qtdd_target && rmdir /tmp/qtdd_iso /tmp/qtdd_target && sync";
        process->start("pkexec", args);
        break;

    default:
        break;
    }
}

void qtdd::readProcessOutput()
{
    QByteArray data = process->readAllStandardError();
    if (data.isEmpty()) {
        data = process->readAllStandardOutput();
    }
    QString output = QString::fromUtf8(data);

    if (currentIsoStep == IsoStep::CopyFiles) {
        static QRegularExpression re(R"((\d+)%)");
        QRegularExpressionMatch match = re.match(output);
        if (match.hasMatch()) {
            int progress = match.captured(1).toInt();
            ui->progressBar->setValue(progress);
        }
    } else if (currentIsoStep == IsoStep::None) {
        QStringList lines = output.split(QRegularExpression("[\r\n]"), Qt::SkipEmptyParts);
        for (const QString &line : lines) {
            static QRegularExpression re("^(\\d+)\\s+bytes");
            QRegularExpressionMatch match = re.match(line.trimmed());
            if (match.hasMatch() && totalBytes > 0) {
                qint64 bytesCopied = match.captured(1).toLongLong();
                int progress = static_cast<int>((bytesCopied * 100) / totalBytes);
                ui->progressBar->setValue(qMin(progress, 100));
            }
        }
    }
}

void qtdd::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitCode != 0 || exitStatus != QProcess::NormalExit) {
        if (currentIsoStep != IsoStep::Unmount) {
            ui->btn_start->setEnabled(true);
            ui->btn_exit->setEnabled(true);
            ui->btn_cancel->setEnabled(false);
            ui->comboBox_device->setEnabled(true);
            ui->comboBox_bootsel->setEnabled(true);
            ui->btn_refreshdev->setEnabled(true);
            ui->checkBox_alldev->setEnabled(true);

            QMessageBox::warning(this, "Operation Failed", QString("Failed at step %1").arg(static_cast<int>(currentIsoStep)));
            currentIsoStep = IsoStep::None;
            return;
        }
    }

    if (currentIsoStep != IsoStep::None) {
        switch (currentIsoStep) {
        case IsoStep::Unmount: currentIsoStep = IsoStep::Partition; break;
        case IsoStep::Partition: currentIsoStep = IsoStep::Format; break;
        case IsoStep::Format: currentIsoStep = IsoStep::MountISO; break;
        case IsoStep::MountISO: currentIsoStep = IsoStep::MountTarget; break;
        case IsoStep::MountTarget: currentIsoStep = IsoStep::CopyFiles; break;
        case IsoStep::CopyFiles: currentIsoStep = IsoStep::Cleanup; break;
        case IsoStep::Cleanup: currentIsoStep = IsoStep::None; break;
        default: break;
        }

        if (currentIsoStep != IsoStep::None) {
            executeNextIsoStep();
            return;
        }
    }

    ui->btn_start->setEnabled(true);
    ui->btn_exit->setEnabled(true);
    ui->btn_cancel->setEnabled(false);
    ui->comboBox_device->setEnabled(true);
    ui->comboBox_bootsel->setEnabled(true);
    ui->btn_refreshdev->setEnabled(true);
    ui->checkBox_alldev->setEnabled(true);

    ui->progressBar->setValue(100);
    QMessageBox::information(this, "Success", "Image successfully written to device!");
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