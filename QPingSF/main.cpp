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

    QString destIpAddress = "192.168.200.254";
    if ( argc == 2 )
    {
        // You can use application first parameter
        // For example) QPingSF 192.168.0.10
        QString strArg = argv[1];
        destIpAddress = strArg;
    }

    // Define your OS and OS language.
    // See sample of *.ini for OS. (You can define your own INI file)
    // Please suggest strings that can be set in various languages and operating systems.

    QString iniFilePath;

#ifdef Q_OS_WIN
    iniFilePath = ":/ping-config-win-en.ini"; // Windows, English
    // iniFilePath = ":/ping-config-win-kr.ini"; // Windows, Korean
#endif

#ifdef Q_OS_LINUX
    iniFilePath = ":/ping-config-linux-en.ini"; // Linux, English
#endif

#ifdef Q_OS_MAC
    // iniFilePath = mac ini... I don't have a Mac, because I'm poor.
#endif

    ////////////////////

    QPing qp; // main class

    qp.setIniFile( iniFilePath ); // set configuration file
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

        case QPing::initFailed1: // "m_successString is empty"
        case QPing::initFailed2: //  "m_failedString is empty"
            std::cout <<  "[ERROR] Initialization is failed" << std::endl;
        break;

        case QPing::notFound: // something wrong
            std::cout <<  "[ERROR] Result is not found" << std::endl;
        break;

        default:
            std::cout <<  "Undefined result : " << ((quint32)result) << std::endl;
        break;
    }

    return 0;
}

