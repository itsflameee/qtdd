#ifndef QTDD_H
#define QTDD_H

#include <QMainWindow>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui {
class qtdd;
}
QT_END_NAMESPACE

class qtdd : public QMainWindow
{
    Q_OBJECT

public:
    explicit qtdd(QWidget *parent = nullptr);
    ~qtdd() override;

private slots:
    void on_btn_exit_clicked();
    void on_btn_refreshdev_clicked();
    void on_checkBox_alldev_toggled(bool checked);
    void refreshDevices();
    void on_btn_select_bootsel_clicked();
    void on_comboBox_part_schem_currentIndexChanged(int index);
    void on_comboBox_imageopt_currentIndexChanged(int index);

    void on_btn_start_clicked();
    void on_btn_cancel_clicked();
    void readProcessOutput();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    // Перечисление шагов для ISO Mode
    enum class IsoStep {
        None,
        Unmount,
        Partition,
        Format,
        MountISO,
        MountTarget,
        CopyFiles,
        Cleanup
    };

    void startIsoPipeline();
    void executeNextIsoStep();

    Ui::qtdd *ui;
    QProcess *process;
    qint64 totalBytes = 0;

    IsoStep currentIsoStep = IsoStep::None;
    QString currentImagePath;
    QString currentDevicePath;
    QString targetPartitionPath;
};

#endif // QTDD_H