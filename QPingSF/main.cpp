/*
 The MIT License
 SPDX short identifier: MIT https://opensource.org/licenses/MIT
 Copyright 2018-. j2doll https://github.com/j2doll
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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

    QString destIpAddress = "192.168.0.10";
    if ( argc == 2 )
    {
        // You can use application first parameter
        // For example) QPingSF 192.168.200.50
        QString strArg = argv[1];
        destIpAddress = strArg;
    }

    // Define your OS and OS language.
    // See sample of *.ini for OS. (You can define your own INI file)
    QString iniFilePath = "./ping-config-win-en.ini"; // Windows, English
    // QString iniFilePath = "./ping-config-win-kr.ini"; // Windows, Korean
    // QString iniFilePath = "./ping-config-linux-en.ini"; // Linux, English

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

        case QPing::initFailed: // something wrong
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

