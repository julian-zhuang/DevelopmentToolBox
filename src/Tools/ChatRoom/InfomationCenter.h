#ifndef INFOMATIONCENTER_H
#define INFOMATIONCENTER_H

#include <QObject>
#include <QTimer>
#include <QFile>
#include <QTcpServer>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QMutex>
#include <QThread>
#include <QIcon>

struct InfoCard{
    QString ID;
    QIcon Icon;
    QString Name;
    QString Profile;
};

struct MemberInfoCard :public InfoCard{
    int             Sex;
    char            MacAddr[6];
    unsigned int    IpAddr;
    QString         PhoneNumber;
    QString         Department;
};

struct GroupInfoCard :public InfoCard{
    QList<MemberInfoCard> Members;
};

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

    void Start();
    void Stop();
    void Restart();
    //void run() override;
private:
    struct RecvDataInfo{
        QHostAddress HostAddr;
        unsigned short SrcPort;
        unsigned short DesPort;
        QByteArray Data;
    };
public slots:

private slots:
    void Slot_Connected();
    void Slot_Disconnected();
    void Slot_Error(QAbstractSocket::SocketError socketError);
    void Slot_NewConnection();

    void Slot_TCPreadyRead();
    void Slot_UDPreadyRead();

    void Slot_MsgTimerTimeout();
private:
    void RecvData(QByteArray Data,unsigned int SrcIP,unsigned short SrcPort);
    void SendData(QByteArray Data,unsigned int DesIP,unsigned short DesPort);
    void SendData(QByteArray Data,QHostAddress HostAddr,unsigned short DesPort);

    void SendHello();
    void SendOnlineState(unsigned int State);
    void SendIpMacInquiry();
    void FindIp(QString MACAddr);

    QString UIntToStrIp(unsigned int Ip);
    unsigned int StrIpToUInt(QString StrIP);

private:
    unsigned short SystemInfoTransmissionPort;
    unsigned short FileTransmissionPort;
    unsigned short MessagePort;

    unsigned int OrganizationNumber;
    QHostAddress SystemInfoMulticastGroup;
    QHostAddress MessageMulticastGroup;
    QHostAddress FileMulticastGroup;

    QTcpServer TCP_FileRecv;
    QUdpSocket UDP_FileRecv;
    QUdpSocket UDP_SystemInfo;
    QUdpSocket UDP_MessageRecv;

    QMap <QTcpSocket *, QFile>  Tcp_File;
    QMap <QString,QString>      FileID_Name;
    QMap <QString,QString>      FileID_Path;
    QMutex                      UDPRecvData_Mutex;
    QList<RecvDataInfo>         UDPRecvData;

    QTimer MsgTimeOut;
    QMap<QString, unsigned int> MessageID_SendTime;

    //表决

    //Mac_IP
    QMap<QString,unsigned int>  LocalMac_IP;
    QMap<QString,unsigned int>  Mac_IP;
};

#endif // INFOMATIONCENTER_H
