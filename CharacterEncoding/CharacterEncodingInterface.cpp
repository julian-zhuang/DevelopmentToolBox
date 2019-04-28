#include "CharacterEncodingInterface.h"
#include "CharacterEncodingUI.h"
#include <QDir>

void CharacterEncodingInterface::GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description)
{
    ID = "ID:CharacterEncoding";
    Type = PluginType::Gui;
    Name = "Character Encoding";
    Description = "CharacterEncoding";
}

int CharacterEncodingInterface::PluginConfigure(ConfigureAction Action, void **ptr)
{
    if (Action == ConfigureAction::Init){
        QDir Dir;
        Dir.mkdir("FileTransfer");
        m_Widget = nullptr;
        return 1;
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
        m_Widget = new CharacterEncodingUI(*(QWidget**)ptr);
        *ptr = m_Widget;
        return 0;
    }
    if (Action == ConfigureAction::DestroyWidget){
        delete (CharacterEncodingUI *)m_Widget;
        m_Widget = nullptr;
        return 0;
    }
}
