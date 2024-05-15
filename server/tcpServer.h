#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>

class QTcpServer;
class QTcpSocket;

class TcpServer : public QObject
{
    Q_OBJECT

public:
    TcpServer();
    virtual ~TcpServer() {}

public:
    QList<QTcpSocket *> getClients();

public slots:
    virtual void newConnection();
    void readClient();
    void gotDisconnection();
    qint64 sendToClient(QTcpSocket *socket, const QString &str);

signals:
    void gotNewMesssage(QString msg);
    void smbDisconnected();

private:
    quint16 m_nNextBlockSize;
    QList<QTcpSocket*> m_clients;
    QTcpServer *m_tcpServer;

};

#endif // TCPSERVER_H
