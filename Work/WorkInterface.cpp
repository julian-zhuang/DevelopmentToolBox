#include "WorkInterface.h"
#include <WorkUI.h>
#include <QDir>

void WorkInterface::GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description)
{
    ID = "ID:Work";
    Type = PluginType::Gui;
    Name = "Work";
    Description = "Work";
}

int WorkInterface::PluginConfigure(ConfigureAction Action, void **ptr)
{

    if (Action == ConfigureAction::Init){
        QDir Dir;
        Dir.mkdir("Work");
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
        m_Widget = (QWidget *)new WorkUI((QWidget *)(*ptr));
        *ptr = m_Widget;
        return 0;
    }
    if (Action == ConfigureAction::DestroyWidget){
        delete (WorkUI*)m_Widget;
        m_Widget = nullptr;
        return 0;
    }
}
