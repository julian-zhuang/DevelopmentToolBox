#ifndef WORKLOG_H
#define WORKLOG_H

#include <QtCore/qglobal.h>
#include <QObject>
#include <DevelopmentToolBoxPluginInterface.h>

#if defined(WORKLOGINTERFACE_LIBRARY)
#  define WORKLOGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WORKLOGSHARED_EXPORT Q_DECL_IMPORT
#endif

class WORKLOGSHARED_EXPORT WorkInterface : public QObject, public DevelopmentToolBoxPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "WorkInterface")
    Q_INTERFACES(DevelopmentToolBoxPluginInterface)
public:
    void GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description) override;
    int PluginConfigure(ConfigureAction Action, void **ptr = nullptr) override;
private:
    QWidget *m_Widget;
    CallBack m_Callback;
    CallBack MainWindow_Callback;
};

#endif // WORKLOG_H
