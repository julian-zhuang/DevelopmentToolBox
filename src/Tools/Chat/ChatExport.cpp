#include "ChatExport.h"
#include <Chat.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

std::mutex ChatExport::CreatInstance_Mutex;
ChatExport* ChatExport::m_ClassInstance = nullptr;

void ChatExport::DestoryInstance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        return;
    }
    delete m_ClassInstance;
    m_ClassInstance = nullptr;
    return;
}

ChatExport *ChatExport::Instance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        m_ClassInstance = new ChatExport;
    }
    return m_ClassInstance;
}

void ChatExport::GetPluginInfo(std::string &jsonInfo)
{
    QJsonObject Obj;
    Obj.insert("PluginID", "Chat");
    Obj.insert("PluginType", "GUI");
    Obj.insert("PluginVersion", "ChatRoom");
    jsonInfo = QJsonDocument(Obj).toJson().toStdString();
}

std::tuple<int, std::string> ChatExport::APIRequest(std::string API_Name, std::vector<void *> Argv)
{
    if (API_Name == "Init") {
        return std::make_tuple(0, "ok");
    }
    if (API_Name == "GetWidget") {
        *((QWidget**)(Argv[0])) = new Chat(*((QWidget**)(Argv[1])));
        return std::make_tuple(0, "ok");
    }
    if (API_Name == "DestoryWidget") {
        Chat** Widget = (Chat**)(Argv[0]);
        delete* Widget;
        return std::make_tuple(0, "ok");
    }
    return std::make_tuple(-1, API_Name + "不存在");
}

DTBPluginInterfaceExport* GetDTBPluginInterfaceExport()
{
    return ChatExport::Instance();
}

void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport* Ptr)
{
    delete (ChatExport*)Ptr;
}

