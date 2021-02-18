#ifndef CONFIG_H
#define CONFIG_H

#include <mutex>
#include <iostream>

#include <map>

#include <QVariant>

class Config
{
public:
    static void DestoryInstance();
    static Config *Instance();

    int GetValue(QString group, QString key, int &value);
    int GetValue(QString group, QString key, bool &value, bool Oper);
    int GetValue(QString group, QString key, double &value);
    int GetValue(QString group, QString key, QString& value);

    int SetValue(QString group, QString key, int value);
    int SetValue(QString group, QString key, bool value, bool Oper);
    int SetValue(QString group, QString key, double value);
    int SetValue(QString group, QString key, QString value);

    void Read(QString ini_filepath);

protected:
    Config();
    ~Config();

protected:
    static std::mutex CreatInstance_Mutex;
    static Config* m_ClassInstance;
    QString IniFile;
    std::map<QString, std::map<QString, QVariant>> ConfInfo;
};

#endif // CONFIG_H
