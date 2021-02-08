#include "RaspberryPiGPIOExport.h"
#include <RaspberryPiGPIOUI.h>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

std::mutex RaspberryPiGPIOInterface::CreatInstance_Mutex;
RaspberryPiGPIOInterface* RaspberryPiGPIOInterface::m_ClassInstance = nullptr;

void RaspberryPiGPIOInterface::DestoryInstance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        return;
    }
    delete m_ClassInstance;
    return;
}

RaspberryPiGPIOInterface *RaspberryPiGPIOInterface::Instance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        m_ClassInstance = new RaspberryPiGPIOInterface;
    }
    return m_ClassInstance;
}

void RaspberryPiGPIOInterface::GetPluginInfo(std::string &jsonInfo)
{
    QJsonObject Obj;
    Obj.insert("PluginID", "RaspberryPiGPIO");
    Obj.insert("PluginType", "GUI");
    jsonInfo = QJsonDocument(Obj).toJson().toStdString();
}

std::tuple<int, std::string> RaspberryPiGPIOInterface::APIRequest(std::string API_Name, std::vector<void *> Argv)
{
    if (API_Name == "GetWidget") {
        *((QWidget**)(Argv[0])) = new RaspberryPiGPIOUI(*((QWidget**)(Argv[1])));
        return std::make_tuple(0, "ok");
    }
    return std::make_tuple(-1, API_Name + "不存在");
}

RaspberryPiGPIOInterface::RaspberryPiGPIOInterface()
{

}

RaspberryPiGPIOInterface::~RaspberryPiGPIOInterface()
{

}

DTBPluginInterfaceExport* GetDTBPluginInterfaceExport()
{
    return RaspberryPiGPIOInterface::Instance();
}

void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport* Ptr)
{
    delete (RaspberryPiGPIOInterface*)Ptr;
}
