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
    QString serialPort;

    QStringList getTTYList();
    void setSerialPort(QString port);
    void setBaudRate(int rate);
};

#endif // SERIALCONSOLE_H
