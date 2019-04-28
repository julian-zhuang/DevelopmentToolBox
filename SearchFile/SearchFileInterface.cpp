#include "SearchFileInterface.h"
#include "SearchFile.h"
#include <QDir>

void SearchFileInterface::GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description)
{
    ID = "ID:SearchFile";
    Type = PluginType::Gui;
    Name = "Search File";
    Description = "Search File";
}

int SearchFileInterface::PluginConfigure(ConfigureAction Action, void **ptr)
{
    if (Action == ConfigureAction::Init){
        QDir Dir;
        Dir.mkdir("SearchFile");
        return 0;
    }
    if (Action == ConfigureAction::Uinit){
        if (m_Widget != nullptr){
            PluginConfigure(ConfigureAction::DestroyWidget);
        }
        return 0;
    }
    if (Action == ConfigureAction::SetCallback){
        MainWindow_Callback = *((CallBack*)(*ptr));
        return 0;
    }
    if (Action == ConfigureAction::GetCallback){
        (*ptr) = nullptr;
        return 0;
    }
    if (Action == ConfigureAction::CreatWidget){
        m_Widget = new SearchFile((QWidget*)(*ptr));
        *ptr = m_Widget;
        return 0;
    }
    if (Action == ConfigureAction::DestroyWidget){
        delete (SearchFile*)m_Widget;
        m_Widget = nullptr;
        return 0;
    }
}
