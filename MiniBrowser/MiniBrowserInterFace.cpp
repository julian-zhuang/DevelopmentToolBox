#include "MiniBrowserInterFace.h"
#include <QDir>
#include <QTabWidget>
#include <QSettings>
#include <BrowserWidget.h>
#include <QtWebEngineWidgets/QtWebEngineWidgets>

void MiniBrowserInterFace::GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description)
{
    ID = "ID:MiniBrowser";
    Type = PluginType::Gui;
    Name = "Mini Browser";
    Description = "Mini Browser";
}

int MiniBrowserInterFace::PluginConfigure(ConfigureAction Action, void **ptr)
{
    if (Action == ConfigureAction::Init){
        QDir Dir;
        Dir.mkdir("MiniBrowser");
        m_Widget = nullptr;
        return 0;
    }
    if (Action == ConfigureAction::Uinit){

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
        m_Widget = new BrowserWidget(*(QWidget**)ptr);
        *ptr = m_Widget;
        return 0;
    }
    if (Action == ConfigureAction::DestroyWidget){
        delete (BrowserWidget *)m_Widget;
        m_Widget = nullptr;
        return 0;
    }
}
