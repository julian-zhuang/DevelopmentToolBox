#include "RaspberryPiGPIOInterface.h"
#include <QDir>
#include <RaspberryPiGPIOUI.h>

void RaspberryPiGPIOInterface::GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description)
{
    ID = "ID:RaspberryPiGPIO";
    Type = PluginType::Gui;
    Name = "Raspberry Pi GPIO";
    Description = "Raspberry Pi GPIO";
}

int RaspberryPiGPIOInterface::PluginConfigure(ConfigureAction Action, void **ptr)
{
    if (Action == ConfigureAction::Init){
        QDir Dir;
        Dir.mkdir("RaspberryPiGPIO");
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
        m_Widget = new RaspberryPiGPIOUI(*(QWidget**)ptr);
        *ptr = m_Widget;
        return 0;
    }
    if (Action == ConfigureAction::DestroyWidget){
        delete (RaspberryPiGPIOUI *)m_Widget;
        m_Widget = nullptr;
        return 0;
    }
}
