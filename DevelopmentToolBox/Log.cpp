#include "Log.h"

#include <Poco/AutoPtr.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/Message.h>
#include <Poco/LogStream.h>
#include <Poco/FileChannel.h>
#include <Poco/SyslogChannel.h>
#include <Poco/SplitterChannel.h>

#include <QCoreApplication>
#include <QDir>

Log* Log::m_ClassInstance = nullptr;
std::mutex Log::CreatInstance_Mutex;
std::function<void(std::string)> Log::LogOutCallBack = nullptr;

void Log::DestoryInstance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr){
        return;
    }
    delete m_ClassInstance;
    return;
}

Log *Log::Instance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr){
        m_ClassInstance = new Log;
    }
    return m_ClassInstance;
}

void Log::Trace(std::string model, std::string content, const char* file, int Line)
{
    if (m_ClassInstance != nullptr) {
        m_ClassInstance->m_LogChannels.logger->trace('['+ model +']' + content, file, Line);
    }
}

void Log::Debug(std::string model, std::string content, const char* file, int Line)
{
    if (m_ClassInstance != nullptr) {
        m_ClassInstance->m_LogChannels.logger->debug('['+ model +']' + content, file, Line);
    }
}

void Log::Information(std::string model, std::string content, const char* file, int Line)
{
    if (m_ClassInstance != nullptr) {
        m_ClassInstance->m_LogChannels.logger->information('['+ model +']' + content, file, Line);
    }
}

void Log::Notice(std::string model, std::string content, const char* file, int Line)
{
    if (m_ClassInstance != nullptr) {
        m_ClassInstance->m_LogChannels.logger->notice('['+ model +']' + content, file, Line);
    }
}

void Log::Warning(std::string model, std::string content, const char* file, int Line)
{
    if (m_ClassInstance != nullptr) {
        m_ClassInstance->m_LogChannels.logger->warning('['+ model +']' + content, file, Line);
    }
}

void Log::Error(std::string model, std::string content, const char* file, int Line)
{
    if (m_ClassInstance != nullptr) {
        m_ClassInstance->m_LogChannels.logger->error('['+ model +']' + content, file, Line);
    }
}

void Log::Critical(std::string model, std::string content, const char* file, int Line)
{
    if (m_ClassInstance != nullptr) {
        m_ClassInstance->m_LogChannels.logger->critical('['+ model +']' + content, file, Line);
    }
}

void Log::Fatal(std::string model, std::string content, const char* file, int Line)
{
    if (m_ClassInstance != nullptr) {
        m_ClassInstance->m_LogChannels.logger->fatal('['+ model +']' + content, file, Line);
    }
}

Log::Log()
{
    QDir dir;
    dir.mkdir(QDir::currentPath() + "/log");
    Poco::SplitterChannel* SplotterChannel = new Poco::SplitterChannel();
    m_LogChannels.logger = &(Poco::Logger::create(QCoreApplication::applicationName().toStdString(), SplotterChannel));

    Poco::AutoPtr<Poco::PatternFormatter> Format = new Poco::PatternFormatter("[%P][%L%Y-%m-%d %H:%M:%S:%i][%p]%t");
    m_LogChannels.Console = new Poco::FormattingChannel(Format, new Poco::ConsoleChannel);
    SplotterChannel->addChannel(m_LogChannels.Console);

    Format = new Poco::PatternFormatter("[%P][%L%Y-%m-%d %H:%M:%S:%i][%p]%t");
    m_LogChannels.File = new Poco::FormattingChannel(Format, new Poco::FileChannel);
    m_LogChannels.File->setProperty("path", QString(QDir::currentPath() + "/log/" + QCoreApplication::applicationName() + ".log").toStdString());
    m_LogChannels.File->setProperty("archive", "timestamp");
    m_LogChannels.File->setProperty("rotation", "1 days");
    m_LogChannels.File->setProperty("times", "local");
    m_LogChannels.File->setProperty("compress", "true");
    m_LogChannels.File->setProperty("purgeAge", "1 months");
    SplotterChannel->addChannel(m_LogChannels.File);

    Format = new Poco::PatternFormatter("[%P][%L%Y-%m-%d %H:%M:%S:%i][%p]%t");
    m_LogChannels.LogToText = new Poco::FormattingChannel(Format, new LogOutToTextCancel([&](std::string text) {
        LogOutToTextCallBack(text);
    }));

    SplotterChannel->addChannel(m_LogChannels.LogToText);
}

Log::~Log()
{

}

void Log::LogOutToTextCallBack(std::string text)
{
    try
    {
        LogOutCallBack(text);
    }
    catch (const std::exception&)
    {

    }
}

Log::LogOutToTextCancel::LogOutToTextCancel(std::function<void(std::string)> Func)
{
    m_LogTextCallback = Func;
}

Log::LogOutToTextCancel::~LogOutToTextCancel()
{
    
}

void Log::LogOutToTextCancel::log(const Poco::Message &msg)
{
    if (!m_LogTextCallback){
        return;
    }
    try{
        m_LogTextCallback(msg.getText());
    }catch(const std::bad_function_call& err){
        m_LogTextCallback = nullptr;
    }
}
