// main.cpp

#include <QtGlobal>
#include <QCoreApplication>
#include <QProcess>
#include <QtGlobal>
#include <QDebug>
#include <QFile>
#include <QSettings>

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
        qDebug() << "failed to load ini file";
        return;
    }

    QString destIpAddress = "192.168.100.10";
    // QString destIpAddress = "192.168.0.1";

    QPing::pingResult result = qp.ping(destIpAddress);

    switch( result )
    {
        case QPing::pingSuccess:
            qDebug() << " Success to ping " << destIpAddress;
        break;

        case QPing::pingFailed:
            qDebug() << " Failed to ping " << destIpAddress;
        break;

        case QPing::initFailed:
            qDebug() << "[NOK] Initialization is failed";
        break;

        case QPing::notFound:
            qDebug() << "[NOK] Result is not found";
        break;
    }
}
