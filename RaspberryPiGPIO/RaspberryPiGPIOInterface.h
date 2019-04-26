#ifndef RASPBERRYPIGPIOINTERFACE_H
#define RASPBERRYPIGPIOINTERFACE_H

#include <QObject>
#include <QtCore/qglobal.h>
#include <DevelopmentToolBoxPluginInterface.h>

#if defined(RASPBERRYPIGPIO_LIBRARY)
#  define RASPBERRYPIGPIOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RASPBERRYPIGPIOSHARED_EXPORT Q_DECL_IMPORT
#endif

class RASPBERRYPIGPIOSHARED_EXPORT RaspberryPiGPIOInterface: public QObject, public DevelopmentToolBoxPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "RaspberryPiGPIOInterface")
    Q_INTERFACES(DevelopmentToolBoxPluginInterface)
public:
    void GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description) override;
    int PluginConfigure(ConfigureAction Action, void **ptr = nullptr) override;
private:
    QWidget *m_Widget;
    CallBack m_Callback;
    CallBack MainWindow_Callback;
};
#endif // RASPBERRYPIGPIOINTERFACE_H
