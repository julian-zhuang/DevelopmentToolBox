#include "SocketTestInterface.h"
#include <QPushButton>
#include <QDir>
#include "SocketTestUI.h"

void SocketTestInterface::GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description)
{
    ID = "ID:SocketTest";
    Type = PluginType::Gui;
    Name = "Socket Test";
    Description = "Socket Test";
}

int SocketTestInterface::PluginConfigure(ConfigureAction Action, void **ptr)
{
    if (Action == ConfigureAction::Init){
        QDir Dir;
        Dir.mkdir("SocketTest");
        return 0;
    }
    if (Action == ConfigureAction::Uinit){
        SocketTestUI* t_SocketTestUI = (SocketTestUI*)m_Widget;
        delete t_SocketTestUI;
        return 0;
    }
    if (Action == ConfigureAction::SetCallback){
        return 0;
    }
    if (Action == ConfigureAction::GetCallback){
        (*ptr) = nullptr;
        return 0;
    }
    if (Action == ConfigureAction::CreatWidget){
        m_Widget = (QWidget *)new SocketTestUI((QWidget *)(*ptr));
        *ptr = m_Widget;
        return 0;
    }
    if (Action == ConfigureAction::DestroyWidget){
        delete (SocketTestUI*)m_Widget;
        return 0;
    }
}
