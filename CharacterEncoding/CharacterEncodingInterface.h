#ifndef CHARACTERENCODING_H
#define CHARACTERENCODING_H

#include <QObject>
#include <QtCore/qglobal.h>
#include <DevelopmentToolBoxPluginInterface.h>

#if defined(CHARACTERENCODING_LIBRARY)
#  define CHARACTERENCODINGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CHARACTERENCODINGSHARED_EXPORT Q_DECL_IMPORT
#endif

class CHARACTERENCODINGSHARED_EXPORT CharacterEncodingInterface  : public QObject, public DevelopmentToolBoxPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "CharacterEncodingInterface")
    Q_INTERFACES(DevelopmentToolBoxPluginInterface)
public:
    void GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description) override;
    int PluginConfigure(ConfigureAction Action, void **ptr = nullptr) override;
private:
    QWidget *m_Widget;
    CallBack m_Callback;
    CallBack MainWindow_Callback;
};

#endif // CHARACTERENCODING_H
