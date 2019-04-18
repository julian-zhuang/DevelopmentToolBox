#ifndef SEARCHFILEINTERFACE_H
#define SEARCHFILEINTERFACE_H

#include <QObject>
#include <QtCore/qglobal.h>
#include <DevelopmentToolBoxPluginInterface.h>

#if defined(SEARCHFILE_LIBRARY)
#  define SEARCHFILESHARED_EXPORT Q_DECL_EXPORT
#else
#  define SEARCHFILESHARED_EXPORT Q_DECL_IMPORT
#endif

class SEARCHFILESHARED_EXPORT SearchFileInterface : public QObject, public DevelopmentToolBoxPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "SearchFileInterface")
    Q_INTERFACES(DevelopmentToolBoxPluginInterface)
public:
    void GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description) override;
    int PluginConfigure(ConfigureAction Action, void **ptr = nullptr) override;
private:
    QWidget *m_Widget;
    CallBack m_Callback;
    CallBack MainWindow_Callback;
};

#endif // SEARCHFILEINTERFACE_H
