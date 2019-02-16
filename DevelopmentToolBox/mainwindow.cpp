#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SqliteService.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    SqliteService::GetInstance()->Init();
    ui->setupUi(this);
	this->setWindowTitle(tr("DevelopmentToolBox"));
    //工具栏设置
    ToolStrs.clear();
    ToolStrs<<tr("Working");
    ToolStrs<<tr("SearchFile");
    ToolStrs<<tr("FileTransfer");
    ToolStrs<<tr("SocketClient");
    ToolStrs<<tr("SocketServer");
    ToolStrs<<tr("SocketTransfer");
    ToolStrs<<tr("HttpClient");
    ToolStrs<<tr("ColorPicker");
    ToolStrs<<tr("Screenshot");
    ToolStrs<<tr("SnakeGame");
    ToolStrs<<tr("Calculation");
    QToolButton *Tool;
    QVBoxLayout *t_VBoxLayout = new QVBoxLayout;
    t_VBoxLayout->setContentsMargins(0, 0, 0, 0);
    ui->ToolBar_Tools->setLayout(t_VBoxLayout);
    foreach(auto var,ToolStrs){
        Tool = new QToolButton(this);
        Tool->setText(var);
        Tool->setMinimumSize(QSize(150,35));
        Tool->setMaximumSize(QSize(150,35));
        connect(Tool,SIGNAL(clicked()),this,SLOT(Slot_ToolClicked()));
        t_VBoxLayout->addWidget(Tool);
    }
    t_VBoxLayout->addStretch();

    //贪吃蛇速度设置
    connect(ui->spinBox_SnakeSpeed, SIGNAL(valueChanged(int)), ui->widget_SnakeGame, SLOT(SetSpeed(int)));
    connect(ui->pushButton_GameStart,SIGNAL(clicked()),ui->widget_SnakeGame,SLOT(Init()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Slot_ToolClicked()
{
    QToolButton* tbn = (QToolButton*)sender();
    QString ToolText = tbn->text();
    if (ToolText == tr("Working")){
        ui->stackedWidget->setCurrentWidget(ui->page_Working);
    }
    if (ToolText == tr("SocketClient")){
        ui->stackedWidget->setCurrentWidget(ui->page_SocketClient);
    }
    if (ToolText == tr("SocketServer")){
        ui->stackedWidget->setCurrentWidget(ui->page_SocketServer);
    }
    if (ToolText == tr("HttpClient")){
        ui->stackedWidget->setCurrentWidget(ui->page_HttpClient);
    }
    if (ToolText == tr("ColorPicker")){
        ui->stackedWidget->setCurrentWidget(ui->page_ColorPicker);
    }
    if (ToolText == tr("Screenshot")){
        ui->stackedWidget->setCurrentWidget(ui->page_Screenshot);
    }
    if (ToolText == tr("SearchFile")){
        ui->stackedWidget->setCurrentWidget(ui->page_SearchFile);
    }
    if (ToolText == tr("FileTransfer")){
        ui->stackedWidget->setCurrentWidget(ui->page_FileTransfer);
    }
    if (ToolText == tr("SnakeGame")){
        ui->stackedWidget->setCurrentWidget(ui->page_SnakeGame);
    }
    if (ToolText == tr("SocketTransfer")){
        ui->stackedWidget->setCurrentWidget(ui->page_SocketTransfer);
    }
    if (ToolText == tr("SnakeGame")){
        ui->stackedWidget->setCurrentWidget(ui->page_SnakeGame);
    }
    if (ToolText == tr("Calculation")){
        ui->stackedWidget->setCurrentWidget(ui->page_Calculation);
    }
}
