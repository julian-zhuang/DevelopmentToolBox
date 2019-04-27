#include "TerminalInterface.h"
#include "TerminalUI.h"
#include <QDir>

void TerminalInterface::GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description)
{
    ID = "ID:Terminal";
    Type = PluginType::Gui;
    Name = "Terminal";
    Description = "Terminal";
}

int TerminalInterface::PluginConfigure(ConfigureAction Action, void **ptr)
{
    if (Action == ConfigureAction::Init){
        QDir Dir;
        Dir.mkdir("Terminal");
        return 0;
    }
    if (Action == ConfigureAction::Uinit){

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
        m_Widget = new TerminalUI((QWidget*)(*ptr));
        *ptr = m_Widget;
        return 0;
    }
    if (Action == ConfigureAction::DestroyWidget){
        delete (TerminalUI*)m_Widget;
        m_Widget = nullptr;
        return 0;
    }
}
