/*
 The MIT License
 SPDX short identifier: MIT https://opensource.org/licenses/MIT
 Copyright 2018-. j2doll https://github.com/j2doll
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// QPing.h

#ifndef QPING_H
#define QPING_H

#include <QtGlobal>
#include <QObject>
#include <QtGlobal>
#include <QProcess>
#include <QtGlobal>
#include <QFile>
#include <QSettings>
#include <QString>

/**
 * @brief The QPing class
 * @author j2doll https://github.com/j2doll
 * @date from 2018-
 */
class QPing : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief QPing
     * @param constructor
     */
    explicit QPing(QObject *parent = nullptr);

public:

    /**
     * @brief set ini file for os and os language
     * @param iniFile : ini file name
     */
    void setIniFile(QString iniFile);

    /**
     * @brief ini file name
     * @return return ini file name
     */
    QString iniFile() const;

public:
    /**
     * @brief ping reult
     * @enum  pingSuccess : success to ping.
     * @enum  pingFailed : failed to ping.
     * @enum initFailed : initialization is failed. something wrong.
     * @enum notFound : result is not found. something wrong.
     */
    enum pingResult
    { pingSuccess, pingFailed, initFailed1, initFailed2, notFound };

public:

    /**
     * @brief load INI file(*.ini) for ping configuation. see sample of ini file.
     * @param iniFile : name of ini file for config. if you set ini file name, you may not set this param.
     * @return true: success to load ini file. false: failed to load ini file.
     */
    bool loadIniFile( QString iniFile = QString("") );

    /**
     * @brief ping function.
     * @param destIpAddress : destination ip address
     * @return returns ping result
     */
    QPing::pingResult ping( QString destIpAddress );

protected:
    /**
     * @brief ini file path & name
     */
    QString m_iniFile;

    /**
     * @brief ping parameter. The values may vary by operating system(win/linux/mac/etc).
     */
    QString m_pingParam;

    /**
     * @brief sting that is success to ping
     */
    QString m_successString;

    /**
     * @brief sting that is failed to ping
     */
    QString m_failedString;


};

#endif // QPING_H
