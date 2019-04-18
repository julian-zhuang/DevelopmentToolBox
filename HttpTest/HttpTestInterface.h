#ifndef HTTPTEST_H
#define HTTPTEST_H

#include <QObject>
#include <QtCore/qglobal.h>
#include <DevelopmentToolBoxPluginInterface.h>

#if defined(HTTPTEST_LIBRARY)
#  define HTTPTESTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HTTPTESTSHARED_EXPORT Q_DECL_IMPORT
#endif

class HTTPTESTSHARED_EXPORT HttpTestInterface : public QObject, public DevelopmentToolBoxPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "HttpTestInterface")
    Q_INTERFACES(DevelopmentToolBoxPluginInterface)
public:
    void GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description) override;
    int PluginConfigure(ConfigureAction Action, void **ptr = nullptr) override;
private:
    QWidget *m_Widget;
    CallBack m_Callback;
    CallBack MainWindow_Callback;
};

#endif // HTTPTEST_H
