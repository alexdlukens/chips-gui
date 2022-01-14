#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include "systemcmdcaller.h"
#include "settingsdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->MakeMCS, SIGNAL(clicked(bool)), this, SLOT(onMCSButtonPressed()));
    connect(ui->MakeBSP, SIGNAL(clicked(bool)), this, SLOT(onBSPButtonPressed()));
    connect(ui->actionSettings, SIGNAL(triggered(bool)), this, SLOT(onSettingsButtonPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//when settings button pressed (tools->settings), open settings dialog
void MainWindow::onSettingsButtonPressed()
{
    SettingsDialog *settings = new SettingsDialog(this->settingsMap);
    settings->setModal(true);
    settings->setWindowTitle(QString("Settings"));
    settings->exec();
    std::cout << "here" << std::endl;
    for (auto i : settingsMap.allKeys()){
        std::cout <<"settings entry: " + i.toStdString() + ", " + (settingsMap.value(i)).toString().toStdString() << std::endl;
    }

}

//invoke make MCS command with specified arguments
void MainWindow::onMCSButtonPressed()
{
    std::string args = ui->commandDir->text().toStdString();
    std::string cmd = "make ";
    std::string dir = settingsMap.value("chip_fpga").toString().toStdString();

    //exit if no directory set
    if(dir.empty()) {
        std::cout << "chipyard/fpga dir not set in settings" << std::endl;
        return;
    }
    auto system = std::make_unique<SystemCmdCaller>();

    //combine all segments to make single string of commands (executed by /bin/sh)
    std::string wholeCommand = "cd " + dir + " && " + cmd + args + "mcs";
    system->RunCommand(wholeCommand.c_str());

    //output command text to browser window
    ui->textBrowser->setText(tr(system->ReturnOutput().c_str()));
}

//invoke make BSP command with specified arguments;
void MainWindow::onBSPButtonPressed()
{
    std::string args = ui->commandDir->text().toStdString();
    std::string cmd = "make ";
    std::string dir = settingsMap.value("chip_fpga").toString().toStdString();

    //exit if no directory set
    if(dir.empty()) {
        std::cout << "chipyard/fpga dir not set in settings" << std::endl;
        return;
    }
    auto system = std::make_unique<SystemCmdCaller>();

    //combine all segments to make single string of commands (executed by /bin/sh)
    std::string wholeCommand = "cd " + dir + " && " + cmd + args + "bsp";
    system->RunCommand(wholeCommand.c_str());

    //output command text to browser window
    ui->textBrowser->setText(tr(system->ReturnOutput().c_str()));
}
