#include "SocketTestExport.h"
#include <QPushButton>
#include <QDir>
#include "SocketTestUI.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

std::mutex SocketTestInterface::CreatInstance_Mutex;
SocketTestInterface* SocketTestInterface::m_ClassInstance = nullptr;

std::tuple<int, std::string> SocketTestInterface::APIRequest(std::string API_Name, std::vector<void*> Argv)
{
    if (API_Name == "GetWidget") {
        *((QWidget**)(Argv[0])) = new SocketTestUI(*((QWidget**)(Argv[1])));
        return std::make_tuple(0, "ok");
    }
    return std::make_tuple(-1, API_Name + "不存在");
}

SocketTestInterface::SocketTestInterface()
{
}

SocketTestInterface::~SocketTestInterface()
{
}

void SocketTestInterface::DestoryInstance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        return;
    }
    delete m_ClassInstance;
    return;
}

SocketTestInterface* SocketTestInterface::Instance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        m_ClassInstance = new SocketTestInterface;
    }
    return m_ClassInstance;
}

void SocketTestInterface::GetPluginInfo(std::string& jsonInfo)
{
    /*
    {
"Interface":[
    {
        "api":"GetWidget",
        "par":[
            {
                "type":"std::vector",
                "note":"ceshi"
            }
        ]
    },
    {
        "api":"GetWidget2",
        "par":[
            {
                "type":"std::vector",
                "note":"ceshi"
            }
        ]
    }
]
}
    */
    QJsonObject Obj;
    Obj.insert("PluginID", "SocketTest");
    Obj.insert("PluginType", "GUI");
    jsonInfo = QJsonDocument(Obj).toJson().toStdString();
}

DTBPluginInterfaceExport* GetDTBPluginInterfaceExport()
{
    return SocketTestInterface::Instance();
}

void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport* Ptr)
{
    delete (SocketTestInterface*)Ptr;
}
