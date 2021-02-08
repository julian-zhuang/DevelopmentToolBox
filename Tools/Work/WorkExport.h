#ifndef WORKLOG_H
#define WORKLOG_H

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define Q_DECL_EXPORT __declspec(dllexport)
#  define Q_DECL_IMPORT __declspec(dllimport)
#else
#  define Q_DECL_EXPORT     __attribute__((visibility("default")))
#  define Q_DECL_IMPORT     __attribute__((visibility("default")))
#endif

#if defined(WORKLOGINTERFACE_LIBRARY)
#  define WORKLOGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CHATROOMSHARED_EXPORT Q_DECL_IMPORT
#endif

#include <mutex>
#include "../../DTBPluginInterfaceExport.h"

extern "C" WORKLOGSHARED_EXPORT DTBPluginInterfaceExport * GetDTBPluginInterfaceExport();
extern "C" WORKLOGSHARED_EXPORT void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport *Ptr);

class WORKLOGSHARED_EXPORT WorkInterface : public DTBPluginInterfaceExport
{
public:
    static void DestoryInstance();
    static WorkInterface* Instance();

    //获取接口信息
    virtual void GetPluginInfo(std::string &jsonInfo) override;

    //接口调用
    virtual std::tuple<int, std::string> APIRequest(std::string API_Name, std::vector<void *> Argv) override;

protected:
    WorkInterface();
    ~WorkInterface();
    friend void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport *Ptr);

private:
    static std::mutex CreatInstance_Mutex;
    static WorkInterface* m_ClassInstance;
};

#endif // WORKLOG_H
