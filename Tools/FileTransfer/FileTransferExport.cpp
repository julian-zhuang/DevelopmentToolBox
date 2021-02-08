#include "FileTransferExport.h"
#include <FileTransferUI.h>
#include <QDir>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

std::mutex FileTransferInterface::CreatInstance_Mutex;
FileTransferInterface* FileTransferInterface::m_ClassInstance;
void FileTransferInterface::DestoryInstance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        return;
    }
    delete m_ClassInstance;
    return;
}

FileTransferInterface *FileTransferInterface::Instance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        m_ClassInstance = new FileTransferInterface;
    }
    return m_ClassInstance;
}

void FileTransferInterface::GetPluginInfo(std::string &jsonInfo)
{
    QJsonObject Obj;
    Obj.insert("PluginID", "FileTransfer");
    Obj.insert("PluginType", "GUI");
    jsonInfo = QJsonDocument(Obj).toJson().toStdString();
}

std::tuple<int, std::string> FileTransferInterface::APIRequest(std::string API_Name, std::vector<void *> Argv)
{
    if (API_Name == "GetWidget") {
        *((QWidget**)(Argv[0])) = new FileTransferUI(*((QWidget**)(Argv[1])));
        return std::make_tuple(0, "ok");
    }
    return std::make_tuple(-1, API_Name + "不存在");
}

FileTransferInterface::FileTransferInterface()
{

}

FileTransferInterface::~FileTransferInterface()
{

}

DTBPluginInterfaceExport* GetDTBPluginInterfaceExport()
{
    return FileTransferInterface::Instance();
}

void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport* Ptr)
{
    delete (FileTransferInterface*)Ptr;
}
