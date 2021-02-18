#include "SearchFileExport.h"
#include "SearchFile.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

std::mutex SearchFileInterface::CreatInstance_Mutex;
SearchFileInterface* SearchFileInterface::m_ClassInstance = nullptr;

std::tuple<int, std::string> SearchFileInterface::APIRequest(std::string API_Name, std::vector<void*> Argv)
{
    if (API_Name == "GetWidget") {
        *((QWidget**)(Argv[0])) = new SearchFile(*((QWidget**)(Argv[1])));
        return std::make_tuple(0, "ok");
    }
    return std::make_tuple(-1, API_Name + "不存在");
}

SearchFileInterface::SearchFileInterface()
{
}

SearchFileInterface::~SearchFileInterface()
{
}

void SearchFileInterface::DestoryInstance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        return;
    }
    delete m_ClassInstance;
    return;
}

SearchFileInterface* SearchFileInterface::Instance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        m_ClassInstance = new SearchFileInterface;
    }
    return m_ClassInstance;
}

void SearchFileInterface::GetPluginInfo(std::string& jsonInfo)
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
    Obj.insert("PluginID", "SearchFile");
    Obj.insert("PluginType", "GUI");
    jsonInfo = QJsonDocument(Obj).toJson().toStdString();
}

DTBPluginInterfaceExport* GetDTBPluginInterfaceExport()
{
    return SearchFileInterface::Instance();
}

void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport* Ptr)
{
    delete (SearchFileInterface*)Ptr;
}
