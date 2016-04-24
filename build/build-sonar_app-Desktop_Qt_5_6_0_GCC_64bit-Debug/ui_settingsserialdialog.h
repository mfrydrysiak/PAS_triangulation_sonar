/********************************************************************************
** Form generated from reading UI file 'settingsserialdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSSERIALDIALOG_H
#define UI_SETTINGSSERIALDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingsSerialDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SettingsSerialDialog)
    {
        if (SettingsSerialDialog->objectName().isEmpty())
            SettingsSerialDialog->setObjectName(QStringLiteral("SettingsSerialDialog"));
        SettingsSerialDialog->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(SettingsSerialDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(SettingsSerialDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(SettingsSerialDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsSerialDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsSerialDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SettingsSerialDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsSerialDialog)
    {
        SettingsSerialDialog->setWindowTitle(QApplication::translate("SettingsSerialDialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingsSerialDialog: public Ui_SettingsSerialDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSSERIALDIALOG_H
