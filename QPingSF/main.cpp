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

void testQPing();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    testQPing();
    return 0;  // return a.exec();
}

void testQPing()
{
    QPing qp;
    QString iniFilePath = "./ping-config-win-kr.ini"; // see sample of *.ini
    qp.setIniFile( iniFilePath );
    if ( ! qp.loadIniFile() )
    {
        std::cout <<  "failed to load ini file" << std::endl;
        return;
    }

    QString destIpAddress = "192.168.100.10";
    // QString destIpAddress = "192.168.0.1";

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
