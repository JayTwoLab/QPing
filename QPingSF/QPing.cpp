/*
 The MIT License
 SPDX short identifier: MIT https://opensource.org/licenses/MIT
 Copyright 2018-. j2doll https://github.com/j2doll
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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


























