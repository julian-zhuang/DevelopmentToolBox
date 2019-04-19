#include "InfomationCenter.h"
#include <QDateTime>

InfomationCenter::InfomationCenter(QObject *parent) : QObject(parent)
{
    SystemInfoTransmissionPort = 5420;
    MessagePort = 5422;
    FileTransmissionPort = 5424;
    MsgTimeOut.start(1000);

    connect(&TCP_FileRecv,SIGNAL(newConnection()),this,SLOT(Slot_NewConnection()));
    connect(&TCP_FileRecv,SIGNAL(acceptError(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));

    connect(&UDP_FileRecv,SIGNAL(readyRead()),this,SLOT(Slot_UDPreadyRead()));
    connect(&UDP_SystemInfo,SIGNAL(readyRead()),this,SLOT(Slot_UDPreadyRead()));
    connect(&UDP_MessageRecv,SIGNAL(readyRead()),this,SLOT(Slot_UDPreadyRead()));

    connect(&UDP_FileRecv,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));
    connect(&UDP_SystemInfo,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));
    connect(&UDP_MessageRecv,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));

}

void InfomationCenter::SetSystemInfoTransmissionPort(unsigned short Port)
{
    SystemInfoTransmissionPort = Port;
    UDP_SystemInfo.close();
    UDP_SystemInfo.bind(QHostAddress::AnyIPv4, SystemInfoTransmissionPort);
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
    RecvDataInfo t_RecvDataInfo;
    unsigned int DataLenth;
    QByteArray Data;
    QUdpSocket *UDPSocket = (QUdpSocket *)sender();
    DataLenth = UDPSocket->pendingDatagramSize();
    t_RecvDataInfo.Data.resize(DataLenth);
    UDPSocket->readDatagram(Data.data(), DataLenth, &t_RecvDataInfo.HostAddr, &t_RecvDataInfo.SrcPort);
    t_RecvDataInfo.DesPort = UDPSocket->localPort();
    UDPRecvData.append(t_RecvDataInfo);
}

void InfomationCenter::Slot_MsgTimerTimeout()
{
    unsigned int newTime_t = QDateTime::currentDateTime().toTime_t();
    for (auto i = Message_SendTime.begin();i != Message_SendTime.end();++i){
        if (newTime_t - i.value() > 10){
            emit MessageState(i.key(),SendState::Failed);
            Message_SendTime.remove(i.key());
        }
    }
}
