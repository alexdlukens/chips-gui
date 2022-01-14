#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QSettings &settingsMap, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->mainSettings = &settingsMap;
    this->editedSettings.clear();
//    std::cout << "success" << std::endl;

    //pull values from QSettings if they exist, put them in the corresponding areas
    if(this->mainSettings->contains("freedom_sdk_path")){
        ui->freedomSdkPath->setText(this->mainSettings->value("freedom_sdk_path").toString());
    }
    if(this->mainSettings->contains("chip_fpga")){
        ui->chipyardFpgaPath->setText(this->mainSettings->value("chip_fpga").toString());
    }

    connect(ui->chipyardFpgaButton, SIGNAL(clicked(bool)), this, SLOT(onChipFpgaButtonClicked()));
    connect(ui->freedomSdkButton, SIGNAL(clicked(bool)), this, SLOT(onFreedomSdkButtonClicked()));
    connect(ui->ExitButtons, SIGNAL(accepted()), this, SLOT(onExitButtonClicked()));
}

void SettingsDialog::onChipFpgaButtonClicked()
{
    //when button clicked, get path to chipyard fpga directory;
    QString dirPath = QFileDialog::getExistingDirectory(this, "Chipyard/FPGA Dir", "$pwd");
    if(!dirPath.isEmpty()){
        ui->chipyardFpgaPath->setText(dirPath);
        this->editedSettings["chip_fpga"] = dirPath;
    }

}
void SettingsDialog::onFreedomSdkButtonClicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, "Freedom-E-SDK Dir", "$pwd");
    if(!dirPath.isEmpty()){
        ui->freedomSdkPath->setText(dirPath);
        this->editedSettings["freedom_sdk_path"] = dirPath;
    }
}


SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::onExitButtonClicked()
{
    for(auto i : this->editedSettings){
        this->mainSettings->setValue(i.first, i.second);
        std::cout << "storing settings: " + i.first.toStdString() + ", " + i.second.toStdString() << std::endl;
    }
}
