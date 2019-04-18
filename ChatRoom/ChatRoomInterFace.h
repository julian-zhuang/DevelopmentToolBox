#ifndef CHATROOMINTERFACE_H
#define CHATROOMINTERFACE_H

#include <QObject>
#include <QtCore/qglobal.h>
#include <DevelopmentToolBoxPluginInterface.h>

#if defined(CHATROOM_LIBRARY)
#  define CHATROOMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CHATROOMSHARED_EXPORT Q_DECL_IMPORT
#endif

class CHATROOMSHARED_EXPORT ChatRoomInterFace  : public QObject, public DevelopmentToolBoxPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ChatRoomInterFace")
    Q_INTERFACES(DevelopmentToolBoxPluginInterface)
public:
    void GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description) override;
    int PluginConfigure(ConfigureAction Action, void **ptr = nullptr) override;
private:
    QWidget *m_Widget;
    CallBack m_Callback;
    CallBack MainWindow_Callback;
};

#endif // CHATROOMINTERFACE_H
