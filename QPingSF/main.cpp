// main.cpp

#include <QtGlobal>
#include <QCoreApplication>
#include <QProcess>
#include <QtGlobal>
#include <QDebug>
#include <QFile>
#include <QSettings>

#include <iostream>
using namespace std;

#include "QPing.h"

void testQPing(QString destIpAddress);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString destIpAddress = "192.168.0.1";
    if ( argc == 2 )
    {
        QString strArg = argv[1];
        destIpAddress = strArg;
    }
    testQPing(destIpAddress);
    return 0;  // return a.exec();
}

void testQPing(QString destIpAddress)
{

    // see sample of *.ini
    QString iniFilePath = "./ping-config-win-kr.ini";
    // QString iniFilePath = "./ping-config-linux-en.ini";

    QPing qp;
    qp.setIniFile( iniFilePath );
    if ( ! qp.loadIniFile() )
    {
        std::cout <<  "failed to load ini file" << std::endl;
        return;
    }

    QPing::pingResult result = qp.ping(destIpAddress);

    switch( result )
    {
        case QPing::pingSuccess:
            std::cout <<  "Success to ping" << std::endl;
        break;

        case QPing::pingFailed:
            std::cout <<  "Failed to ping" << std::endl;
        break;

        case QPing::initFailed:
            std::cout <<  "[NOK] Initialization is failed" << std::endl;
        break;

        case QPing::notFound:
            std::cout <<  "[NOK] Result is not found" << std::endl;
        break;
    }
}
