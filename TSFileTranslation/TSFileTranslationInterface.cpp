#include "TSFileTranslationInterface.h"
#include <TSFileTranslationUI.h>
#include <QDir>

void TSFileTranslationInterface::GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description)
{
    ID = "ID:TSFileTranslation";
    Type = PluginType::Gui;
    Name = "TS File Translation";
    Description = "TS File Translation";
}

int TSFileTranslationInterface::PluginConfigure(ConfigureAction Action, void **ptr)
{
    if (Action == ConfigureAction::Init){
        QDir Dir;
        Dir.mkdir("TSFileTranslation");
        return 0;
    }
    if (Action == ConfigureAction::Uinit){
        delete (TSFileTranslationUI*)m_Widget;;
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
        m_Widget = (QWidget *)new TSFileTranslationUI((QWidget *)(*ptr));
        *ptr = m_Widget;
        return 0;
    }
    if (Action == ConfigureAction::DestroyWidget){
        delete (TSFileTranslationUI*)m_Widget;
        return 0;
    }
}
