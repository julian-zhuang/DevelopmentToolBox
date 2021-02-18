#include "WorkExport.h"
#include <WorkUI.h>
#include <QDir>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

std::mutex WorkInterface::CreatInstance_Mutex;
WorkInterface* WorkInterface::m_ClassInstance = nullptr;

std::tuple<int, std::string> WorkInterface::APIRequest(std::string API_Name, std::vector<void*> Argv)
{
    if (API_Name == "GetWidget") {
        *((QWidget**)(Argv[0])) = new WorkUI(*((QWidget**)(Argv[1])));
        return std::make_tuple(0, "ok");
    }
    return std::make_tuple(-1, API_Name + "不存在");
}

WorkInterface::WorkInterface()
{
}

WorkInterface::~WorkInterface()
{
}

void WorkInterface::DestoryInstance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        return;
    }
    delete m_ClassInstance;
    return;
}

WorkInterface* WorkInterface::Instance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        m_ClassInstance = new WorkInterface;
    }
    return m_ClassInstance;
}

void WorkInterface::GetPluginInfo(std::string& jsonInfo)
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
    Obj.insert("PluginID", "CharacterEncoding");
    Obj.insert("PluginType", "GUI");
    jsonInfo = QJsonDocument(Obj).toJson().toStdString();
}

DTBPluginInterfaceExport* GetDTBPluginInterfaceExport()
{
    return WorkInterface::Instance();
}

void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport* Ptr)
{
    delete (WorkInterface*)Ptr;
}
