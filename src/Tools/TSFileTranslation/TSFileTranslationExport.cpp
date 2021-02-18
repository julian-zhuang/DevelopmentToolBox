#include "TSFileTranslationExport.h"
#include <QDir>
#include "mainwindow.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

std::mutex TSFileTranslationInterface::CreatInstance_Mutex;
TSFileTranslationInterface* TSFileTranslationInterface::m_ClassInstance = nullptr;

std::tuple<int, std::string> TSFileTranslationInterface::APIRequest(std::string API_Name, std::vector<void*> Argv)
{
    if (API_Name == "GetWidget") {
        *((QWidget**)(Argv[0])) = new MainWindow(*((QWidget**)(Argv[1])));
        return std::make_tuple(0, "ok");
    }
    return std::make_tuple(-1, API_Name + "不存在");
}

TSFileTranslationInterface::TSFileTranslationInterface()
{
}

TSFileTranslationInterface::~TSFileTranslationInterface()
{
}

void TSFileTranslationInterface::DestoryInstance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        return;
    }
    delete m_ClassInstance;
    return;
}

TSFileTranslationInterface* TSFileTranslationInterface::Instance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        m_ClassInstance = new TSFileTranslationInterface;
    }
    return m_ClassInstance;
}

void TSFileTranslationInterface::GetPluginInfo(std::string& jsonInfo)
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
    Obj.insert("PluginID", "TSFileTranslation");
    Obj.insert("PluginType", "GUI");
    jsonInfo = QJsonDocument(Obj).toJson().toStdString();
}

DTBPluginInterfaceExport* GetDTBPluginInterfaceExport()
{
    return TSFileTranslationInterface::Instance();
}

void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport* Ptr)
{
    delete (TSFileTranslationInterface*)Ptr;
}

