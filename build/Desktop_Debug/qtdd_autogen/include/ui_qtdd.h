/********************************************************************************
** Form generated from reading UI file 'qtdd.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTDD_H
#define UI_QTDD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtdd
{
public:
    QAction *actionGitHub;
    QAction *actionExit;
    QAction *actionEnglish;
    QAction *action_3;
    QWidget *centralwidget;
    QComboBox *comboBox_device;
    QComboBox *comboBox_bootsel;
    QPushButton *btn_select_bootsel;
    QComboBox *comboBox_part_schem;
    QComboBox *comboBox_targetsys;
    QComboBox *comboBox_imageopt;
    QLabel *label_device;
    QLabel *label_bootsel;
    QLabel *label_imageopt;
    QLabel *label_part_schem;
    QLabel *label_targetsys;
    QLabel *label_category_formatopt;
    QLabel *label_category_driveprop;
    QLabel *label_vol_label;
    QLineEdit *vol_label;
    QComboBox *comboBox_fs;
    QLabel *label_fs;
    QLabel *label_status;
    QProgressBar *progressBar;
    QFrame *frame;
    QFrame *frame_2;
    QFrame *frame_3;
    QPushButton *btn_refreshdev;
    QCheckBox *checkBox_quickformat;
    QPushButton *btn_start;
    QPushButton *btn_cancel;
    QPushButton *btn_exit;
    QCheckBox *checkBox_alldev;
    QMenuBar *menubar;
    QMenu *menuqtdd;

    void setupUi(QMainWindow *qtdd)
    {
        if (qtdd->objectName().isEmpty())
            qtdd->setObjectName("qtdd");
        qtdd->setWindowModality(Qt::WindowModality::NonModal);
        qtdd->resize(460, 583);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qtdd->sizePolicy().hasHeightForWidth());
        qtdd->setSizePolicy(sizePolicy);
        qtdd->setMinimumSize(QSize(460, 583));
        qtdd->setMaximumSize(QSize(460, 583));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::MediaFlash));
        qtdd->setWindowIcon(icon);
        actionGitHub = new QAction(qtdd);
        actionGitHub->setObjectName("actionGitHub");
        actionExit = new QAction(qtdd);
        actionExit->setObjectName("actionExit");
        actionEnglish = new QAction(qtdd);
        actionEnglish->setObjectName("actionEnglish");
        action_3 = new QAction(qtdd);
        action_3->setObjectName("action_3");
        centralwidget = new QWidget(qtdd);
        centralwidget->setObjectName("centralwidget");
        comboBox_device = new QComboBox(centralwidget);
        comboBox_device->setObjectName("comboBox_device");
        comboBox_device->setGeometry(QRect(10, 70, 401, 25));
        comboBox_bootsel = new QComboBox(centralwidget);
        comboBox_bootsel->setObjectName("comboBox_bootsel");
        comboBox_bootsel->setGeometry(QRect(10, 150, 341, 25));
        btn_select_bootsel = new QPushButton(centralwidget);
        btn_select_bootsel->setObjectName("btn_select_bootsel");
        btn_select_bootsel->setGeometry(QRect(360, 150, 91, 25));
        comboBox_part_schem = new QComboBox(centralwidget);
        comboBox_part_schem->addItem(QString());
        comboBox_part_schem->addItem(QString());
        comboBox_part_schem->setObjectName("comboBox_part_schem");
        comboBox_part_schem->setEnabled(false);
        comboBox_part_schem->setGeometry(QRect(10, 250, 211, 25));
        comboBox_targetsys = new QComboBox(centralwidget);
        comboBox_targetsys->addItem(QString());
        comboBox_targetsys->addItem(QString());
        comboBox_targetsys->setObjectName("comboBox_targetsys");
        comboBox_targetsys->setEnabled(false);
        comboBox_targetsys->setGeometry(QRect(240, 250, 211, 25));
        comboBox_targetsys->setEditable(false);
        comboBox_imageopt = new QComboBox(centralwidget);
        comboBox_imageopt->addItem(QString());
        comboBox_imageopt->addItem(QString());
        comboBox_imageopt->setObjectName("comboBox_imageopt");
        comboBox_imageopt->setGeometry(QRect(10, 200, 441, 25));
        label_device = new QLabel(centralwidget);
        label_device->setObjectName("label_device");
        label_device->setGeometry(QRect(10, 50, 181, 17));
        label_bootsel = new QLabel(centralwidget);
        label_bootsel->setObjectName("label_bootsel");
        label_bootsel->setGeometry(QRect(10, 130, 181, 17));
        label_imageopt = new QLabel(centralwidget);
        label_imageopt->setObjectName("label_imageopt");
        label_imageopt->setGeometry(QRect(10, 180, 181, 17));
        label_part_schem = new QLabel(centralwidget);
        label_part_schem->setObjectName("label_part_schem");
        label_part_schem->setGeometry(QRect(10, 230, 181, 17));
        label_targetsys = new QLabel(centralwidget);
        label_targetsys->setObjectName("label_targetsys");
        label_targetsys->setGeometry(QRect(240, 230, 181, 17));
        label_category_formatopt = new QLabel(centralwidget);
        label_category_formatopt->setObjectName("label_category_formatopt");
        label_category_formatopt->setGeometry(QRect(15, 300, 181, 17));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label_category_formatopt->setFont(font);
        label_category_driveprop = new QLabel(centralwidget);
        label_category_driveprop->setObjectName("label_category_driveprop");
        label_category_driveprop->setGeometry(QRect(15, 20, 181, 17));
        label_category_driveprop->setFont(font);
        label_vol_label = new QLabel(centralwidget);
        label_vol_label->setObjectName("label_vol_label");
        label_vol_label->setGeometry(QRect(10, 330, 181, 17));
        vol_label = new QLineEdit(centralwidget);
        vol_label->setObjectName("vol_label");
        vol_label->setEnabled(false);
        vol_label->setGeometry(QRect(10, 350, 441, 24));
        comboBox_fs = new QComboBox(centralwidget);
        comboBox_fs->addItem(QString());
        comboBox_fs->addItem(QString());
        comboBox_fs->setObjectName("comboBox_fs");
        comboBox_fs->setEnabled(false);
        comboBox_fs->setGeometry(QRect(10, 400, 211, 25));
        label_fs = new QLabel(centralwidget);
        label_fs->setObjectName("label_fs");
        label_fs->setGeometry(QRect(10, 380, 181, 17));
        label_status = new QLabel(centralwidget);
        label_status->setObjectName("label_status");
        label_status->setGeometry(QRect(15, 450, 181, 17));
        label_status->setFont(font);
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(10, 480, 441, 23));
        progressBar->setValue(0);
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(180, 20, 271, 20));
        frame->setFrameShape(QFrame::Shape::HLine);
        frame->setFrameShadow(QFrame::Shadow::Sunken);
        frame->setLineWidth(2);
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(160, 300, 291, 20));
        frame_2->setFrameShape(QFrame::Shape::HLine);
        frame_2->setFrameShadow(QFrame::Shadow::Sunken);
        frame_2->setLineWidth(2);
        frame_3 = new QFrame(centralwidget);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(90, 450, 361, 20));
        frame_3->setFrameShape(QFrame::Shape::HLine);
        frame_3->setFrameShadow(QFrame::Shadow::Sunken);
        frame_3->setLineWidth(2);
        btn_refreshdev = new QPushButton(centralwidget);
        btn_refreshdev->setObjectName("btn_refreshdev");
        btn_refreshdev->setGeometry(QRect(420, 70, 28, 25));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::ViewRefresh));
        btn_refreshdev->setIcon(icon1);
        checkBox_quickformat = new QCheckBox(centralwidget);
        checkBox_quickformat->setObjectName("checkBox_quickformat");
        checkBox_quickformat->setEnabled(false);
        checkBox_quickformat->setGeometry(QRect(240, 400, 211, 21));
        btn_start = new QPushButton(centralwidget);
        btn_start->setObjectName("btn_start");
        btn_start->setGeometry(QRect(160, 510, 111, 31));
        QFont font1;
        font1.setPointSize(15);
        btn_start->setFont(font1);
        btn_start->setIcon(icon);
        btn_cancel = new QPushButton(centralwidget);
        btn_cancel->setObjectName("btn_cancel");
        btn_cancel->setEnabled(false);
        btn_cancel->setGeometry(QRect(280, 510, 81, 31));
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::ProcessStop));
        btn_cancel->setIcon(icon2);
        btn_exit = new QPushButton(centralwidget);
        btn_exit->setObjectName("btn_exit");
        btn_exit->setGeometry(QRect(370, 510, 81, 31));
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::WindowClose));
        btn_exit->setIcon(icon3);
        checkBox_alldev = new QCheckBox(centralwidget);
        checkBox_alldev->setObjectName("checkBox_alldev");
        checkBox_alldev->setGeometry(QRect(10, 100, 441, 21));
        qtdd->setCentralWidget(centralwidget);
        menubar = new QMenuBar(qtdd);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 460, 21));
        menuqtdd = new QMenu(menubar);
        menuqtdd->setObjectName("menuqtdd");
        qtdd->setMenuBar(menubar);

        menubar->addAction(menuqtdd->menuAction());
        menuqtdd->addAction(actionGitHub);
        menuqtdd->addSeparator();
        menuqtdd->addAction(actionExit);

        retranslateUi(qtdd);

        QMetaObject::connectSlotsByName(qtdd);
    } // setupUi

    void retranslateUi(QMainWindow *qtdd)
    {
        qtdd->setWindowTitle(QCoreApplication::translate("qtdd", "qtdd", nullptr));
        actionGitHub->setText(QCoreApplication::translate("qtdd", "GitHub", nullptr));
        actionExit->setText(QCoreApplication::translate("qtdd", "Exit", nullptr));
        actionEnglish->setText(QCoreApplication::translate("qtdd", "English", nullptr));
        action_3->setText(QCoreApplication::translate("qtdd", "\320\240\321\203\321\201\321\201\320\272\320\270\320\271", nullptr));
        comboBox_device->setPlaceholderText(QCoreApplication::translate("qtdd", "No device selected", nullptr));
        comboBox_bootsel->setPlaceholderText(QCoreApplication::translate("qtdd", "No boot image selected", nullptr));
        btn_select_bootsel->setText(QCoreApplication::translate("qtdd", "Select Image", nullptr));
        comboBox_part_schem->setItemText(0, QCoreApplication::translate("qtdd", "GPT", nullptr));
        comboBox_part_schem->setItemText(1, QCoreApplication::translate("qtdd", "MBR", nullptr));

        comboBox_targetsys->setItemText(0, QCoreApplication::translate("qtdd", "UEFI (non-CSM)", nullptr));
        comboBox_targetsys->setItemText(1, QCoreApplication::translate("qtdd", "BIOS (or UEFI-CSM)", nullptr));

        comboBox_imageopt->setItemText(0, QCoreApplication::translate("qtdd", "dd Image", nullptr));
        comboBox_imageopt->setItemText(1, QCoreApplication::translate("qtdd", "ISO Mode", nullptr));

        comboBox_imageopt->setPlaceholderText(QCoreApplication::translate("qtdd", "No option selected", nullptr));
        label_device->setText(QCoreApplication::translate("qtdd", "Device", nullptr));
        label_bootsel->setText(QCoreApplication::translate("qtdd", "Boot selection", nullptr));
        label_imageopt->setText(QCoreApplication::translate("qtdd", "Image option", nullptr));
        label_part_schem->setText(QCoreApplication::translate("qtdd", "Partition scheme", nullptr));
        label_targetsys->setText(QCoreApplication::translate("qtdd", "Target system", nullptr));
        label_category_formatopt->setText(QCoreApplication::translate("qtdd", "Format options", nullptr));
        label_category_driveprop->setText(QCoreApplication::translate("qtdd", "Drive Properties", nullptr));
        label_vol_label->setText(QCoreApplication::translate("qtdd", "Volume label", nullptr));
        comboBox_fs->setItemText(0, QCoreApplication::translate("qtdd", "FAT32", nullptr));
        comboBox_fs->setItemText(1, QCoreApplication::translate("qtdd", "NTFS", nullptr));

        label_fs->setText(QCoreApplication::translate("qtdd", "File system", nullptr));
        label_status->setText(QCoreApplication::translate("qtdd", "Status", nullptr));
        btn_refreshdev->setText(QString());
        checkBox_quickformat->setText(QCoreApplication::translate("qtdd", "Quick format", nullptr));
        btn_start->setText(QCoreApplication::translate("qtdd", "Start", nullptr));
        btn_cancel->setText(QCoreApplication::translate("qtdd", "Cancel", nullptr));
        btn_exit->setText(QCoreApplication::translate("qtdd", "Exit", nullptr));
        checkBox_alldev->setText(QCoreApplication::translate("qtdd", "Show all devices (<256GB, USB flash drives only)", nullptr));
        menuqtdd->setTitle(QCoreApplication::translate("qtdd", "qtdd", nullptr));
    } // retranslateUi

};

namespace Ui {
    class qtdd: public Ui_qtdd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTDD_H
