#include "PluginManager.h"

#include <QDir>
#include <QString>
#include <QLibrary>

#include <json/json.h>

#include "Log.h"
#include "../DTBPluginInterfaceExport.h"


std::mutex PluginManager::CreatInstance_Mutex;
PluginManager* PluginManager::m_ClassInstance = nullptr;

void PluginManager::DestoryInstance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        return;
    }
    delete m_ClassInstance;
    return;
}

PluginManager* PluginManager::Instance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr) {
        m_ClassInstance = new PluginManager;
    }
    return m_ClassInstance;
}

int PluginManager::PluginInfo(std::string PluginID, std::string& info)
{
    auto iterator = m_PluginInstances.find(PluginID);
    if (iterator == m_PluginInstances.end()) {
        return -1;
    }
    m_PluginInstances[PluginID]->GetPluginInfo(info);
    return 0;
}

int PluginManager::PluginType(std::string PluginID, std::string &type)
{
    auto iterator = m_PluginInstances.find(PluginID);
    if (iterator == m_PluginInstances.end()) {
        return -1;
    }

    std::string JsonStr;
    Json::Reader Reader;
    Json::Value Root;

    m_PluginInstances[PluginID]->GetPluginInfo(JsonStr);

    if (JsonStr != "" && Reader.parse(JsonStr, Root) == false) {
        return -2;
    }
    type = Root["PluginType"].asString();
    return 0;
}

int PluginManager::PluginList(std::list<std::string> &list)
{
    for (auto i = m_PluginInstances.begin(); i != m_PluginInstances.end(); i++) {
        list.push_back(i->first);
    }
    return 0;
}

int PluginManager::PluginLoad(std::string FileName)
{
    QLibrary * DllLoader = new QLibrary(FileName.c_str());
    if (DllLoader->load() == false){
        Warning(DllLoader->errorString().toStdString(), __FILE__, __LINE__);
        delete DllLoader;
        return -1;
    }

    auto CreatInstanceFuncPtr = DllLoader->resolve("GetDTBPluginInterfaceExport");
    if (CreatInstanceFuncPtr == nullptr) {
        bool Unload = DllLoader->unload();
        delete DllLoader;
        return -2;
    }
    auto DestoryInstanceFuncPtr = DllLoader->resolve("DestoryDTBPluginInterfaceExport");
    if (DestoryInstanceFuncPtr == nullptr) {
        bool Unload = DllLoader->unload();
        delete DllLoader;
        return -3;
    }

    auto CreatInstanceCall = (DTBPluginInterfaceExport * (*)())CreatInstanceFuncPtr;
    auto PluginInstance = CreatInstanceCall();
    if (PluginInstance == nullptr) {
        bool Unload = DllLoader->unload();
        delete DllLoader;
        return -3;
    }
    std::string JsonStr;
    PluginInstance->GetPluginInfo(JsonStr);

    Json::Reader Reader;
    Json::Value Root;

    if (JsonStr != "" && Reader.parse(JsonStr, Root) == false) {
        bool Unload = DllLoader->unload();
        delete DllLoader;
        return -4;
    }

    std::string PluginID = Root["PluginID"].asString();

    if (m_PluginInstances.find(PluginID) != m_PluginInstances.end()) {
        auto DestoryInstanceFunCall = (void (*)(DTBPluginInterfaceExport*))DestoryInstanceFuncPtr;
        DestoryInstanceFunCall(PluginInstance);
        bool Unload = DllLoader->unload();
        delete DllLoader;
        return -5;
    }

    m_PluginInstances[PluginID] = PluginInstance;
    m_PluginDllLoader[PluginID] = DllLoader;

    PluginInstance->Trace = std::bind(&Log::Trace, PluginID, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    PluginInstance->Debug = std::bind(&Log::Debug, PluginID, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    PluginInstance->Information = std::bind(&Log::Information, PluginID, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    PluginInstance->Notice = std::bind(&Log::Notice, PluginID, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    PluginInstance->Warning = std::bind(&Log::Warning, PluginID, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    PluginInstance->Error = std::bind(&Log::Error, PluginID, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    PluginInstance->Critical = std::bind(&Log::Critical, PluginID, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    PluginInstance->Fatal = std::bind(&Log::Fatal, PluginID, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    return 0;
}

int PluginManager::PluginUnLoad(std::string PluginID)
{
    if (m_PluginDllLoader.find(PluginID) == m_PluginDllLoader.end()) {
        return -1;
    }
    auto& DllLoader = m_PluginDllLoader[PluginID];
    auto DestoryInstanceFuncPtr = DllLoader->resolve("DestoryDTBPluginInterfaceExport");
    if (DestoryInstanceFuncPtr == nullptr) {
        delete DllLoader;
        DllLoader->unload();
        return -2;
    }
    auto InstancePtr = m_PluginInstances[PluginID];
    auto DestoryInstanceFunCall = (void (*)(DTBPluginInterfaceExport*))DestoryInstanceFuncPtr;
    DestoryInstanceFunCall(InstancePtr);
    bool Unload = DllLoader->unload();
    delete DllLoader;
    return 0;
}

void PluginManager::LoadPluginDir(std::string FileName)
{
    QDir PluginsDirectory;
    PluginsDirectory.setPath(FileName.c_str());
    if (PluginsDirectory.exists() == false) {
        Warning("the libPath is: " + FileName, __FILE__, __LINE__);
        return;
    }
    QStringList PluginFiles;
    QStringList FileFilters;
    FileFilters.clear();

#ifdef Q_OS_LINUX
    FileFilters << "*.so";
#endif
#ifdef Q_OS_WIN32
    FileFilters << "*.dll";
#endif

    //遍历目录
    PluginFiles = PluginsDirectory.entryList(FileFilters, QDir::Files | QDir::Readable, QDir::Name);
    foreach(auto var, PluginFiles) {
        auto LoadRet = PluginLoad(QString(PluginsDirectory.path() + '/' + var).toStdString());
        Information("加载插件" + var.toStdString(), __FILE__, __LINE__);
        if (LoadRet != 0) {
            Error("加载失败" + var.toStdString(), __FILE__, __LINE__);
            continue;
        }
        Information("加载成功" + var.toStdString() + var.toStdString() + std::to_string(LoadRet), __FILE__, __LINE__);
    }
}

std::tuple<int, std::string> PluginManager::APIRequest(std::string API_Name, std::vector<void *> Argv)
{
    return std::make_tuple(-1, "");
}

std::tuple<int, std::string> PluginManager::APIRequest(std::string PluginID, std::string API_Name, std::vector<void *> Argv)
{
    auto iterator = m_PluginInstances.find(PluginID);
    if (iterator == m_PluginInstances.end()) {
        return std::make_tuple(-1, "");
    }
    return m_PluginInstances[PluginID]->APIRequest(API_Name, Argv);
}

PluginManager::PluginManager()
{
    Log::Instance();

    Trace = std::bind(&Log::Warning,"PluginManager", std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    Debug = std::bind(&Log::Debug,"PluginManager", std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    Information = std::bind(&Log::Information,"PluginManager", std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    Notice = std::bind(&Log::Notice,"PluginManager", std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    Warning = std::bind(&Log::Warning,"[PluginManager", std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    Error = std::bind(&Log::Error,"PluginManager", std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    Critical = std::bind(&Log::Error,"[PluginManager", std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    Fatal = std::bind(&Log::Error,"PluginManager", std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

PluginManager::~PluginManager()
{
}
