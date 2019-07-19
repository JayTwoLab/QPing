## QPing

> *Read this in other languages: [English](README.md), :kr: [한국어](README.ko.md)*

![](markdown-data/qping.png)

- Ping 클래스. Qt 기반.

- 이 클래스로 ping을 쏘고 응답을 확인할 수 있습니다.

### 노트

- ICMP 프로토콜을 사용하는 함수를 호출하지 않도록 구성하였습니다.
	- 저는 예전에 로소켓을 사용하는 유사한 클래스를 만든 적이 있습니다.
	- 하지만 그런 경우 사용자 계정의 권한 상승이 필요합니다. root, superuser, admin 등

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

    // 각 OS 별 INI 파일을 참조하세요. 자신만의 INI 파일을 만들 수 있습니다.
    // QString iniFilePath = "./ping-config-win-en.ini"; // Windows, English
    QString iniFilePath = "./ping-config-win-kr.ini"; // Windows, Korean
    // QString iniFilePath = "./ping-config-linux-en.ini"; // Linux, English

    QPing qp;
     
    qp.setIniFile( iniFilePath ); // 환경 파일을 설정
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

        case QPing::initFailed: // 초기화 실패
            std::cout <<  "[ERROR] Initialization is failed" << std::endl;
        break;

        case QPing::notFound: // 비정상 결과값
            std::cout <<  "[ERROR] Result is not found" << std::endl;
        break;
    }

    return 0;  
}
```

### 라이센스

- QPing은 MIT 라이센스입니다. [https://github.com/j2doll/QPing](https://github.com/j2doll/QPing)

### 문의

- 이슈를 남겨 주세요. [https://github.com/j2doll/QPing/issues](https://github.com/j2doll/QPing/issues)
