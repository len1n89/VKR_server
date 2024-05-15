#include "tcpServer.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QDebug>

TcpServer::TcpServer(int port)
    : m_nNextBlockSize(0)
//    , m_clients(new QList<QTcpSocket*>)
{
    m_tcpServer = new QTcpServer(this);
    if(!m_tcpServer->listen(QHostAddress::Any, port)) {
        qDebug()<<"Error "<<m_tcpServer->errorString();
        m_tcpServer->close();
        return;
    }

//    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection));
}

void TcpServer::newConnection()
{
    QTcpSocket *clientSocket = m_tcpServer->nextPendingConnection();

    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::readyRead, this, &TcpServer::readClient);
    connect(clientSocket, &QTcpSocket::disconnected, this, &TcpServer::gotDisconnection);

    m_clients << clientSocket;

    sendToClient(clientSocket, "Reply: connection established");
}

void TcpServer::readClient()
{
    QTcpSocket *clientSocket = (QTcpSocket*)sender();
    QDataStream in(clientSocket);
    //in.setVersion(QDataStream::Qt_5_10);
    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (clientSocket->bytesAvailable() < sizeof(quint16)) { break; }
            in >> m_nNextBlockSize;
        }

        if (clientSocket->bytesAvailable() < m_nNextBlockSize) { break; }
        QString str;
        in >> str;

        emit gotNewMesssage(str);

        m_nNextBlockSize = 0;

        if (sendToClient(clientSocket, QString("Reply: received [%1]").arg(str)) == -1)
        {
            qDebug() << "Some error occured";
        }
    }
}

void TcpServer::gotDisconnection()
{
    m_clients.removeAt(m_clients.indexOf((QTcpSocket*)sender()));
    emit smbDisconnected();
}

qint64 TcpServer::sendToClient(QTcpSocket *socket, const QString &str)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_10);
    //out << quint16(0) << QTime::currentTime() << str;
    out << quint16(0) << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    return socket->write(arrBlock);
}

QList<QTcpSocket *> TcpServer::getClients()
{
    return m_clients;
}
