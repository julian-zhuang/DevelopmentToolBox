#include "HttpTestExport.h"
#include "HttpTestUI.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

std::mutex HttpTesExport::CreatInstance_Mutex;
HttpTesExport* HttpTesExport::m_ClassInstance = nullptr;

void HttpTesExport::DestoryInstance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        return;
    }
    delete m_ClassInstance;
    return;
}

HttpTesExport *HttpTesExport::Instance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        m_ClassInstance = new HttpTesExport;
    }
    return m_ClassInstance;
}

void HttpTesExport::GetPluginInfo(std::string &jsonInfo)
{
    QJsonObject Obj;
    Obj.insert("PluginID", "HttpTest");
    Obj.insert("PluginType", "GUI");
    jsonInfo = QJsonDocument(Obj).toJson().toStdString();
}

std::tuple<int, std::string> HttpTesExport::APIRequest(std::string API_Name, std::vector<void *> Argv)
{
    if (API_Name == "GetWidget") {
        *((QWidget**)(Argv[0])) = new HttpTestUI(*((QWidget**)(Argv[1])));
        return std::make_tuple(0, "ok");
    }
    return std::make_tuple(-1, API_Name + "不存在");
}

HttpTesExport::HttpTesExport()
{
}

HttpTesExport::~HttpTesExport()
{

}
DTBPluginInterfaceExport* GetDTBPluginInterfaceExport()
{
    return HttpTesExport::Instance();
}

void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport* Ptr)
{
    delete (HttpTesExport*)Ptr;
}

