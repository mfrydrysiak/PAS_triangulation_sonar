#ifndef SETTINGSSERIALDIALOG_H
#define SETTINGSSERIALDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsSerialDialog;
}

class SettingsSerialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsSerialDialog(QWidget *parent = 0);
    ~SettingsSerialDialog();

private:
    Ui::SettingsSerialDialog *ui;
};

#endif // SETTINGSSERIALDIALOG_H
