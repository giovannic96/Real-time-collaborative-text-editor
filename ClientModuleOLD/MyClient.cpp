#include "myClient.h"

#include <qtextcodec.h>

myClient::myClient(
        const QString hostAddress,
        int portNumber,
        QObject *parent
        ) : QObject(parent), m_nNextBlockSize(0)
{
    status = false;

    host = hostAddress;
    port = portNumber;

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &myClient::closeConnection);

    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &myClient::connectionTimeout);
}

void myClient::connect2host()
{
    timeoutTimer->start(3000);

    tcpSocket->connectToHost(host, port);
    connect(tcpSocket, &QTcpSocket::connected, this, &myClient::connected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &myClient::readyRead);
}

void myClient::connectionTimeout()
{
    //qDebug() << tcpSocket->state();
    if(tcpSocket->state() == QAbstractSocket::ConnectingState)
    {
        tcpSocket->abort();
        emit tcpSocket->error(QAbstractSocket::SocketTimeoutError);
    }
}

void myClient::connected()
{
    status = true;
    emit statusChanged(status);
}

bool myClient::getStatus() {return status;}

void myClient::readyRead()
{
    QDataStream in(tcpSocket);
    //in.setVersion(QDataStream::Qt_5_10);
    //for (;;)
    //{
        tcpSocket->bytesAvailable();
        qDebug() << "recvd signal data. bytesAvailable:" << tcpSocket->bytesAvailable();
        QString str = QString::fromUtf8(tcpSocket->readAll());
        //QString str = QString::fromStdString(tcpSocket->readAll().toStdString());
        qDebug() << "recvd: " << str;
        if (str == "0") {
            str = "Connection closed";
            closeConnection();
        }
        emit hasReadSome(str);

        /*

        if (!m_nNextBlockSize)
        {
            if (tcpSocket->bytesAvailable() < sizeof(quint16)) { break; }
            in >> m_nNextBlockSize;
        }

        if (tcpSocket->bytesAvailable() < m_nNextBlockSize) { break; }

        QString str; in >> str;

        if (str == "0")
        {
            str = "Connection closed";
            closeConnection();
        }

        emit hasReadSome(str);
        m_nNextBlockSize = 0;
        */
    //}
}

//void ClientStuff::gotDisconnection()
//{
//    status = false;
//    emit statusChanged(status);
//}

void myClient::closeConnection()
{
    timeoutTimer->stop();

    //qDebug() << tcpSocket->state();
    disconnect(tcpSocket, &QTcpSocket::connected, nullptr, nullptr);
    disconnect(tcpSocket, &QTcpSocket::readyRead, nullptr, nullptr);

    bool shouldEmit = false;
    switch (tcpSocket->state())
    {
        case 0:
            tcpSocket->disconnectFromHost();
            shouldEmit = true;
            break;
        case 2:
            tcpSocket->abort();
            shouldEmit = true;
            break;
        default:
            tcpSocket->abort();
    }

    if (shouldEmit)
    {
        status = false;
        emit statusChanged(status);
    }
}
