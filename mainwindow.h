#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>
#include <QSettings>
#include <cstdlib>
#include <QProcess>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "systemcmdcaller.h"
#include "settingsdialog.h"
#include "serialconsole.h"
#include <QAbstractItemView>
#include <QTimer>
#include <yaml-cpp/yaml.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSettings settingsMap;
public slots:
    void onSettingsButtonPressed();
    void onMCSButtonPressed();
    void onBSPButtonPressed();
    void readyReadStandardOutputBSP();
    void readyReadStandardErrorBSP();
    void setChipyardButtonsEnabled(QProcess::ProcessState newState);


private slots:
    void on_AbortOperation_clicked();
    void updateTTYPortList();

private:
    Ui::MainWindow *ui;
    QProcess *chipyardProcess;
    SerialConsole *console;
};
#endif // MAINWINDOW_H
