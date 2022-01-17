#include "serialconsole.h"

SerialConsole::SerialConsole()
{
    this->baudRate = 9600;
    this->serialPort = "";
}

//return list of TTY ports in /dev directory
QStringList SerialConsole::getTTYList() {
    QStringList ttyList;
    QDir devTTYDir;
    devTTYDir.setPath("/dev");
    devTTYDir.setFilter(QDir::System);
    devTTYDir.setNameFilters(QStringList("tty*"));
    ttyList = devTTYDir.entryList();
    return ttyList;
}

//call this when QComboBox for port selection is "activated"/an option is chosen
void SerialConsole::setSerialPort(QString port)
{
    this->serialPort = port;
}

//call this when QComboBox for baud rate selection is "activated;
void SerialConsole::setBaudRate(int rate)
{
    this->baudRate = rate;
}
