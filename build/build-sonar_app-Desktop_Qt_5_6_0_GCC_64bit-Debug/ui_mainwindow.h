/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "src/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QAction *actionSerial_port;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QPushButton *connectBtn;
    QTabWidget *tabWidget;
    QWidget *tabControl;
    QGridLayout *gridLayout_9;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_10;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout_2;
    QLabel *label;
    QSpinBox *spinBox;
    QLabel *label_2;
    QSpinBox *spinBox_2;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox;
    QPushButton *updateAngleBtn;
    QFrame *line;
    QLabel *label_4;
    QSpinBox *signalThresholdValueBox;
    QWidget *tabScan;
    QFormLayout *formLayout_3;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_9;
    QRadioButton *rBtn_TOF_scan;
    QRadioButton *rBtn_PAS_scan;
    QPushButton *singleMeasurementBtn;
    QPushButton *scanBtn;
    QGroupBox *groupBox_7;
    QFormLayout *formLayout_4;
    QLabel *label_5;
    QLCDNumber *lcd_left;
    QLabel *label_6;
    QLCDNumber *lcd_right;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_10;
    QCheckBox *cBox_left_sensor;
    QCheckBox *cBox_right_sensor;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_11;
    QCheckBox *cBox_alg1;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QCustomPlot *sonarMap;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QCustomPlot *sonarSignal;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSettings;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(793, 776);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionSerial_port = new QAction(MainWindow);
        actionSerial_port->setObjectName(QStringLiteral("actionSerial_port"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(5);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        connectBtn = new QPushButton(centralWidget);
        connectBtn->setObjectName(QStringLiteral("connectBtn"));

        verticalLayout_3->addWidget(connectBtn);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabControl = new QWidget();
        tabControl->setObjectName(QStringLiteral("tabControl"));
        gridLayout_9 = new QGridLayout(tabControl);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        groupBox_4 = new QGroupBox(tabControl);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_10 = new QGridLayout(groupBox_4);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));

        gridLayout_10->addLayout(verticalLayout_4, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBox_4, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(tabControl);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        formLayout_2 = new QFormLayout(groupBox_3);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        spinBox = new QSpinBox(groupBox_3);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(-90);
        spinBox->setMaximum(90);
        spinBox->setValue(-45);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, spinBox);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        spinBox_2 = new QSpinBox(groupBox_3);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMinimum(-90);
        spinBox_2->setMaximum(90);
        spinBox_2->setValue(45);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, spinBox_2);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);

        doubleSpinBox = new QDoubleSpinBox(groupBox_3);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setDecimals(1);
        doubleSpinBox->setMaximum(5);
        doubleSpinBox->setSingleStep(0.1);
        doubleSpinBox->setValue(1);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, doubleSpinBox);

        updateAngleBtn = new QPushButton(groupBox_3);
        updateAngleBtn->setObjectName(QStringLiteral("updateAngleBtn"));

        formLayout_2->setWidget(3, QFormLayout::SpanningRole, updateAngleBtn);

        line = new QFrame(groupBox_3);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        formLayout_2->setWidget(4, QFormLayout::SpanningRole, line);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_4);

        signalThresholdValueBox = new QSpinBox(groupBox_3);
        signalThresholdValueBox->setObjectName(QStringLiteral("signalThresholdValueBox"));
        signalThresholdValueBox->setMaximum(2400);
        signalThresholdValueBox->setValue(1600);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, signalThresholdValueBox);


        gridLayout_9->addWidget(groupBox_3, 0, 0, 1, 1);

        gridLayout_9->setRowStretch(0, 5);
        tabWidget->addTab(tabControl, QString());
        tabScan = new QWidget();
        tabScan->setObjectName(QStringLiteral("tabScan"));
        formLayout_3 = new QFormLayout(tabScan);
        formLayout_3->setSpacing(6);
        formLayout_3->setContentsMargins(11, 11, 11, 11);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        groupBox_5 = new QGroupBox(tabScan);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        verticalLayout_9 = new QVBoxLayout(groupBox_5);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        rBtn_TOF_scan = new QRadioButton(groupBox_5);
        rBtn_TOF_scan->setObjectName(QStringLiteral("rBtn_TOF_scan"));
        rBtn_TOF_scan->setChecked(true);

        verticalLayout_9->addWidget(rBtn_TOF_scan);

        rBtn_PAS_scan = new QRadioButton(groupBox_5);
        rBtn_PAS_scan->setObjectName(QStringLiteral("rBtn_PAS_scan"));

        verticalLayout_9->addWidget(rBtn_PAS_scan);


        formLayout_3->setWidget(0, QFormLayout::FieldRole, groupBox_5);

        singleMeasurementBtn = new QPushButton(tabScan);
        singleMeasurementBtn->setObjectName(QStringLiteral("singleMeasurementBtn"));
        singleMeasurementBtn->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(singleMeasurementBtn->sizePolicy().hasHeightForWidth());
        singleMeasurementBtn->setSizePolicy(sizePolicy2);

        formLayout_3->setWidget(3, QFormLayout::FieldRole, singleMeasurementBtn);

        scanBtn = new QPushButton(tabScan);
        scanBtn->setObjectName(QStringLiteral("scanBtn"));
        scanBtn->setEnabled(false);
        sizePolicy2.setHeightForWidth(scanBtn->sizePolicy().hasHeightForWidth());
        scanBtn->setSizePolicy(sizePolicy2);

        formLayout_3->setWidget(4, QFormLayout::FieldRole, scanBtn);

        groupBox_7 = new QGroupBox(tabScan);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        formLayout_4 = new QFormLayout(groupBox_7);
        formLayout_4->setSpacing(6);
        formLayout_4->setContentsMargins(11, 11, 11, 11);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        label_5 = new QLabel(groupBox_7);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_5);

        lcd_left = new QLCDNumber(groupBox_7);
        lcd_left->setObjectName(QStringLiteral("lcd_left"));
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        font.setKerning(true);
        font.setStyleStrategy(QFont::PreferDefault);
        lcd_left->setFont(font);
        lcd_left->setFrameShape(QFrame::Box);
        lcd_left->setFrameShadow(QFrame::Plain);
        lcd_left->setMidLineWidth(0);
        lcd_left->setSmallDecimalPoint(false);
        lcd_left->setDigitCount(5);
        lcd_left->setSegmentStyle(QLCDNumber::Flat);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, lcd_left);

        label_6 = new QLabel(groupBox_7);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_6);

        lcd_right = new QLCDNumber(groupBox_7);
        lcd_right->setObjectName(QStringLiteral("lcd_right"));
        lcd_right->setFrameShadow(QFrame::Plain);
        lcd_right->setSegmentStyle(QLCDNumber::Flat);

        formLayout_4->setWidget(1, QFormLayout::FieldRole, lcd_right);


        formLayout_3->setWidget(5, QFormLayout::FieldRole, groupBox_7);

        groupBox_6 = new QGroupBox(tabScan);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        verticalLayout_10 = new QVBoxLayout(groupBox_6);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        cBox_left_sensor = new QCheckBox(groupBox_6);
        cBox_left_sensor->setObjectName(QStringLiteral("cBox_left_sensor"));
        cBox_left_sensor->setChecked(true);

        verticalLayout_10->addWidget(cBox_left_sensor);

        cBox_right_sensor = new QCheckBox(groupBox_6);
        cBox_right_sensor->setObjectName(QStringLiteral("cBox_right_sensor"));

        verticalLayout_10->addWidget(cBox_right_sensor);


        formLayout_3->setWidget(2, QFormLayout::FieldRole, groupBox_6);

        groupBox_8 = new QGroupBox(tabScan);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        verticalLayout_11 = new QVBoxLayout(groupBox_8);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        cBox_alg1 = new QCheckBox(groupBox_8);
        cBox_alg1->setObjectName(QStringLiteral("cBox_alg1"));

        verticalLayout_11->addWidget(cBox_alg1);


        formLayout_3->setWidget(1, QFormLayout::FieldRole, groupBox_8);

        tabWidget->addTab(tabScan, QString());

        verticalLayout_3->addWidget(tabWidget);


        horizontalLayout_4->addLayout(verticalLayout_3);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_8 = new QVBoxLayout(groupBox_2);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        sonarMap = new QCustomPlot(groupBox_2);
        sonarMap->setObjectName(QStringLiteral("sonarMap"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(2);
        sizePolicy3.setVerticalStretch(3);
        sizePolicy3.setHeightForWidth(sonarMap->sizePolicy().hasHeightForWidth());
        sonarMap->setSizePolicy(sizePolicy3);
        sonarMap->setMinimumSize(QSize(20, 20));

        verticalLayout_7->addWidget(sonarMap);


        verticalLayout_8->addLayout(verticalLayout_7);


        horizontalLayout_4->addWidget(groupBox_2);

        horizontalLayout_4->setStretch(0, 2);
        horizontalLayout_4->setStretch(1, 6);

        verticalLayout->addLayout(horizontalLayout_4);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        sonarSignal = new QCustomPlot(groupBox);
        sonarSignal->setObjectName(QStringLiteral("sonarSignal"));
        sonarSignal->setEnabled(true);
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(1);
        sizePolicy4.setHeightForWidth(sonarSignal->sizePolicy().hasHeightForWidth());
        sonarSignal->setSizePolicy(sizePolicy4);

        verticalLayout_5->addWidget(sonarSignal);


        verticalLayout_6->addLayout(verticalLayout_5);


        verticalLayout->addWidget(groupBox);

        verticalLayout->setStretch(0, 8);
        verticalLayout->setStretch(1, 3);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 793, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuSettings->addAction(actionSerial_port);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
#ifndef QT_NO_TOOLTIP
        actionConnect->setToolTip(QApplication::translate("MainWindow", "Connect to the uC", 0));
#endif // QT_NO_TOOLTIP
        actionSerial_port->setText(QApplication::translate("MainWindow", "Serial port", 0));
        connectBtn->setText(QApplication::translate("MainWindow", "Connect", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Single measurement", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Parameters", 0));
        label->setText(QApplication::translate("MainWindow", "Initial angle", 0));
        label_2->setText(QApplication::translate("MainWindow", "Final angle", 0));
        label_3->setText(QApplication::translate("MainWindow", "Step", 0));
        updateAngleBtn->setText(QApplication::translate("MainWindow", "Update", 0));
        label_4->setText(QApplication::translate("MainWindow", "Signal threshold", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabControl), QApplication::translate("MainWindow", "Control", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Scan type", 0));
        rBtn_TOF_scan->setText(QApplication::translate("MainWindow", "TOF only", 0));
        rBtn_PAS_scan->setText(QApplication::translate("MainWindow", "PAS", 0));
        singleMeasurementBtn->setText(QApplication::translate("MainWindow", "Single", 0));
        scanBtn->setText(QApplication::translate("MainWindow", "Continuous", 0));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Measurement", 0));
        label_5->setText(QApplication::translate("MainWindow", "Left", 0));
        label_6->setText(QApplication::translate("MainWindow", "Right", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Active sensor", 0));
        cBox_left_sensor->setText(QApplication::translate("MainWindow", "Left sonar", 0));
        cBox_right_sensor->setText(QApplication::translate("MainWindow", "Right sonar", 0));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Algorithm", 0));
        cBox_alg1->setText(QApplication::translate("MainWindow", "Alg1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabScan), QApplication::translate("MainWindow", "Scan", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Sonar map", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Analog voltage envelope", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
