// main.cpp

#include <QtGlobal>
#include <QCoreApplication>
#include <QProcess>
#include <QtGlobal>
#include <QDebug>
#include <QFile>

void test();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    test();

    return 0;
    // return a.exec();
}

void test()
{
    QProcess pingProcess;
    // QString executeString = "ping 192.168.0.1";
    QString executeString = "ping 192.168.99.1";

    pingProcess.start(executeString);
    pingProcess.waitForFinished();

    QByteArray ba = pingProcess.readAllStandardOutput();
    QString output = QString::fromLocal8Bit( ba );

    // current source code is EUC-KR character-set
    QString successString;
    QString failedString;

    QFile file("message.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "failed to load message.txt";
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8"); // message.txt must be UTF-8 text file.
    quint32 lineCount = 0;
    while(!in.atEnd())
    {
        QString line = in.readLine();
        lineCount++;

        switch ( lineCount)
        {
            case 1:
                successString = line;
            break;

            case 2:
                failedString = line;
            break;
        }

        qDebug() << line;
    }

    if ( output.indexOf(successString) >= 0 )
    {
        qDebug() << "Success to PING";
    }

    if ( output.indexOf(failedString) >= 0 )
    {
        qDebug() << "Failed to PING";
    }


    // qDebug() << output;
}
