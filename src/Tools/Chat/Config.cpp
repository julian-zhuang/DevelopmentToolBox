#include "Config.h"

#include <QSettings>

Config* Config::m_ClassInstance = nullptr;
std::mutex Config::CreatInstance_Mutex;

#pragma execution_character_set("utf-8")
void Config::DestoryInstance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr){
        return;
    }
    delete m_ClassInstance;
    return;
}

Config *Config::Instance()
{
    std::lock_guard<std::mutex> lockGuard(CreatInstance_Mutex);
    if (m_ClassInstance == nullptr){
        m_ClassInstance = new Config;
    }
    return m_ClassInstance;
}

int Config::GetValue(QString group, QString key, int &value)
{
    if(m_ClassInstance == nullptr){
        return -1;
    }
    if (m_ClassInstance->ConfInfo.find(group) == m_ClassInstance->ConfInfo.end()) {
        return -2;
    }
    if (m_ClassInstance->ConfInfo[group].find(key) == m_ClassInstance->ConfInfo[group].end()) {
        return -3;
    }
    value = m_ClassInstance->ConfInfo[group][key].toInt();
    return 0;
}

int Config::GetValue(QString group, QString key, bool &value, bool Oper)
{
    if(m_ClassInstance == nullptr){
        return -1;
    }
    if (m_ClassInstance->ConfInfo.find(group) == m_ClassInstance->ConfInfo.end()) {
        return -2;
    }
    if (m_ClassInstance->ConfInfo[group].find(key) == m_ClassInstance->ConfInfo[group].end()) {
        return -3;
    }
    value = m_ClassInstance->ConfInfo[group][key].toBool();
}

int Config::GetValue(QString group, QString key, double &value)
{
    if(m_ClassInstance == nullptr){
        return -1;
    }
    if (m_ClassInstance->ConfInfo.find(group) == m_ClassInstance->ConfInfo.end()) {
        return -2;
    }
    if (m_ClassInstance->ConfInfo[group].find(key) == m_ClassInstance->ConfInfo[group].end()) {
        return -3;
    }
    value = m_ClassInstance->ConfInfo[group][key].toDouble();
    return 0;
}

int Config::GetValue(QString group, QString key, QString &value)
{
    if(m_ClassInstance == nullptr){
        return -1;
    }
    if (m_ClassInstance->ConfInfo.find(group) == m_ClassInstance->ConfInfo.end()) {
        return -2;
    }
    if (m_ClassInstance->ConfInfo[group].find(key) == m_ClassInstance->ConfInfo[group].end()) {
        return -3;
    }
    value = m_ClassInstance->ConfInfo[group][key].toString();
    return 0;
}

int Config::SetValue(QString group, QString key, int value)
{
    if(m_ClassInstance == nullptr){
        return -1;
    }
    m_ClassInstance->ConfInfo[group][key] = QVariant(value);
    return 0;
}

int Config::SetValue(QString group, QString key, bool value, bool Oper)
{
    if(m_ClassInstance == nullptr){
        return -1;
    }
    m_ClassInstance->ConfInfo[group][key] = QVariant(value);
    return 0;
}

int Config::SetValue(QString group, QString key, double value)
{
    if(m_ClassInstance == nullptr){
        return -1;
    }
    m_ClassInstance->ConfInfo[group][key] = QVariant(value);
    return 0;
}

int Config::SetValue(QString group, QString key, QString value)
{
    if(m_ClassInstance == nullptr){
        return -1;
    }
    m_ClassInstance->ConfInfo[group][key] = QVariant(value);
    return 0;
}

void Config::Read(QString ini_filepath)
{
    IniFile = ini_filepath;
    QSettings IniConf(IniFile, QSettings::IniFormat);
    auto Groups = IniConf.childGroups();
    foreach(auto Group, Groups)
    {
        IniConf.beginGroup(Group);
        auto Keys = IniConf.allKeys();
        foreach(auto key, Keys) {
            ConfInfo[Group][key] = IniConf.value(key);
        }
        IniConf.endGroup();
    }
}

Config::Config()
{

}

Config::~Config()
{
    QSettings IniConf(IniFile, QSettings::IniFormat);
    for (auto i = ConfInfo.begin(); i != ConfInfo.end(); i++) {
        IniConf.beginGroup(i->first);
        for (auto j = (i->second).begin(); j != (i->second).end(); j++) {
            IniConf.setValue(j->first, j->second);
        }
        IniConf.endGroup();
    }
}
