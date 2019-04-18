#include "ChatRoomInterFace.h"
#include "ChatRoomUI.h"
#include <QDir>

void ChatRoomInterFace::GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description)
{
    ID = "ID:ChatRoom";
    Type = PluginType::Gui;
    Name = "ChatRoom";
    Description = "ChatRoom";
}

int ChatRoomInterFace::PluginConfigure(ConfigureAction Action, void **ptr)
{
    if (Action == ConfigureAction::Init){
        QDir Dir;
        Dir.mkdir("ChatRoom");
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
        m_Widget = new ChatRoomUI(*(QWidget**)ptr);
        *ptr = m_Widget;
        return 0;
    }
    if (Action == ConfigureAction::DestroyWidget){
        delete (ChatRoomUI *)m_Widget;
        m_Widget = nullptr;
        return 0;
    }
}
