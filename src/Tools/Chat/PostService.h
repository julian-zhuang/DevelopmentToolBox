#ifndef POSTSERVICE_H
#define POSTSERVICE_H

#include <QMap>
#include <QObject>
#include <QString>
#include <QHostAddress>

#include <QTcpSocket>
#include <QUdpSocket>
#include <QTcpServer>

#include <mutex>
#include <tuple>
#include <memory>
#include <iostream>

class PostService : public QObject
{
    Q_OBJECT

signals:
    void RecvStringMessage      (QString SrcId, QString str,  QString MsgId);
    void RecvImageMessage       (QString SrcId, QString SourceID, QString MsgId);
    void RecvFileMessage        (QString SrcId, QString SourceID, QString MsgId);
    void RecvAudioMessage       (QString SrcId, QString SourceID, QString MsgId);
    void RecvVideoMessage       (QString SrcId, QString SourceID, QString MsgId);
    void RecvResourceSuccess    (QString SrcId, QString SourceID, QString MsgId);
    void RecvMessageHaveRead    (QString SrcId, QString MsgId);

public:
    static void DestoryInstance();
    static PostService *Instance();

    int SendStringMessage      (QString DstId, QString str,  QString &MsgId, QString Model = "TCP");
    int SendImageMessage       (QString DstId, QString path, QString &MsgId, QString Model = "TCP");
    int SendFileMessage        (QString DstId, QString path, QString &MsgId, QString Model = "TCP");
    int SendAudioMessage       (QString DstId, QString path, QString &MsgId, QString Model = "TCP");
    int SendVideoMessage       (QString DstId, QString path, QString &MsgId, QString Model = "TCP");
    int SendResourceRequest    (QString DstId, QString &SourceId, QString Model = "TCP");
    int SendMessageHaveRead    (QString DstId, QString &MsgId, QString Model = "TCP");

    void SetLocalAddr          (QString Id, QHostAddress Addr, quint16 port);
    void AddRemoteAddr         (QString Id, QHostAddress Addr, quint16 port);
    void DelRemoteAddr         (QString Id);

    void GetTcpsocket(QString Id, QTcpSocket *&ptr);
    void SocketSendData(QTcpSocket * socket, QByteArray *data);
    
public:
    void Slot_Connected();
    void Slot_Disconnected();
    void Slot_ReadyRead();

public:
    PostService();
    ~PostService();

private:
    static PostService* m_ClassInstance;
    static std::mutex CreatInstance_Mutex;

    QString m_LocalID;
    QMap<QString, std::tuple<QHostAddress, quint16>> m_ID_Addr_Port;
    QMap<QString, QTcpSocket *> ID_TcpSocket;
    QMap<QString, QByteArray> ID_RecvBuffer;
    QMap<QString, QByteArray> ID_WaitSendData;
    QMap<QString, QString> MsgID_SourceID;
    QMap<QString, QString> SourceID_Path;
    QMap<QTcpSocket*, QByteArray> Socket_RecvBuffer;
};

#endif // POSTSERVICE_H
