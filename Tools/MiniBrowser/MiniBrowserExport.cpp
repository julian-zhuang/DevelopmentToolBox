#include "MiniBrowserExport.h"
#include "MiniBrowserUI.h"
#include <QDir>
#include <QTabWidget>
#include <QSettings>
#include <BrowserWidget.h>
#include <QtWebEngineWidgets/QtWebEngineWidgets>

std::mutex MiniBrowserInterFace::CreatInstance_Mutex;
MiniBrowserInterFace* MiniBrowserInterFace::m_ClassInstance = nullptr;

void MiniBrowserInterFace::DestoryInstance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        return;
    }
    delete m_ClassInstance;
    return;

}

MiniBrowserInterFace *MiniBrowserInterFace::Instance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        m_ClassInstance = new MiniBrowserInterFace;
    }
    return m_ClassInstance;
}

void MiniBrowserInterFace::GetPluginInfo(std::string &jsonInfo)
{
    QJsonObject Obj;
    Obj.insert("PluginID", "MiniBrowser");
    Obj.insert("PluginType", "GUI");
    jsonInfo = QJsonDocument(Obj).toJson().toStdString();

}

std::tuple<int, std::string> MiniBrowserInterFace::APIRequest(std::string API_Name, std::vector<void *> Argv)
{
    if (API_Name == "GetWidget") {
        *((QWidget**)(Argv[0])) = new MiniBrowserUI(*((QWidget**)(Argv[1])));
        return std::make_tuple(0, "ok");
    }
    return std::make_tuple(-1, API_Name + "不存在");
}

MiniBrowserInterFace::MiniBrowserInterFace()
{

}

MiniBrowserInterFace::~MiniBrowserInterFace()
{

}

DTBPluginInterfaceExport* GetDTBPluginInterfaceExport()
{
    return MiniBrowserInterFace::Instance();
}

void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport* Ptr)
{
    delete (MiniBrowserInterFace*)Ptr;
}
