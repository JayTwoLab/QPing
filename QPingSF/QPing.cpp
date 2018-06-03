// QPing.cpp

#include <QtGlobal>
#include <QProcess>
#include <QtGlobal>
#include <QDebug>
#include <QFile>
#include <QSettings>

#include "QPing.h"

QPing::QPing(QObject *parent)
    : QObject(parent)
{
    m_iniFile.clear();

    m_pingParam.clear();
    m_successString.clear();
    m_failedString.clear();

}

void QPing::setIniFile(QString iniFile)
{
    m_iniFile = iniFile;
}

QString QPing::iniFile() const
{
    return m_iniFile;
}

bool QPing::loadIniFile(QString iniFile)
{
    if ( m_iniFile.isEmpty() )
    {
        if ( iniFile.isEmpty() )
        {
            return false;
        }
       m_iniFile = iniFile;
    }

    QString fileName = QString("%1").arg(m_iniFile);
    QSettings settings( fileName, QSettings::IniFormat );
    settings.setIniCodec( "UTF-8" );

    QVariant varPingParam = settings.value( "ping-param" );
    if ( varPingParam.toString().isEmpty() )
    {
        return false;
    }
    m_pingParam = varPingParam.toString();

    QVariant varSuccessString = settings.value( "success-string" );
    if ( varSuccessString.toString().isEmpty() )
    {
        return false;
    }
    m_successString = varSuccessString.toString();

    QVariant varFailedString = settings.value( "failed-string" );
    if ( varFailedString.toString().isEmpty() )
    {
        return false;
    }
    m_failedString = varFailedString.toString();

    return true;
}

QPing::pingResult QPing::ping(QString ipAddress)
{
    // note: ping param can be empty

    if ( m_successString.isEmpty() )
    {
        qDebug() << "m_successString is empty";
        return initFailed;
    }

    if ( m_failedString.isEmpty())
    {
        qDebug() << "m_failedString is empty";
        return initFailed;
    }

    QProcess pingProcess;
    QString executeString = QString("ping %1 %2").arg(m_pingParam).arg(ipAddress);

    pingProcess.start(executeString);
    pingProcess.waitForFinished();

    QByteArray ba = pingProcess.readAllStandardOutput();
    QString output = QString::fromLocal8Bit( ba );

    if ( output.indexOf(m_successString) >= 0 )
    {
        qDebug() << "Success to PING";
        return pingSuccess;
    }

    if ( output.indexOf(m_failedString) >= 0 )
    {
        qDebug() << "Failed to PING";
        return pingFailed;
    }

    return notFound; // result is not found
}


























