#ifndef SEARCHFILEEXPORT_H
#define SEARCHFILEEXPORT_H

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define Q_DECL_EXPORT __declspec(dllexport)
#  define Q_DECL_IMPORT __declspec(dllimport)
#else
#  define Q_DECL_EXPORT     __attribute__((visibility("default")))
#  define Q_DECL_IMPORT     __attribute__((visibility("default")))
#endif

#if defined(SEARCHFILE_LIBRARY)
#  define SEARCHFILESHARED_EXPORT Q_DECL_EXPORT
#else
#  define SEARCHFILESHARED_EXPORT Q_DECL_IMPORT
#endif

#include <mutex>
#include "../../DTBPluginInterfaceExport.h"

extern "C" SEARCHFILESHARED_EXPORT DTBPluginInterfaceExport * GetDTBPluginInterfaceExport();
extern "C" SEARCHFILESHARED_EXPORT void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport *Ptr);

class SEARCHFILESHARED_EXPORT SearchFileInterface : public DTBPluginInterfaceExport{
public:
    static void DestoryInstance();
    static SearchFileInterface* Instance();

    //获取接口信息
    virtual void GetPluginInfo(std::string &jsonInfo) override;

    //接口调用
    virtual std::tuple<int, std::string> APIRequest(std::string API_Name, std::vector<void *> Argv) override;

protected:
    friend void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport *Ptr);
    SearchFileInterface();
    ~SearchFileInterface();

private:
    static std::mutex CreatInstance_Mutex;
    static SearchFileInterface* m_ClassInstance;
};

#endif // SEARCHFILEEXPORT_H
