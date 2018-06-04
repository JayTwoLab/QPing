// main.cpp

#include <QtGlobal>
#include <QCoreApplication>
#include <QProcess>
#include <QtGlobal>
#include <QDebug>
#include <QFile>
#include <QSettings>

#include <iostream>

#include "QPing.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString destIpAddress = "192.168.0.1";
    if ( argc == 2 )
    {
        // You can use application first parameter
        // For example) QPingSF 192.168.100.10
        QString strArg = argv[1];
        destIpAddress = strArg;
    }

    // see sample of *.ini for OS (You can
    QString iniFilePath = "./ping-config-win-en.ini"; // Windows, English
    // QString iniFilePath = "./ping-config-win-kr.ini"; // Windows, Korean
    // QString iniFilePath = "./ping-config-linux-en.ini"; // Linux, English

    QPing qp;

     // set configuration file
    qp.setIniFile( iniFilePath );
    if ( ! qp.loadIniFile() )
    {
        std::cout <<  "[ERROR] Failed to load ini file" << std::endl;
        return (-1);
    }

    // Ping!
    QPing::pingResult result = qp.ping(destIpAddress);

    switch( result )
    {
        case QPing::pingSuccess:
            std::cout <<  "Success to ping" << std::endl;
        break;

        case QPing::pingFailed:
            std::cout <<  "Failed to ping" << std::endl;
        break;

        case QPing::initFailed: // something wrong
            std::cout <<  "[ERROR] Initialization is failed" << std::endl;
        break;

        case QPing::notFound: // something wrong
            std::cout <<  "[ERROR] Result is not found" << std::endl;
        break;
    }

    return 0;  // return a.exec();
}

