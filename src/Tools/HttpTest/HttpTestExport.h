#ifndef HTTPTESTEXPORT_H
#define HTTPTESTEXPORT_H

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define Q_DECL_EXPORT __declspec(dllexport)
#  define Q_DECL_IMPORT __declspec(dllimport)
#else
#  define Q_DECL_EXPORT     __attribute__((visibility("default")))
#  define Q_DECL_IMPORT     __attribute__((visibility("default")))
#endif

#if defined(HTTPTES_LIBRARY)
#  define HTTPTES_EXPORT Q_DECL_EXPORT
#else
#  define HTTPTES_EXPORT Q_DECL_IMPORT
#endif

#include <mutex>
#include "../../DTBPluginInterfaceExport.h"

extern "C" HTTPTES_EXPORT DTBPluginInterfaceExport * GetDTBPluginInterfaceExport();
extern "C" HTTPTES_EXPORT void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport *Ptr);

class HTTPTES_EXPORT HttpTesExport : public DTBPluginInterfaceExport{

public:
    static void DestoryInstance();
    static HttpTesExport* Instance();

    //获取接口信息
    virtual void GetPluginInfo(std::string &jsonInfo) override;

    //接口调用
    virtual std::tuple<int, std::string> APIRequest(std::string API_Name, std::vector<void *> Argv) override;

protected:
    friend void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport *Ptr);
    HttpTesExport();
    ~HttpTesExport();

private:
    static std::mutex CreatInstance_Mutex;
    static HttpTesExport* m_ClassInstance;
};

#endif // HTTPTESTEXPORT_H
