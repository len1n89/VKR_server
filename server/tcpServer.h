#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>

class QTcpServer;
class QTcpSocket;

//! \class TcpServer
//! \brief Отвечает за установку соединения с агентами и передачу иформации

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
    //! отключился клиент номер index в списке m_clients, он уже удален!!!
    void clientDisconnected(const int index);

private:
    quint16 m_nNextBlockSize;
    //! Массив подключенных на данный момент клиентов(сокетов)
    QList<QTcpSocket*> m_clients;
    QTcpServer *m_tcpServer;

};

#endif // TCPSERVER_H
