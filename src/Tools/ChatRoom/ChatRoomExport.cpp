#include "ChatRoomExport.h"
#include "ChatRoomUI.h"
#include <QDir>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

std::mutex ChatRoomInterFace::CreatInstance_Mutex;
ChatRoomInterFace* ChatRoomInterFace::m_ClassInstance = nullptr;

void ChatRoomInterFace::DestoryInstance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        return;
    }
    delete m_ClassInstance;
    return;
}

ChatRoomInterFace *ChatRoomInterFace::Instance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        m_ClassInstance = new ChatRoomInterFace;
    }
    return m_ClassInstance;
}

void ChatRoomInterFace::GetPluginInfo(std::string &jsonInfo)
{
    QJsonObject Obj;
    Obj.insert("PluginID", "ChatRoom");
    Obj.insert("PluginType", "GUI");
    jsonInfo = QJsonDocument(Obj).toJson().toStdString();
}

std::tuple<int, std::string> ChatRoomInterFace::APIRequest(std::string API_Name, std::vector<void *> Argv)
{
    if (API_Name == "GetWidget") {
        *((QWidget**)(Argv[0])) = new ChatRoomUI(*((QWidget**)(Argv[1])));
        return std::make_tuple(0, "ok");
    }
    return std::make_tuple(-1, API_Name + "不存在");
}


DTBPluginInterfaceExport* GetDTBPluginInterfaceExport()
{
    return ChatRoomInterFace::Instance();
}

void DestoryDTBPluginInterfaceExport(ChatRoomInterFace* Ptr)
{
    delete (ChatRoomInterFace*)Ptr;
}
