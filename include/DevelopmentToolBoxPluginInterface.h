#pragma once
#include <QString>
#include <iostream>
#include <functional>
#include <memory>
#include <QWidget>
#include <list>

#ifndef __DEVELOPMENTTOOLBOXPLUGININTERFACE__
#define __DEVELOPMENTTOOLBOXPLUGININTERFACE__

#define SharePtr std::shared_ptr
#define SharePtrMake std::make_shared
#define ShareCast std::static_pointer_cast

typedef std::function<void(std::string DataType, std::shared_ptr<void> Data, int Mode)> CallBack;

enum PluginType{
    Gui,
    NoGui
};

enum ConfigureAction{
    Init,
    Uinit,
    SetCallback,
    GetCallback,
    CreatWidget,
    DestroyWidget
};

struct DataRegistration{
    bool Registration = true;
    std::list<std::string> StrDataTypeS;
    CallBack *p_CallBack;
};

class DevelopmentToolBoxPluginInterface{
public:
    /*************************************************************************
    *函数名：GetPluginInfo
    *功能：获取插件的基本信息（改接口由MainWindow调用）
    *参数：
        ID：            插件的唯一ID
        Type:           插件的类型
        Name:           插件的名称
        Description:    插件的描述
    *返回值：
    *备注：
        Mainwindow调用时会先传入自己的回调函数地址，插件在收到传入的地址时应当对改地址进行保
        存，然后将其修改为插件本身的回调函数地址，一遍Mainwindow能够顺利的通过回调函数进行通讯
    *************************************************************************/
    virtual void GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description) = 0;
    /*************************************************************************
    *函数名：PluginConfigure
    *功能：插件配置
    *参数：
        p_Widget:       父窗口指针
    *返回值：正常返回0
            失败返回负数
    *备注：
        如果是Gui插件，请使用传入的ptr作为父窗口建立窗口
    *************************************************************************/
    virtual int PluginConfigure(ConfigureAction Action, void **ptr = nullptr) = 0;
};
Q_DECLARE_INTERFACE(DevelopmentToolBoxPluginInterface, "DevelopmentToolBoxPluginInterface")
#endif //__DEVELOPMENTTOOLBOXPLUGININTERFACE__
