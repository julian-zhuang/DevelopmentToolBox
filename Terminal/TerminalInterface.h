#ifndef TERMINALINTERFACE_H
#define TERMINALINTERFACE_H

#include <QObject>
#include <QtCore/qglobal.h>
#include <DevelopmentToolBoxPluginInterface.h>

#if defined(TERMINAL_LIBRARY)
#  define TERMINALSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TERMINALSHARED_EXPORT Q_DECL_IMPORT
#endif


class TERMINALSHARED_EXPORT TerminalInterface : public QObject, public DevelopmentToolBoxPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TerminalInterface")
    Q_INTERFACES(DevelopmentToolBoxPluginInterface)
public:
    void GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description) override;
    int PluginConfigure(ConfigureAction Action, void **ptr = nullptr) override;
private:
    QWidget *m_Widget;
    CallBack m_Callback;
    CallBack MainWindow_Callback;
};

#endif // TERMINALINTERFACE_H
