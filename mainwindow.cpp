#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "systemcmdcaller.h"
#include "settingsdialog.h"
#include <rapidxml/rapidxml.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->MakeMCS, SIGNAL(clicked(bool)), this, SLOT(onMCSButtonPressed()));
    connect(ui->MakeBSP, SIGNAL(clicked(bool)), this, SLOT(onBSPButtonPressed()));
    connect(ui->actionSettings, SIGNAL(triggered(bool)), this, SLOT(onSettingsButtonPressed()));

    this->bspProcess = new QProcess(this);
    connect(bspProcess, SIGNAL(readyReadStandardOutput()),this, SLOT(readyReadStandardOutputBSP()));
    connect(bspProcess, SIGNAL(readyReadStandardError()),this, SLOT(readyReadStandardErrorBSP()));
    connect(bspProcess, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(setChipyardButtonsEnabled(QProcess::ProcessState)));

//    QFile svdFile;
//    svdFile.setFileName("design.svd");
//    svdFile.open(QFile::ReadOnly);
//    QString fileContents = svdFile.readAll();
//    rapidxml::xml_document<> doc;
//    char* fileString = new char[fileContents.size() + 1];
//    strcpy(fileString, fileContents.toStdString().c_str());

//    doc.parse<0>(fileString);

//    std::cout << "First node name = " << doc.first_node()->first_node()->name() << " and value = " << doc.first_node()->first_node()->value() << std::endl;


//    delete [] fileString;
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
    std::string dir = settingsMap.value("chip_fpga").toString().toStdString();

    //exit if no directory set
    if(dir.empty()) {
        std::cout << "chipyard/fpga dir not set in settings" << std::endl;
        return;
    }
    QStringList env = {ui->commandDir->text(), "RISCV=" + settingsMap.value("RISCV").toString()};
    bspProcess->setEnvironment(env);


    QString command = QString::fromStdString("make");

    //in this case our only argument is to specify that we want to build "bsp"
    QStringList arguments;
    arguments.append("bsp");

    this->bspProcess->setWorkingDirectory(settingsMap.value("chip_fpga").toString());
    std::cout << "before starting bspProcess" << std::endl;
    this->bspProcess->start(command, arguments);
    std::cout << "started bspProcess" << std::endl;


//    //output command text to browser window
//    ui->textBrowser->setText(tr(system->ReturnOutput().c_str()));
}

void MainWindow::setChipyardButtonsEnabled(QProcess::ProcessState newState)
{
    if(newState == QProcess::Starting)
    {
        ui->MakeBSP->setEnabled(false);
        ui->MakeMCS->setEnabled(false);
    }
    else if(newState == QProcess::NotRunning){
        ui->MakeBSP->setEnabled(true);
        ui->MakeMCS->setEnabled(true);
    }
}

void MainWindow::readyReadStandardOutputBSP()
{
    std::cout << "APPENDING STD OUTPUT" << std::endl;
    ui->textBrowser->append(this->bspProcess->readAllStandardOutput());
}

void MainWindow::readyReadStandardErrorBSP()
{
    std::cout << "APPENDING ERROR OUTPUT" << std::endl;
    ui->textBrowser->append(this->bspProcess->readAllStandardError());
}
