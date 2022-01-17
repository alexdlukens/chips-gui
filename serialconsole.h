#ifndef SERIALCONSOLE_H
#define SERIALCONSOLE_H
#include <string>
#include <QDir>
#include <QString>

class SerialConsole
{
public:
    SerialConsole();
    int baudRate;
    std::string serialPort;
    QStringList getTTYList();
};

#endif // SERIALCONSOLE_H
