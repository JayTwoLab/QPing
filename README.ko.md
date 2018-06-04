## QPing

> *Read this in other languages: [English](README.md), :kr: [한국어](README.ko.md)*

### 요약
- Ping 클래스. Qt5 지원.

### 노트
- ICMP 프로토콜을 사용하는 함수를 부르지 않도록 구성하였습니다.
	- 저는 예전에 로소켓을 사용하는 유사한 클래스를 만든 적이 있습니다.
	- 하지만 그런 경우 사용자 계정의 권한 상읏이 필요합니다. 루트, 슈퍼유저, 어드민 등 정도의 권한이 필요하지요.

### 설정 방법
- QPing.h, QPing.cpp 를 여러분의 프로젝트에 복사하세요.
- 여러분의 Qt 프로젝트(*.pro)에 해당 소스 코드를 추가하세요.
```qmake
HEADERS += QPing.h
SOURCES += QPing.cpp
```
- 클래스를 활용하는 소스 코드를 넣으세요. main.cpp를 참조하세요.
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

    // see sample of *.ini for OS (You can
    // QString iniFilePath = "./ping-config-win-en.ini"; // Windows, English
    QString iniFilePath = "./ping-config-win-kr.ini"; // Windows, Korean
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
```

### 라이센스
- MIT 라이센스

### 문의
- https://github.com/j2doll/QPing
