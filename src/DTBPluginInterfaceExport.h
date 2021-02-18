#ifndef DTBPLUGINNTERFACEEXPORT_H
#define DTBPLUGINNTERFACEEXPORT_H

#include <vector>
#include <iostream>
#include <functional>

class DTBPluginInterfaceExport {

public:
    //获取接口信息
    virtual void GetPluginInfo(std::string &jsonInfo) = 0;

    //接口注册
    std::function<std::tuple<int, std::string>(std::string API_Name)> APIRegister;
    std::function<std::tuple<int, std::string>(std::string API_Name)> APIUnRegister;

    //接口调用
    virtual std::tuple<int, std::string> APIRequest(std::string API_Name, std::vector<void *> Argv) = 0;

    //日志
    std::function<void(std::string content, const char* file, int Line)> Trace;
    std::function<void(std::string content, const char* file, int Line)> Debug;
    std::function<void(std::string content, const char* file, int Line)> Information;
    std::function<void(std::string content, const char* file, int Line)> Notice;
    std::function<void(std::string content, const char* file, int Line)> Warning;
    std::function<void(std::string content, const char* file, int Line)> Error;
    std::function<void(std::string content, const char* file, int Line)> Critical;
    std::function<void(std::string content, const char* file, int Line)> Fatal;
};
#endif // DTBPLUGINNTERFACEEXPORT_H
