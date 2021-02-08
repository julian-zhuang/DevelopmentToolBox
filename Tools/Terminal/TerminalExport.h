#ifndef TERMINALEXPORT_H
#define TERMINALEXPORT_H

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define Q_DECL_EXPORT __declspec(dllexport)
#  define Q_DECL_IMPORT __declspec(dllimport)
#else
#  define Q_DECL_EXPORT     __attribute__((visibility("default")))
#  define Q_DECL_IMPORT     __attribute__((visibility("default")))
#endif

#if defined(TERMINAL_LIBRARY)
#  define TERMINALSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TERMINALSHARED_EXPORT Q_DECL_IMPORT
#endif

#include <mutex>
#include "../../DTBPluginInterfaceExport.h"

extern "C" TERMINALSHARED_EXPORT DTBPluginInterfaceExport * GetDTBPluginInterfaceExport();
extern "C" TERMINALSHARED_EXPORT void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport *Ptr);


class TERMINALSHARED_EXPORT TerminalInterface : public DTBPluginInterfaceExport{

public:
    static void DestoryInstance();
    static TerminalInterface* Instance();

    //鑾峰彇鎺ュ彛淇℃伅
    virtual void GetPluginInfo(std::string &jsonInfo) override;

    //鎺ュ彛璋冪敤
    virtual std::tuple<int, std::string> APIRequest(std::string API_Name, std::vector<void *> Argv) override;

protected:
    friend void DestoryDTBPluginInterfaceExport(DTBPluginInterfaceExport *Ptr);
    TerminalInterface();
    ~TerminalInterface();

private:
    static std::mutex CreatInstance_Mutex;
    static TerminalInterface* m_ClassInstance;
};

#endif // TERMINALEXPORT_H
