#include "settingsserialdialog.h"
#include "ui_settingsserialdialog.h"

SettingsSerialDialog::SettingsSerialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsSerialDialog)
{
    ui->setupUi(this);
}

SettingsSerialDialog::~SettingsSerialDialog()
{
    delete ui;
}
