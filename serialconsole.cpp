#include "serialconsole.h"

SerialConsole::SerialConsole()
{
    this->baudRate = 9600;
    this->serialPort = "";
}

QStringList SerialConsole::getTTYList() {
    QStringList ttyList;
    QDir devTTYDir;
    devTTYDir.setPath("/dev");
    devTTYDir.setFilter(QDir::System);
    devTTYDir.setNameFilters(QStringList("tty*"));
    ttyList = devTTYDir.entryList();
    return ttyList;
}
