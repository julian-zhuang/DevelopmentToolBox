#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <map>
#include <list>
#include <mutex>
#include <string>
#include <vector>
#include <functional>

class QLibrary;
class DTBPluginInterfaceExport;

class PluginManager
{

public:
    static void DestoryInstance();
    static PluginManager *Instance();

    // 插件
    int PluginLoad(std::string FileName);
    int PluginUnLoad(std::string PluginID);
    int PluginInfo(std::string PluginID, std::string &info);
    int PluginType(std::string PluginID, std::string &type);
    int PluginList(std::list<std::string>& list);

    void LoadPluginDir(std::string FileName);

    std::tuple<int, std::string> APIRequest(std::string API_Name, std::vector<void *> Argv);
    std::tuple<int, std::string> APIRequest(std::string PluginID, std::string API_Name, std::vector<void *> Argv);

    std::function<void (std::string content, const char* file, int Line)> Trace;
    std::function<void (std::string content, const char* file, int Line)> Debug;
    std::function<void (std::string content, const char* file, int Line)> Information;
    std::function<void (std::string content, const char* file, int Line)> Notice;
    std::function<void (std::string content, const char* file, int Line)> Warning;
    std::function<void (std::string content, const char* file, int Line)> Error;
    std::function<void (std::string content, const char* file, int Line)> Critical;
    std::function<void (std::string content, const char *file, int Line)> Fatal;

protected:
    PluginManager();
    ~PluginManager();

private:
    static std::mutex CreatInstance_Mutex;
    static PluginManager* m_ClassInstance;

    std::map<std::string, DTBPluginInterfaceExport*> m_PluginInstances;
    std::map<std::string, QLibrary*> m_PluginDllLoader;
};

#endif // PLUGINMANAGER_H
