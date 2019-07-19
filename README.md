## QPing

> *Read this in other languages: [English](README.md), :kr: [한국어](README.ko.md)*

![](markdown-data/qping.png)

- Ping class for Qt 5

- You can check the response by shooting the ping.

### Note

- I do not call functions that use the ICMP protocol.
	- I have written a raw socket program for pinging in the past.
	- But there's a problem with user's elevation. Application should be executed by root or superuser.

### How to use

- Copy QPing.h, QPing.cpp to your project.

- Append Qt project(*.pro) setting of source code

```qmake
HEADERS += QPing.h
SOURCES += QPing.cpp
```

- Add source code that applies the class. See main.cpp.

```cpp
// main.cpp 
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

    // See sample of *.ini for each OS and language. You can make your own INI.
    QString iniFilePath = "./ping-config-win-en.ini"; // Windows, English
    // QString iniFilePath = "./ping-config-win-kr.ini"; // Windows, Korean
    // QString iniFilePath = "./ping-config-linux-en.ini"; // Linux, English

    QPing qp;
     
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
    }

    return 0;  // return a.exec();
}
```

### License and links

- QPing is under MIT license. [https://github.com/j2doll/QPing](https://github.com/j2doll/QPing)

### Contact

- Leave me a issue. [https://github.com/j2doll/QPing/issues](https://github.com/j2doll/QPing/issues)

- Hi! I'm j2doll. My native language is not English and my English is not fluent. Please, use EASY English. :-)
