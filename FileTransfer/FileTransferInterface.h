#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <QObject>
#include <QtCore/qglobal.h>
#include <DevelopmentToolBoxPluginInterface.h>

#if defined(FILETRANSFER_LIBRARY)
#  define FILETRANSFERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FILETRANSFERSHARED_EXPORT Q_DECL_IMPORT
#endif

class FILETRANSFERSHARED_EXPORT FileTransferInterface  : public QObject, public DevelopmentToolBoxPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FileTransferInterface")
    Q_INTERFACES(DevelopmentToolBoxPluginInterface)
public:
    void GetPluginInfo(QString &ID, PluginType &Type, QString &Name, QString &Description) override;
    int PluginConfigure(ConfigureAction Action, void **ptr = nullptr) override;
private:
    QWidget *m_Widget;
    CallBack m_Callback;
    CallBack MainWindow_Callback;
};

#endif // FILETRANSFER_H
