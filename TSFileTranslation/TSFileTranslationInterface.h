#ifndef TSFILETRANSLATIONINTERFACE_H
#define TSFILETRANSLATIONINTERFACE_H

#include <QObject>
#include <QtCore/qglobal.h>
#include <DevelopmentToolBoxPluginInterface.h>

#if defined(TSFILETRANSLATION_LIBRARY)
#  define TSFILETRANSLATIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TSFILETRANSLATIONSHARED_EXPORT Q_DECL_IMPORT
#endif

class TSFILETRANSLATIONSHARED_EXPORT TSFileTranslationInterface : public QObject, public DevelopmentToolBoxPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TSFileTranslationInterface")
    Q_INTERFACES(DevelopmentToolBoxPluginInterface)
public:
    void GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description) override;
    int PluginConfigure(ConfigureAction Action, void **ptr = nullptr) override;
private:
    QWidget *m_Widget;
    CallBack m_Callback;
    CallBack MainWindow_Callback;
};

#endif // TSFILETRANSLATIONINTERFACE_H
