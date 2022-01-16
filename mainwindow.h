#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>
#include <QSettings>
#include <cstdlib>
#include <QProcess>

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

private:
    Ui::MainWindow *ui;
    QProcess *chipyardProcess;
};
#endif // MAINWINDOW_H
