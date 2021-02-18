#include "PostService.h"

#include <QUuid>
#include <QTimer>
#include <QtEndian>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

PostService* PostService::m_ClassInstance = nullptr;
std::mutex PostService::CreatInstance_Mutex;

#pragma execution_character_set("utf-8")

void PostService::DestoryInstance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr){
        return;
    }
    delete m_ClassInstance;
    m_ClassInstance = nullptr;
    return;
}

PostService *PostService::Instance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr){
        m_ClassInstance = new PostService;
    }
    return m_ClassInstance;
}

void PostService::SocketSendData(QTcpSocket *Socket, QByteArray *data)
{
    auto SendLenth = Socket->write(*data);
    data->remove(0, SendLenth);
    if (data->length() > 0){
        QTimer::singleShot(100, [this, Socket, data]{
            SocketSendData(Socket, data);
        });
    }
}

int PostService::SendStringMessage(QString DstId, QString str, QString &MsgId, QString Model)
{
    if (Model == "TCP"){
        QTcpSocket *Socket = nullptr;
        GetTcpsocket(DstId, Socket);
        if (Socket == nullptr){
            return -1;
        }
        unsigned int Lenth = 0;
        MsgId = QUuid::createUuid().toString();

        QJsonObject Msg;
        Msg.insert("Type", "CHAT_STRING_MSG");
        Msg.insert("SrcID", m_LocalID);
        Msg.insert("MsgID", MsgId);
        Msg.insert("Content", str);
        Msg.insert("Date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));

        QByteArray &WaitSendData = ID_WaitSendData[DstId];
        QByteArray MsgInfo = QJsonDocument(Msg).toJson();
        Lenth = MsgInfo.length();
        Lenth = qToLittleEndian<quint32>(Lenth);
        WaitSendData.append((char *)&Lenth, sizeof (Lenth));
        WaitSendData.append(MsgInfo);
        SocketSendData(Socket, &WaitSendData);
        return 0;
    }
    if (Model == "UDP"){

        return 0;
    }
    return -1;
}

int PostService::SendImageMessage(QString DstId, QString path, QString &MsgId, QString Model)
{
    if (Model == "TCP"){
        QTcpSocket *Socket = nullptr;
        GetTcpsocket(DstId, Socket);
        if (Socket == nullptr){
            return -1;
        }
        unsigned int Lenth = 0;
        MsgId = QUuid::createUuid().toString();
        QString SourceID = QUuid::createUuid().toString();
        MsgID_SourceID[MsgId] = SourceID;
        SourceID_Path[SourceID] = path;

        QJsonObject Msg;
        Msg.insert("Type", "CHAT_IMAGE_MSG");
        Msg.insert("SrcID", m_LocalID);
        Msg.insert("MsgID", MsgId);
        Msg.insert("SourceID", SourceID);
        Msg.insert("Date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));

        QByteArray &WaitSendData = ID_WaitSendData[DstId];
        QByteArray MsgInfo = QJsonDocument(Msg).toJson();
        Lenth = MsgInfo.length();
        Lenth = qToLittleEndian<quint32>(Lenth);
        WaitSendData.append((char *)&Lenth, sizeof (Lenth));
        WaitSendData.append(MsgInfo);
        SocketSendData(Socket, &WaitSendData);
        return 0;
    }
    if (Model == "UDP"){

        return 0;
    }
    return -1;
}

int PostService::SendFileMessage(QString DstId, QString path, QString &MsgId, QString Model)
{
    if (Model == "TCP"){
        QTcpSocket *Socket = nullptr;
        GetTcpsocket(DstId, Socket);
        if (Socket == nullptr){
            return -1;
        }
        unsigned int Lenth = 0;
        MsgId = QUuid::createUuid().toString();
        QString SourceID = QUuid::createUuid().toString();
        MsgID_SourceID[MsgId] = SourceID;
        SourceID_Path[SourceID] = path;

        QJsonObject Msg;
        Msg.insert("Type", "CHAT_FILE_MSG");
        Msg.insert("SrcID", m_LocalID);
        Msg.insert("MsgID", MsgId);
        Msg.insert("SourceID", SourceID);
        Msg.insert("Date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));

        QByteArray &WaitSendData = ID_WaitSendData[DstId];
        QByteArray MsgInfo = QJsonDocument(Msg).toJson();
        Lenth = MsgInfo.length();
        Lenth = qToLittleEndian<quint32>(Lenth);
        WaitSendData.append((char *)&Lenth, sizeof (Lenth));
        WaitSendData.append(MsgInfo);
        SocketSendData(Socket, &WaitSendData);
        return 0;
    }
    if (Model == "UDP"){

        return 0;
    }
    return -1;
}

int PostService::SendAudioMessage(QString DstId, QString path, QString &MsgId, QString Model)
{
    if (Model == "TCP"){
        QTcpSocket *Socket = nullptr;
        GetTcpsocket(DstId, Socket);
        if (Socket == nullptr){
            return -1;
        }
        unsigned int Lenth = 0;
        MsgId = QUuid::createUuid().toString();
        QString SourceID = QUuid::createUuid().toString();
        MsgID_SourceID[MsgId] = SourceID;
        SourceID_Path[SourceID] = path;

        QJsonObject Msg;
        Msg.insert("Type", "CHAT_AUDIO_MSG");
        Msg.insert("SrcID", m_LocalID);
        Msg.insert("MsgID", MsgId);
        Msg.insert("SourceID", SourceID);
        Msg.insert("Date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));

        QByteArray &WaitSendData = ID_WaitSendData[DstId];
        QByteArray MsgInfo = QJsonDocument(Msg).toJson();
        Lenth = MsgInfo.length();
        Lenth = qToLittleEndian<quint32>(Lenth);
        WaitSendData.append((char *)&Lenth, sizeof (Lenth));
        WaitSendData.append(MsgInfo);
        SocketSendData(Socket, &WaitSendData);
        return 0;
    }
    if (Model == "UDP"){

        return 0;
    }
    return -1;
}

int PostService::SendVideoMessage(QString DstId, QString path, QString &MsgId, QString Model)
{
    if (Model == "TCP"){
        QTcpSocket *Socket = nullptr;
        GetTcpsocket(DstId, Socket);
        if (Socket == nullptr){
            return -1;
        }
        unsigned int Lenth = 0;
        MsgId = QUuid::createUuid().toString();
        QString SourceID = QUuid::createUuid().toString();
        MsgID_SourceID[MsgId] = SourceID;
        SourceID_Path[SourceID] = path;

        QJsonObject Msg;
        Msg.insert("Type", "CHAT_VIDEO_MSG");
        Msg.insert("SrcID", m_LocalID);
        Msg.insert("MsgID", MsgId);
        Msg.insert("SourceID", SourceID);
        Msg.insert("Date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));

        QByteArray &WaitSendData = ID_WaitSendData[DstId];
        QByteArray MsgInfo = QJsonDocument(Msg).toJson();
        Lenth = MsgInfo.length();
        Lenth = qToLittleEndian<quint32>(Lenth);
        WaitSendData.append((char *)&Lenth, sizeof (Lenth));
        WaitSendData.append(MsgInfo);
        SocketSendData(Socket, &WaitSendData);
        return 0;
    }
    if (Model == "UDP"){

        return 0;
    }
    return -1;
}

int PostService::SendResourceRequest(QString DstId, QString &SourceId, QString Model)
{
    if (Model == "TCP"){
        QTcpSocket *Socket = nullptr;
        GetTcpsocket(DstId, Socket);
        if (Socket == nullptr){
            return -1;
        }
        unsigned int Lenth = 0;

        QJsonObject Msg;
        Msg.insert("Type", "CHAT_SOURCE_REQUEST");
        Msg.insert("SrcID", m_LocalID);
        Msg.insert("SourceId", SourceId);
        Msg.insert("Date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));

        QByteArray &WaitSendData = ID_WaitSendData[DstId];
        QByteArray MsgInfo = QJsonDocument(Msg).toJson();
        Lenth = MsgInfo.length();
        Lenth = qToLittleEndian<quint32>(Lenth);
        WaitSendData.append((char *)&Lenth, sizeof (Lenth));
        WaitSendData.append(MsgInfo);
        SocketSendData(Socket, &WaitSendData);
        return 0;
    }
    if (Model == "UDP"){

        return 0;
    }
    return -1;
}

int PostService::SendMessageHaveRead(QString DstId, QString &MsgId, QString Model)
{
    QJsonObject Msg;
    Msg.insert("Type", "CHAT_HAVE_READ");
    Msg.insert("SrcID", m_LocalID);
    Msg.insert("MsgID", MsgId);
    Msg.insert("Date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
    QByteArray MsgInfo = QJsonDocument(Msg).toJson();

    if (Model == "TCP"){
        QTcpSocket *Socket = nullptr;
        GetTcpsocket(DstId, Socket);
        if (Socket == nullptr){
            return -1;
        }
        unsigned int Lenth = 0;

        QByteArray &WaitSendData = ID_WaitSendData[DstId];
        Lenth = MsgInfo.length();
        Lenth = qToLittleEndian<quint32>(Lenth);
        WaitSendData.append((char *)&Lenth, sizeof (Lenth));
        WaitSendData.append(MsgInfo);
        SocketSendData(Socket, &WaitSendData);
        return 0;
    }
    if (Model == "UDP"){
        QHostAddress Addr;
        quint16 Port;
        std::tie(Addr, Port) = m_ID_Addr_Port[DstId];

        QUdpSocket Socket;
        Socket.writeDatagram(MsgInfo, Addr, Port);
        if(Socket.waitForBytesWritten(1000) == false){
            return -1;
        }
        return 0;
    }
    return -1;
}
#include <QUdpSocket>
void PostService::SetLocalAddr(QString Id, QHostAddress Addr, quint16 port)
{
    m_LocalID = Id;
    m_ID_Addr_Port[Id] = std::make_tuple(Addr, port);

    QTcpServer* TcpServer = new QTcpServer(this);
    connect(TcpServer, &QTcpServer::newConnection, [this, TcpServer] {
        QTcpSocket* TcpScoket = TcpServer->nextPendingConnection();
        connect(TcpScoket, &QTcpSocket::connected, this, &PostService::Slot_Connected);
        connect(TcpScoket, &QTcpSocket::disconnected, this, &PostService::Slot_Disconnected);
        connect(TcpScoket, &QTcpSocket::readyRead, this, &PostService::Slot_ReadyRead);
        });

    TcpServer->listen(Addr, port);

    QUdpSocket* UdpSocket = new QUdpSocket(this);
}

void PostService::AddRemoteAddr(QString Id, QHostAddress Addr, quint16 port)
{
    m_ID_Addr_Port[Id] = std::make_tuple(Addr, port);
}

void PostService::DelRemoteAddr(QString Id)
{
    if (m_ID_Addr_Port.contains(Id) == true){
        m_ID_Addr_Port.remove(Id);
    }
}

void PostService::GetTcpsocket(QString Id, QTcpSocket *&ptr)
{
    QHostAddress Addr;
    quint16 Port;
    std::tie(Addr, Port) = m_ID_Addr_Port[Id];

    if (Addr.isNull() == true){
        ptr = nullptr;
        return;
    }

    if (ptr == nullptr){
        ptr = new QTcpSocket;
    }

    connect(ptr, &QTcpSocket::connected, [this, ptr, Id]{

    });
    connect(ptr, &QTcpSocket::disconnected, [this, ptr]{

    });
    connect(ptr, &QTcpSocket::readyRead,  [this, ptr]{
        QByteArray Buffer = ptr->readAll();
        unsigned int DataLenth = *(unsigned int *)Buffer.data();
        DataLenth = qFromLittleEndian<quint32>(DataLenth);

        if (DataLenth > Buffer.length() - 4){
            return;
        }
        QJsonObject JsonObj = QJsonDocument::fromJson(Buffer.mid(0, DataLenth)).object();
        auto Type = JsonObj.value("Type").toString();
        auto SrcID = JsonObj.value("SrcID").toString();

        if (Type == "CHAT_STRING_MSG"){
            QString Str = JsonObj.value("Content").toString();
            QString MsgId = JsonObj.value("MsgID").toString();
            emit RecvStringMessage(SrcID, Str, MsgId);
            return;
        }
        if (Type == "CHAT_IMAGE_MSG"){
            QString MsgId = JsonObj.value("MsgID").toString();
            QString SourceID = JsonObj.value("SourceID").toString();
            emit RecvStringMessage(SrcID, SourceID, MsgId);
            return;
        }
        if (Type == "CHAT_FILE_MSG"){
            QString MsgId = JsonObj.value("MsgID").toString();
            QString SourceID = JsonObj.value("SourceID").toString();
            emit RecvStringMessage(SrcID, SourceID, MsgId);
            return;
        }
        if (Type == "CHAT_AUDIO_MSG"){
            QString MsgId = JsonObj.value("MsgID").toString();
            QString SourceID = JsonObj.value("SourceID").toString();
            emit RecvStringMessage(SrcID, SourceID, MsgId);
            return;
        }
        if (Type == "CHAT_VIDEO_MSG"){
            QString MsgId = JsonObj.value("MsgID").toString();
            QString SourceID = JsonObj.value("SourceID").toString();
            emit RecvStringMessage(SrcID, SourceID, MsgId);
            return;
        }
        if (Type == "CHAT_SOURCE_REQUEST"){
            return;
        }
        if (Type == "CHAT_SOURCE_REPLY"){
            return;
        }
        if (Type == "CHAT_GET_ONLINE_STATE"){
            return;
        }
        if (Type == "CHAT_HAVE_READ"){
            QString MsgId = JsonObj.value("MsgID").toString();
            emit RecvMessageHaveRead(SrcID, MsgId);
            return;
        }
    });
    ptr->connectToHost(Addr, Port);
    if (ptr->waitForConnected(1000) == false){
        delete ptr;
        ptr = nullptr;
    }
    ID_TcpSocket[Id] = ptr;
}

void PostService::Slot_Connected()
{
}

void PostService::Slot_Disconnected()
{
}

void PostService::Slot_ReadyRead()
{
    QTcpSocket* Socket = static_cast<QTcpSocket*>(sender());
    QByteArray& Buffer = Socket_RecvBuffer[Socket];
    Buffer.append(Socket->readAll());
}

PostService::PostService()
{

}

PostService::~PostService()
{

}
