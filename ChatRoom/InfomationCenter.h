#ifndef INFOMATIONCENTER_H
#define INFOMATIONCENTER_H

#include <QObject>
#include <QTimer>
#include <QFile>
#include <QTcpServer>
#include <QUdpSocket>
#include <QTcpSocket>
enum SendState{
    Send,
    Failed,
    Successfully
};

class InfomationCenter : public QObject
{
    Q_OBJECT
public:
    explicit InfomationCenter(QObject *parent = 0);

signals:
    void MessageState(QString MsgID, SendState State);

public:
    QString GetMacAddrIP(QString MacAddr);
    QString SetFileID(QString FilePath);
    QString GetFilePath(QString FileID);

    void SetFileRecvPermission(QString ID, QString MacAddr, bool Permission = true);
    void SetFileSendPermission(QString ID, QString MacAddr, bool Permission = true);
    bool GetFileRecvPermission(QString ID, QString MacAddr);
    bool GetFileSendPermission(QString ID, QString MacAddr);

    void SetSystemInfoTransmissionPort(unsigned short Port);
    unsigned short GetSystemInfoTransmissionPort();

    void SetFileTransmissionPort(unsigned short Port);
    unsigned short GetFileTransmissionPort();

    void SetMessageTransmissionPort(unsigned short Port);
    unsigned short GetMessageTransmissionPort();
private:
    struct RecvDataInfo{
        QHostAddress HostAddr;
        unsigned short SrcPort;
        unsigned short DesPort;
        QByteArray Data;
    };

public slots:
    void SendOnlineState(unsigned int State);
    void SendIpMacInquiry();

private slots:
    void Slot_Connected();
    void Slot_Disconnected();
    void Slot_Error(QAbstractSocket::SocketError socketError);
    void Slot_NewConnection();

    void Slot_TCPreadyRead();
    void Slot_UDPreadyRead();

    void RecvData(QByteArray Data,unsigned int SrcIP,unsigned short SrcPort);
    void SendData(QByteArray Data,unsigned int DesIP,unsigned short DesPort);

    void Slot_MsgTimerTimeout();

private:
    unsigned short SystemInfoTransmissionPort;
    unsigned short FileTransmissionPort;
    unsigned short MessagePort;

    QTcpServer TCP_FileRecv;
    QUdpSocket UDP_FileRecv;
    QUdpSocket UDP_SystemInfo;
    QUdpSocket UDP_MessageRecv;

    QMap <QTcpSocket *, QFile> Tcp_File;
    QMap <QString,QString> FileID_Name;
    QMap <QString,QString> FileID_Path;
    QList<RecvDataInfo> UDPRecvData;

    QTimer MsgTimeOut;
    QMap<QString, unsigned int> Message_SendTime;
};

#endif // INFOMATIONCENTER_H
