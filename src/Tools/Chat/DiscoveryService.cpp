#include "DiscoveryService.h"

#include <json/json.h>

DiscoveryService* DiscoveryService::m_Instance = nullptr;

#pragma execution_character_set("utf-8")

void DiscoveryService::DestoryInstance()
{
    if (m_Instance == nullptr){
        return;
    }
    delete m_Instance;
    m_Instance = nullptr;
    return;
}

DiscoveryService *DiscoveryService::Instance()
{
    if (m_Instance == nullptr){
        m_Instance = new DiscoveryService();
    }
    return m_Instance;
}

bool DiscoveryService::BindRecvPort(quint16 port)
{
    QUdpSocket *&UdpSocket = m_BroadCastUdpSockets[port];
    if (UdpSocket == nullptr){
        UdpSocket = new QUdpSocket;
    }
    if (UdpSocket->bind(port) == false){
        delete UdpSocket;
        UdpSocket = nullptr;
        return false;
    }
    UdpSocket->writeDatagram("HelloEveryone", QHostAddress::Broadcast, port);
    connect(UdpSocket, &QUdpSocket::readyRead, [this, UdpSocket] {
            QHostAddress    Client_Address;
            quint16         CLient_Port = 0;
            QHostAddress    Server_Address = UdpSocket->localAddress();
            quint16         Server_Port = UdpSocket->localPort();
            QByteArray Datagram;
            Datagram.resize(UdpSocket->pendingDatagramSize());
            UdpSocket->readDatagram(Datagram.data(), Datagram.size(), &Client_Address, &CLient_Port);
            emit Signal_RecvBroadCastContent(CLient_Port, QHostAddress(Client_Address.toIPv4Address()), Datagram);
        });
    return true;
}

bool DiscoveryService::ReleaseRecvPort(quint16 port)
{
    if (m_BroadCastUdpSockets.contains(port) == true) {
        QUdpSocket*& UdpSocket = m_BroadCastUdpSockets[port];
        UdpSocket->close();
        delete UdpSocket;
        UdpSocket = nullptr;
        m_BroadCastUdpSockets.remove(port);
        return true;
    }
    return false;
}

void DiscoveryService::AddBroadCastContent(quint16 port, QByteArray Content)
{
    m_BroadCastContents[port] = Content;
}

void DiscoveryService::DelBroadCastContent(quint16 port)
{
    if (m_BroadCastContents.contains(port) == true) {
        m_BroadCastContents.remove(port);
    }
}

DiscoveryService::DiscoveryService()
{
    connect(&m_Timer, &QTimer::timeout, [&](){
        for (auto i = m_BroadCastContents.begin(); i != m_BroadCastContents.end(); i++){
            m_UdpSocket.writeDatagram(i.value(), QHostAddress::Broadcast, i.key());
        }
    });
    m_Timer.start(1000);
}

DiscoveryService::~DiscoveryService()
{
    m_Timer.stop();
    for (auto i = m_BroadCastUdpSockets.begin(); i != m_BroadCastUdpSockets.end(); i++){
        i.value()->writeDatagram("GoodbyeEveryone", QHostAddress::Broadcast, i.key());
        i.value()->waitForBytesWritten(1000);
        if (i.value() != nullptr){
            i.value()->close();
        }
        delete i.value();
        i.value() = nullptr;
    }
}

