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

private:
    Ui::MainWindow *ui;
    QProcess *bspProcess;
};
#endif // MAINWINDOW_H
