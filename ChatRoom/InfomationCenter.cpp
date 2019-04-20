#include "InfomationCenter.h"
#include <QDateTime>
#include <QByteArray>
#include <QNetworkAddressEntry>
#include <QStringList>

InfomationCenter::InfomationCenter(QObject *parent) : QObject(parent)
{
    MessagePort = 5422;
    FileTransmissionPort = 5424;
    SystemInfoTransmissionPort = 5420;

    connect(&TCP_FileRecv,&QTcpServer::newConnection,this,&InfomationCenter::Slot_NewConnection);
    connect(&TCP_FileRecv,&QTcpServer::acceptError,this,&InfomationCenter::Slot_Error);

    connect(&UDP_FileRecv,&QIODevice::readyRead,this,&InfomationCenter::Slot_UDPreadyRead);
    connect(&UDP_SystemInfo,SIGNAL(readyRead()),this,SLOT(Slot_UDPreadyRead()));
    connect(&UDP_MessageRecv,SIGNAL(readyRead()),this,SLOT(Slot_UDPreadyRead()));

    connect(&UDP_FileRecv,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));
    connect(&UDP_SystemInfo,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));
    connect(&UDP_MessageRecv,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));

    connect(&MsgTimeOut,SIGNAL(timeout()),this,SLOT(Slot_MsgTimerTimeout()));

    SystemInfoMulticastGroup.setAddress("225.225.0.0");
    OrganizationNumber = 5420;

    foreach (QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        QString MACAddr = netInterface.hardwareAddress().split(":").join("-");
        LocalMac_IP[MACAddr] = StrIpToUInt(netInterface.addressEntries().first().ip().toString());
    }
}

void InfomationCenter::SetSystemInfoTransmissionPort(unsigned short Port)
{
    SystemInfoTransmissionPort = Port;
    UDP_SystemInfo.close();
    UDP_SystemInfo.bind(QHostAddress::AnyIPv4, SystemInfoTransmissionPort);
    UDP_SystemInfo.joinMulticastGroup(SystemInfoMulticastGroup);
}

unsigned short InfomationCenter::GetSystemInfoTransmissionPort()
{
    return SystemInfoTransmissionPort;
}

void InfomationCenter::SetFileTransmissionPort(unsigned short Port)
{
    FileTransmissionPort = Port;
    TCP_FileRecv.close();
    TCP_FileRecv.listen(QHostAddress::AnyIPv4,FileTransmissionPort);
    UDP_FileRecv.close();
    UDP_FileRecv.bind(QHostAddress::AnyIPv4,FileTransmissionPort);
}

unsigned short InfomationCenter::GetFileTransmissionPort()
{
    return FileTransmissionPort;
}

void InfomationCenter::SetMessageTransmissionPort(unsigned short Port)
{
    MessagePort = Port;
    UDP_MessageRecv.close();
    UDP_MessageRecv.bind(QHostAddress::AnyIPv4, MessagePort);
}

unsigned short InfomationCenter::GetMessageTransmissionPort()
{
    return MessagePort;
}

void InfomationCenter::Start()
{
    SetSystemInfoTransmissionPort(SystemInfoTransmissionPort);
    SetFileTransmissionPort(FileTransmissionPort);
    SetMessageTransmissionPort(MessagePort);
    MsgTimeOut.start(1000);
}

void InfomationCenter::Slot_NewConnection()
{

}

void InfomationCenter::Slot_Connected()
{

}

void InfomationCenter::Slot_Disconnected()
{

}

void InfomationCenter::Slot_Error(QAbstractSocket::SocketError socketError)
{

}

void InfomationCenter::Slot_TCPreadyRead()
{
    QTcpSocket *TcpSocket = (QTcpSocket *)sender();
    if (Tcp_File.contains(TcpSocket)){

    }
}

void InfomationCenter::Slot_UDPreadyRead()
{
    QUdpSocket *UDPSocket = (QUdpSocket *)sender();
    RecvDataInfo t_RecvDataInfo;
    unsigned int DataLenth;
    QByteArray Data;
    DataLenth = UDPSocket->pendingDatagramSize();
    t_RecvDataInfo.Data.resize(DataLenth);
    UDPSocket->readDatagram(Data.data(), DataLenth, &t_RecvDataInfo.HostAddr, &t_RecvDataInfo.SrcPort);
    t_RecvDataInfo.DesPort = UDPSocket->localPort();
    UDPRecvData.append(t_RecvDataInfo);
}

void InfomationCenter::Slot_MsgTimerTimeout()
{
    unsigned int newTime_t = QDateTime::currentDateTime().toTime_t();
    for (auto i = MessageID_SendTime.begin(); i != MessageID_SendTime.end();++i){
        if (newTime_t - i.value() > 10){
            emit MessageState(i.key(),SendState::Failed);
            MessageID_SendTime.remove(i.key());
        }
    }
}

void InfomationCenter::SendData(QByteArray Data, unsigned int DesIP, unsigned short DesPort)
{

}

void InfomationCenter::SendData(QByteArray Data, QHostAddress HostAddr, unsigned short DesPort)
{
    QByteArray WaitSendData;
    char StartTag = 0x66;
    char StopTag = 0x77;
    WaitSendData.append((char *)&OrganizationNumber, 4);
    WaitSendData.append(&StartTag, 1);
    WaitSendData.append(Data);
    WaitSendData.append(&StopTag,1);
    if (DesPort == MessagePort){
        UDP_MessageRecv.writeDatagram(WaitSendData,HostAddr,DesPort);
    }
    if (DesPort == FileTransmissionPort){
        UDP_FileRecv.writeDatagram(WaitSendData,HostAddr,DesPort);
    }
    if (DesPort == SystemInfoTransmissionPort){
        UDP_SystemInfo.writeDatagram(WaitSendData,HostAddr,DesPort);
    }

}

void InfomationCenter::SendHello()
{
    QByteArray WaitSendData;
    WaitSendData.clear();

    UDP_SystemInfo;
}

void InfomationCenter::SendOnlineState(unsigned int State)
{
    QByteArray WaitSendData;
    WaitSendData.clear();
    UDP_SystemInfo;
}

void InfomationCenter::SendIpMacInquiry()
{
    QByteArray WaitSendData;
    WaitSendData.clear();
    UDP_SystemInfo;
}

void InfomationCenter::FindIp(QString MACAddr)
{
    QByteArray WaitSendData;
    WaitSendData.clear();
    QStringList StrList = MACAddr.split("-");
    unsigned char A = 0;
    unsigned char B;
    unsigned char C;
    unsigned char D;
    unsigned char E;
    unsigned char F;
    UDP_SystemInfo;
}

QString InfomationCenter::UIntToStrIp(unsigned int Ip)
{
    QHostAddress UIntIP(Ip);
    return UIntIP.toString();
}

unsigned int InfomationCenter::StrIpToUInt(QString IP)
{
    QHostAddress StrIP(IP);
    return StrIP.toIPv4Address();
}
