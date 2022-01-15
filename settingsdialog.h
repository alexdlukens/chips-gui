#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>
#include <map>
#include <iostream>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QSettings &settingsMap, QWidget *parent = nullptr);
    ~SettingsDialog();

public slots:
    virtual void onChipFpgaButtonClicked();
    virtual void onFreedomSdkButtonClicked();
    virtual void onExitButtonClicked();
    virtual void onRISCVPathButtonClicked();

private:
    Ui::SettingsDialog *ui;
    QSettings *mainSettings;
    std::map<QString, QString> editedSettings;

};

#endif // SETTINGSDIALOG_H
