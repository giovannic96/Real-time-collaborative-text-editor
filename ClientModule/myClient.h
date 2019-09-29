#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QString>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>

class myClient : public QObject
{
    Q_OBJECT

public:
    myClient(const QString hostAddress, int portVal, QObject *parent = nullptr);

    QTcpSocket *tcpSocket;
    bool getStatus();

public slots:
    void closeConnection();
    void connect2host();

signals:
    void statusChanged(bool);
    void hasReadSome(QString msg);

private slots:
    void readyRead();
    void connected();
    void connectionTimeout();

private:
    QString host;
    int port;
    bool status;
    quint16 m_nNextBlockSize;
    QTimer *timeoutTimer;
};

#endif // MYCLIENT_H
