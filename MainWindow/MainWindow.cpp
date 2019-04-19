#include "ui_MainWindow.h"
#include "MainWindow.h"
#include <QDir>
#include <QFile>
#include <iostream>
#include <QToolButton>

void MainWindow::Slot_ToolClicked()
{
    QToolButton *ToolBtn = (QToolButton *)sender();
    if (ToolBtn != nullptr){
        ui->stackedWidget->setCurrentWidget(m_PluginIDIndex[ToolBtn->objectName()]->Widget);
    }
}

void MainWindow::Slot_Activated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Context){

    }
    if (reason == QSystemTrayIcon::DoubleClick){
        this->show();
    }
    if (reason == QSystemTrayIcon::Trigger){

    }
    if (reason == QSystemTrayIcon::MiddleClick){

    }
}

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //工具栏设置
    m_Layout = new QVBoxLayout;
    m_Layout->setDirection(QBoxLayout::BottomToTop);
    m_Layout->setContentsMargins(0, 0, 0, 0);
    ui->widget_ToolBar_Tools->setLayout(m_Layout);
    m_Layout->addStretch(1);
    m_SystemTrayIcon = new QSystemTrayIcon(this);
    m_SystemTrayIcon->setIcon(this->windowIcon());
    m_SystemTrayIcon->setToolTip(this->windowTitle());
    connect(m_SystemTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(Slot_Activated(QSystemTrayIcon::ActivationReason)));
    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::InstallPlugin(QString FilePath)
{
    QPluginLoader *PluginLoader = new QPluginLoader(FilePath);
    if (PluginLoader->load()) {
        DevelopmentToolBoxPluginInterface *DllPointer = qobject_cast<DevelopmentToolBoxPluginInterface*>(PluginLoader->instance());
        if (DllPointer == nullptr) {
            return -1;
        }

        QString pluginID;
        QString pluginName;
        QString pluginDescription;
        PluginType pluginType;
        DllPointer->GetPluginInfo(pluginID,pluginType,pluginName,pluginDescription);

        if (m_PluginIDIndex.find(pluginID) != m_PluginIDIndex.end()) {
            PluginLoader->unload();
            delete PluginLoader;
            return -2;
        }

        if (DllPointer->PluginConfigure(ConfigureAction::Init) < 0){
            PluginLoader->unload();
            delete PluginLoader;
            return -3;
        }

        CallBack *p_Callback = &m_CallBack;
        if (DllPointer->PluginConfigure(ConfigureAction::SetCallback,(void **)&p_Callback) < 0){
            PluginLoader->unload();
            delete PluginLoader;
            return -4;
        }

        p_Callback = nullptr;
        if (DllPointer->PluginConfigure(ConfigureAction::GetCallback,(void **)&p_Callback) < 0){
            PluginLoader->unload();
            delete PluginLoader;
            return -4;
        }

        PluginInfo *t_PluginInfo = new PluginInfo;
        t_PluginInfo->ID = pluginID;
        t_PluginInfo->Type = pluginType;
        t_PluginInfo->Name = pluginName;
        t_PluginInfo->Description = pluginDescription;
        t_PluginInfo->Path = FilePath;
        t_PluginInfo->PluginLoader = PluginLoader;
        t_PluginInfo->PluginPointer = DllPointer;
        t_PluginInfo->Widget = nullptr;
        t_PluginInfo->p_CallBack = p_Callback;
        m_PluginIDIndex[t_PluginInfo->ID] = t_PluginInfo;
    }
    else {
        std::cout << FilePath.toStdString() << "error";
        std::cout << PluginLoader->errorString().toStdString() << std::endl;
        delete PluginLoader;
        return -3;
    }
    return 0;
}

int MainWindow::UnInstallPlugin(QString PluginID)
{
    return 0;
}

int MainWindow::EnablePlugin(QString PluginID)
{
    return 0;
}

int MainWindow::DisablePlugin(QString PluginID)
{
    return 0;
}

bool MainWindow::PluginIsEnable(QString PluginID)
{
    return true;
}

void MainWindow::Init()
{
    QStringList PluginFiles;
    QStringList FileFilters;
    FileFilters.clear();

#ifdef Q_OS_LINUX
    FileFilters << "*.so";
#endif
#ifdef Q_OS_WIN32
    FileFilters << "*.dll";
#endif

    QDir PluginsDirectory;
    PluginsDirectory.setPath(QApplication::applicationDirPath() + "/Plugins");
    PluginFiles = PluginsDirectory.entryList(FileFilters, QDir::Files | QDir::Readable, QDir::Name);
    foreach(auto var, PluginFiles) {
        InstallPlugin(PluginsDirectory.path() + '/' + var);
    }

    //加载工具插件
    QToolButton *Tool = nullptr;
    for (QMap<QString, PluginInfo *>::iterator i = m_PluginIDIndex.begin(); i != m_PluginIDIndex.end(); ++i){
        PluginInfo * t_pInfo =  i.value();
        QWidget *t_Widget = this;
        if (t_pInfo->PluginPointer->PluginConfigure(ConfigureAction::CreatWidget,(void **)&t_Widget) < 0){
            continue;
        }

        if (t_Widget == nullptr){
            continue;
        }

        t_pInfo->Widget = t_Widget;
        ui->stackedWidget->addWidget(t_Widget);
        Tool = new QToolButton(this);
        Tool->setObjectName(t_pInfo->ID);
        Tool->setText(t_pInfo->Name);
        Tool->setMinimumSize(QSize(150,35));
        Tool->setMaximumSize(QSize(150,35));
        connect(Tool,SIGNAL(clicked()),this,SLOT(Slot_ToolClicked()));
        m_Layout->addWidget(Tool,0);
    }
}

void MainWindow::MainWindowCallBack(std::string DataType, std::shared_ptr<void> Data, int Mode)
{
    if (DataType == "PluginInterfaceSwitching"){
        SharePtr<std::string> StdStr_PluginID = ShareCast<std::string>(Data);
        QString PluginID(StdStr_PluginID->c_str());
        if (m_PluginIDIndex.contains(PluginID)){
            ui->stackedWidget->setCurrentWidget(m_PluginIDIndex[PluginID]->Widget);
        }
        return;
    }
    if (DataType == "DataRegistration"){
        SharePtr<DataRegistration> DataReg = ShareCast<DataRegistration>(Data);
        if (DataReg->Registration){
            foreach(auto var,DataReg->StrDataTypeS){
                DataType_CallBackList[var].append(DataReg->p_CallBack);
            }
        }else{
            foreach(auto var,DataReg->StrDataTypeS){
                DataType_CallBackList[var].removeOne(DataReg->p_CallBack);
            }
        }
    return;
    }
}
