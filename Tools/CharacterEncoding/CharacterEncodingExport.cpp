#include "CharacterEncodingExport.h"
#include "CharacterEncodingUI.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

std::mutex CharacterEncodingExport::CreatInstance_Mutex;
CharacterEncodingExport* CharacterEncodingExport::m_ClassInstance = nullptr;

std::tuple<int, std::string> CharacterEncodingExport::APIRequest(std::string API_Name, std::vector<void*> Argv)
{
    if (API_Name == "GetWidget") {
        *((QWidget**)(Argv[0])) = new CharacterEncodingUI(*((QWidget**)(Argv[1])));
        return std::make_tuple(0, "ok");
    }
    return std::make_tuple(-1, API_Name + "不存在");
}

CharacterEncodingExport::CharacterEncodingExport()
{
}

CharacterEncodingExport::~CharacterEncodingExport()
{
}

void CharacterEncodingExport::DestoryInstance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        return;
    }
    delete m_ClassInstance;
    return;
}

CharacterEncodingExport* CharacterEncodingExport::Instance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        m_ClassInstance = new CharacterEncodingExport;
    }
    return m_ClassInstance;
}

void CharacterEncodingExport::GetPluginInfo(std::string& jsonInfo)
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
    return CharacterEncodingExport::Instance();
}

void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport* Ptr)
{
    delete (CharacterEncodingExport*)Ptr;
}
