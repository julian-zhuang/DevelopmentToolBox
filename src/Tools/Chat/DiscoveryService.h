#ifndef DISCOVERYSERVICE_H
#define DISCOVERYSERVICE_H

#include <QTimer>
#include <QObject>
#include <QString>
#include <QUdpSocket>
#include <QByteArray>
#include <QHostAddress>

class DiscoveryService : public QObject
{
    Q_OBJECT

signals:
    void Signal_RecvBroadCastContent(quint16 recv_port, QHostAddress client_addr, QByteArray Datagram);

public:
    static void DestoryInstance();
    static DiscoveryService *Instance();

    bool BindRecvPort(quint16 port);
    bool ReleaseRecvPort(quint16 port);
    void AddBroadCastContent(quint16 port, QByteArray Content);
    void DelBroadCastContent(quint16 port);

protected:
    explicit DiscoveryService();
    ~DiscoveryService();

private:
    static DiscoveryService* m_Instance;

    QUdpSocket m_UdpSocket;
    QTimer m_Timer;
    QMap<quint16, QByteArray> m_BroadCastContents;
    QMap<quint16, QUdpSocket*> m_BroadCastUdpSockets;
};

#endif // DISCOVERYSERVICE_H
