#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define QT_NO_OPENGL
#include <QMainWindow>
#include <QMap>
#include <QObject>
#include <QPluginLoader>
#include <QtCore/qglobal.h>
#include "DevelopmentToolBoxPluginInterface.h"
#include <QStringList>
#include <QVBoxLayout>
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT
public slots:
    void Slot_ToolClicked();
private:
    struct PluginInfo {
        PluginInfo() {
            PluginPointer = NULL;
            PluginLoader = NULL;
        };
        QString ID;
        QString Path;
        QString Name;
        PluginType Type;
        QString Description;

        QWidget* Widget;
        CallBack *p_CallBack;
        QPluginLoader *PluginLoader;
        DevelopmentToolBoxPluginInterface *PluginPointer;
    };
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int InstallPlugin(QString FilePath);
    int UnInstallPlugin(QString PluginID);

    int EnablePlugin(QString PluginID);
    int DisablePlugin(QString PluginID);

    bool PluginIsEnable(QString PluginID);
    void Init();

private:
    void MainWindowCallBack(std::string DataType, std::shared_ptr<void> Data, int Mode);
    CallBack m_CallBack;

    Ui::MainWindow *ui;
    QVBoxLayout *m_Layout;
    //已经安装的插件
    QMap<QString, PluginInfo *>m_PluginIDIndex;//插件ID,插件信息
    QMap<std::string,QList<CallBack *>> DataType_CallBackList;
};

#endif // MAINWINDOW_H
