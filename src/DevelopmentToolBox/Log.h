#ifndef LOG_H
#define LOG_H

//C++
#include <mutex>
#include <string>
#include <iostream>
#include <functional>

//Poco
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>
#include <Poco/AutoPtr.h>
#include <Poco/Logger.h>

class Log
{

public:
    static void DestoryInstance();
    static Log *Instance();

    //日志输出
    static void Trace(std::string model, std::string content, const char* file = nullptr, int Line = 0);
    static void Debug(std::string model, std::string content, const char* file = nullptr, int Line = 0);
    static void Information(std::string model, std::string content, const char* file = nullptr, int Line = 0);
    static void Notice(std::string model, std::string content, const char* file = nullptr, int Line = 0);
    static void Warning(std::string model, std::string content, const char* file = nullptr, int Line = 0);
    static void Error(std::string model, std::string content, const char* file = nullptr, int Line = 0);
    static void Critical(std::string model, std::string content, const char* file = nullptr, int Line = 0);
    static void Fatal(std::string model, std::string content, const char *file = nullptr, int Line = 0);

    static std::function<void(std::string)> LogOutCallBack;

protected:
    Log();
    ~Log();

private:
    class LogOutToTextCancel : public Poco::Channel
    {
    public:
        LogOutToTextCancel(std::function<void (std::string)> Func);

        void log(const Poco::Message& msg) override;

    protected:
        ~LogOutToTextCancel();

    private:
        std::function<void (std::string)> m_LogTextCallback;
    };

    struct PocoLogChannel {
        Poco::Logger* logger;
        Poco::AutoPtr<Poco::FormattingChannel> Console;
        Poco::AutoPtr<Poco::FormattingChannel> File;
        Poco::AutoPtr<Poco::FormattingChannel> LogToText;
    } m_LogChannels;

    void LogOutToTextCallBack(std::string text);

private:
    static std::mutex CreatInstance_Mutex;
    static Log* m_ClassInstance;
};

#endif // LOG_H
