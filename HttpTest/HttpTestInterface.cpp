#include "HttpTestInterface.h"
#include "HttpTestUI.h"
#include <QDir>


void HttpTestInterface::GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description)
{
    ID = "ID:HttpTest";
    Type = PluginType::Gui;
    Name = "Http Test";
    Description = "Http Test";
}

int HttpTestInterface::PluginConfigure(ConfigureAction Action, void **ptr)
{
    if (Action == ConfigureAction::Init){
        QDir Dir;
        Dir.mkdir("HttpTest");
        m_Widget = nullptr;
        return 0;
    }
    if (Action == ConfigureAction::Uinit){
        if (m_Widget != nullptr){
            PluginConfigure(ConfigureAction::DestroyWidget);
        }

        return 0;
    }
    if (Action == ConfigureAction::SetCallback){
        MainWindow_Callback = **((CallBack**)ptr);
        return 0;
    }
    if (Action == ConfigureAction::GetCallback){
        (*ptr) = nullptr;
        return 0;
    }
    if (Action == ConfigureAction::CreatWidget){
        m_Widget = new HttpTestUI(*(QWidget**)ptr);
        *ptr = m_Widget;
        return 0;
    }
    if (Action == ConfigureAction::DestroyWidget){
        delete (HttpTestUI *)m_Widget;
        m_Widget = nullptr;
        return 0;
    }
}
