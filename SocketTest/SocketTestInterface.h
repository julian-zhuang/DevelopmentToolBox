#ifndef SOCKETTESTINTERFACE_H
#define SOCKETTESTINTERFACE_H

#include <QObject>
#include <QtCore/qglobal.h>
#include <DevelopmentToolBoxPluginInterface.h>

#if defined(SOCKETTEST_LIBRARY)
#  define SOCKETTESTINTERFACESHARED_EXPORT Q_DECL_EXPORT
#else
#  define SOCKETTESTINTERFACESHARED_EXPORT Q_DECL_IMPORT
#endif

class SocketTestInterface : public QObject, public DevelopmentToolBoxPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "SocketTestInterface")
    Q_INTERFACES(DevelopmentToolBoxPluginInterface)
public:
    void GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description) override;
    int PluginConfigure(ConfigureAction Action, void **ptr = nullptr) override;
private:
    QWidget *m_Widget;
    CallBack m_Callback;
    CallBack MainWindow_Callback;
};

#endif // SOCKETTESTINTERFACE_H
