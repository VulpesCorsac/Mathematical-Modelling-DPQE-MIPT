#include "AntLoop.h"
#include <QString>
#include <QHostAddress>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const QString defaultServerIP = "127.0.0.1";
    const int defaultPort = 31415;

    QString serverIP = defaultServerIP;

    if (QCoreApplication::arguments().size() > 1)
    {
        QHostAddress ipAddress;

        QString tempValue = QCoreApplication::arguments().at(1);

        if (ipAddress.setAddress(tempValue))
        {
            serverIP = tempValue;
        }
        else
        {
            std::cerr << "Неверный IP адрес: " << tempValue.toStdString() << std::endl << std::flush;
        }
    }

    CAntLoop ant;

    ant.InitAnt("Vadim", AtFarmer);

    ant.ConnectMap(serverIP, defaultPort);

    ant.AntLoop();

    ant.DisconnectMap();

    return 0;
}

