#ifndef MiniBrowserInterFace_H
#define MiniBrowserInterFace_H

#include <QObject>
#include <QtCore/qglobal.h>
#include <DevelopmentToolBoxPluginInterface.h>

#if defined(WEBWECHAT_LIBRARY)
#  define WEBWECHATSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WEBWECHATSHARED_EXPORT Q_DECL_IMPORT
#endif

class WEBWECHATSHARED_EXPORT MiniBrowserInterFace : public QObject, public DevelopmentToolBoxPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "MiniBrowserInterFace")
    Q_INTERFACES(DevelopmentToolBoxPluginInterface)
public:
    void GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description) override;
    int PluginConfigure(ConfigureAction Action, void **ptr = nullptr) override;
private:
    QWidget *m_Widget;
    CallBack m_Callback;
    CallBack MainWindow_Callback;
};

#endif // MiniBrowserInterFace_H
