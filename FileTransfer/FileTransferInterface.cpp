#include "FileTransferInterface.h"
#include <FileTransferUI.h>
#include <QDir>

void FileTransferInterface::GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description)
{
    ID = "ID:FileTransfer";
    Type = PluginType::Gui;
    Name = "File Transfer";
    Description = "File Transfer";
}

int FileTransferInterface::PluginConfigure(ConfigureAction Action, void **ptr)
{
    if (Action == ConfigureAction::Init){
        QDir Dir;
        Dir.mkdir("FileTransfer");
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
        m_Widget = new FileTransferUI(*(QWidget**)ptr);
        *ptr = m_Widget;
        return 0;
    }
    if (Action == ConfigureAction::DestroyWidget){
        delete (FileTransferUI *)m_Widget;
        m_Widget = nullptr;
        return 0;
    }
}
