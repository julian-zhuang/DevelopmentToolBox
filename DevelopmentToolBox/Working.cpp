#include "Working.h"
#include "ui_Working.h"
#include <QDateTime>
#include <QEvent>
#include <QMouseEvent> 
#include <QPoint>
#include <QListWidgetItem>
#include "TaskEdit.h"
#include "TaskWidget.h"
#include <QSettings>
#include "SqliteService.h"
#include <QFileDialog>
#include <QProcess>
#include <QToolButton>
#include <QUuid>
#include <QFileIconProvider>

Working::Working(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Working)
{
    ui->setupUi(this);
	    
    //更新时间设置
    m_TodayTimeUpdata.start(1000);
    connect(&m_TodayTimeUpdata,SIGNAL(timeout()),this,SLOT(Slot_TodayTimeUpdata()));
	ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
	Slot_DateTimeChanged(QDateTime::currentDateTime());

	//工具栏
	ui->widget_Tools->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->widget_Tools, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(Slot_ShowMenu(const QPoint &)));

	m_ToolMenu = new QMenu;
	connect(m_ToolMenu, SIGNAL(triggered(QAction *)), this, SLOT(Slot_MenuClick(QAction *)));

	Tool_Delete = new QAction(m_ToolMenu);
	Tool_Delete->setText(tr("Delete"));
	m_ToolMenu->addAction(Tool_Delete);

	//任务列表
	ui->treeWidget_TaskList->setContextMenuPolicy(Qt::CustomContextMenu);
	ui->treeWidget_TaskList->setColumnHidden(0, true);
	connect(ui->treeWidget_TaskList, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(Slot_ShowMenu(const QPoint &)));
	
	TasklistUpdata();

	m_TaskListMenu = new QMenu;
	connect(m_TaskListMenu, SIGNAL(triggered(QAction *)), this, SLOT(Slot_MenuClick(QAction *)));

	ListWig_Creat = new QAction;
	ListWig_Creat->setText(tr("Create"));
	m_TaskListMenu->addAction(ListWig_Creat);

	ListWig_Edit = new QAction;
	ListWig_Edit->setText(tr("Edit"));
	m_TaskListMenu->addAction(ListWig_Edit);

	ListWig_Start = new QAction;
	ListWig_Start->setText(tr("Start"));
	m_TaskListMenu->addAction(ListWig_Start);

	ListWig_Complete = new QAction;
	ListWig_Complete->setText(tr("Complete"));
	m_TaskListMenu->addAction(ListWig_Complete);

    ListWig_Delete = new QAction;
    ListWig_Delete->setText(tr("Delete"));
    m_TaskListMenu->addAction(ListWig_Delete);

	ui->widget_Tools->installEventFilter(this);

	//添加工具栏按钮
	t_Layout = new QHBoxLayout;
	t_Layout->setDirection(QBoxLayout::LeftToRight);
	ui->widget_Tools->setLayout(t_Layout);
	t_Layout->setContentsMargins(0, 0, 0, 0);
	t_Layout->addStretch();
	
	Toolbtn_FilePath.clear();
	foreach(auto var, SqliteService::GetInstance()->GetToolsInfo()) {
		QString t_ObjName = var.Name;
		t_ToolButton = new QToolButton(this);
		t_ToolButton->setObjectName(t_ObjName);
		Toolbtn_FilePath[t_ToolButton] = var.Path;
		t_ToolButton->setMinimumSize(QSize(50, 50));
		t_ToolButton->setMaximumSize(QSize(50, 50));

		QFileInfo file_info(var.Path);
		QFileIconProvider icon_provider;
		QIcon icon = icon_provider.icon(file_info);
		t_ToolButton->setIcon(icon);
		t_ToolButton->setIconSize(t_ToolButton->size());

		t_Layout->insertWidget(t_Layout->count() - 1, t_ToolButton);
		t_ToolButton->setContextMenuPolicy(Qt::CustomContextMenu);
		connect(t_ToolButton, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(Slot_ShowMenu(const QPoint &)));
		connect(t_ToolButton, SIGNAL(clicked()), this, SLOT(Slot_ButtonClicked()));
	}

	connect(&m_timerTextEditChange, SIGNAL(timeout()), this, SLOT(Slot_EditingFinished()));
	connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(Slot_TextChange()));
	connect(ui->pushButton_DayRight, SIGNAL(clicked()), this, SLOT(Slot_ButtonClicked()));
	connect(ui->pushButton_DayLeft, SIGNAL(clicked()), this, SLOT(Slot_ButtonClicked()));
	connect(ui->dateTimeEdit, SIGNAL(dateTimeChanged(const QDateTime &)), this, SLOT(Slot_DateTimeChanged(const QDateTime &)));
}

Working::~Working()
{
	QStringList t_StrList;
	QList<ToolsInfo> Tools;
	Tools.clear();
	for (auto i = Toolbtn_FilePath.begin(); i != Toolbtn_FilePath.end(); ++i) {
		ToolsInfo t_TI;
		t_TI.Name = i.key()->objectName();
		t_TI.Path = i.value();
		Tools.append(t_TI);
	}
	SqliteService::GetInstance()->SetToolsInfo(Tools);
    delete ui;
}

void Working::Slot_MenuClick(QAction * action)
{
	QMenu * t_pMenu = qobject_cast<QMenu *>(sender());
	auto jk = t_pMenu->objectName();
	if (t_pMenu == m_ToolMenu) {
		if (action->text() == tr("Delete")) {
            Toolbtn_FilePath.remove(CurrentSelection);
			delete CurrentSelection;
		}
	}
	if (t_pMenu == m_TaskListMenu) {
		QTreeWidgetItem *t_pcurrentItem = ui->treeWidget_TaskList->currentItem();
		if (action->text() == tr("Create")) {
            TaskEdit t_TaskEdit("","",this);
            if (t_TaskEdit.exec()){
				SqliteService::GetInstance()->CreatTask(t_TaskEdit.TaskID, t_TaskEdit.TaskName, t_TaskEdit.Taskcontent);
				t_pcurrentItem = new QTreeWidgetItem;
				t_pcurrentItem->setText(0, t_TaskEdit.TaskID);
				t_pcurrentItem->setText(1, t_TaskEdit.TaskName);
				t_pcurrentItem->setText(2, "");
				t_pcurrentItem->setText(3, t_TaskEdit.Taskcontent);
				t_pcurrentItem->setText(4, QDateTime::currentDateTime().toString("yyyy-MM-dd"));
				ui->treeWidget_TaskList->addTopLevelItem(t_pcurrentItem);
				return;
            }
		}
		if (t_pcurrentItem == nullptr) {
			return;
		}
		if (action->text() == tr("Edit")) {
			TaskEdit t_TaskEdit(t_pcurrentItem->text(1), t_pcurrentItem->text(3), this);
			t_TaskEdit.exec();
			SqliteService::GetInstance()->ChangeTask(t_pcurrentItem->text(0), t_TaskEdit.TaskName, t_TaskEdit.Taskcontent);
		}
		if (action->text() == tr("Start")) {
			t_pcurrentItem->setText(5, QDateTime::fromTime_t(SqliteService::GetInstance()->StartTask(t_pcurrentItem->text(0))).toString("yyyy-MM-dd"));
		}
		if (action->text() == tr("Complete")) {
			t_pcurrentItem->setText(6, QDateTime::fromTime_t(SqliteService::GetInstance()->EndTask(t_pcurrentItem->text(0))).toString("yyyy-MM-dd"));
		}
        if (action->text() == tr("Delete")) {
			SqliteService::GetInstance()->DeleteTask(t_pcurrentItem->text(0));
			delete t_pcurrentItem;
        }
	}
}

void Working::Slot_ShowMenu(const QPoint & pos)
{
	QToolButton * t_pToolbtn = qobject_cast<QToolButton *>(sender());
    CurrentSelection = t_pToolbtn;
	if (t_pToolbtn != nullptr) {
		m_ToolMenu->move(cursor().pos());
		m_ToolMenu->exec();
		return;
	}
	QTreeWidget * t_pListWig = qobject_cast<QTreeWidget *>(sender());
    QTreeWidgetItem *t_pcurrentItem = ui->treeWidget_TaskList->currentItem();
    if (t_pcurrentItem == nullptr){
        ListWig_Edit->setEnabled(false);
        ListWig_Delete->setEnabled(false);
        ListWig_Start->setEnabled(false);
        ListWig_Complete->setEnabled(false);
    }else{
        ListWig_Edit->setEnabled(true);
        ListWig_Delete->setEnabled(true);
        ListWig_Start->setEnabled(true);
        ListWig_Complete->setEnabled(true);
    }
	if (t_pListWig != nullptr) {
		m_TaskListMenu->move(cursor().pos());
		m_TaskListMenu->exec();
		return;
    }
}

void Working::Slot_EditingFinished()
{
	m_timerTextEditChange.stop();
    SqliteService::GetInstance()->AddWorkLog(ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd"),ui->textEdit->toPlainText());
}

void Working::Slot_TextChange()
{
	m_timerTextEditChange.start(500);
}

void Working::Slot_DateTimeChanged(const QDateTime & datetime)
{
	QString Text = SqliteService::GetInstance()->GetWorkLog(datetime.toString("yyyy-MM-dd"));
	if (Text.length() <= 0) {
		ui->textEdit->clear();
		ui->textEdit->setText(ui->dateTimeEdit->text());
		return;
	}
	ui->textEdit->setText(Text);
}

void Working::Slot_ButtonClicked()
{
	QPushButton *t_pBtn = (QPushButton *)sender();
	if (t_pBtn == ui->pushButton_DayRight) {
		ui->dateTimeEdit->setDateTime(ui->dateTimeEdit->dateTime().addDays(1));
		TasklistUpdata();
		return;
	}
	if (t_pBtn == ui->pushButton_DayLeft) {
		ui->dateTimeEdit->setDateTime(ui->dateTimeEdit->dateTime().addDays(-1));
		TasklistUpdata();
		return;
	}
	if (Toolbtn_FilePath.find(t_pBtn) != Toolbtn_FilePath.end()) {
		QProcess *t_QProcess = new QProcess;
		t_QProcess->start(Toolbtn_FilePath[t_pBtn]);
	}
}

void Working::InitToolBar()
{
}

void Working::TasklistUpdata()
{
	ui->treeWidget_TaskList->clear();
	unsigned int DataTimeNow = QDateTime::fromString(ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd"), "yyyy-MM-dd").toTime_t();
	DataTimeNow += 86400;
	QList<TaskInfo> Tasks = SqliteService::GetInstance()->GetTask();
	foreach(auto var, Tasks) {
		if (var.CreateTime > DataTimeNow) {
			continue;
		}
		if (var.EndTime < (DataTimeNow - 86400) && var.EndTime != 0) {
			continue;
		}
		QTreeWidgetItem * t_Item = new QTreeWidgetItem;
		t_Item->setText(0, var.ID);
		t_Item->setText(1, var.Name);
		t_Item->setText(2, var.State);
		t_Item->setText(3, var.Content);
		if (var.CreateTime != 0) {
			t_Item->setText(4, QDateTime::fromTime_t(var.CreateTime).toString("yyyy-MM-dd"));
		}
		if (var.StartTime != 0) {
			t_Item->setText(5, QDateTime::fromTime_t(var.StartTime).toString("yyyy-MM-dd"));
		}
		if (var.EndTime != 0) {
			t_Item->setText(6, QDateTime::fromTime_t(var.EndTime).toString("yyyy-MM-dd"));
		}
		ui->treeWidget_TaskList->addTopLevelItem(t_Item);
	}
}

bool Working::eventFilter(QObject * watched, QEvent * event)
{
	if (event->type() == QEvent::MouseButtonDblClick) {
		if (watched == ui->widget_Tools) {
			if (((QMouseEvent *)event)->button() == Qt::LeftButton) {
				QString t_ObjName = QUuid::createUuid().toString();
				t_ToolButton = new QToolButton(this);
				t_ToolButton->setObjectName(t_ObjName);
				//选择文件
				QFileDialog t_FileDialog(this);
				t_FileDialog.setDirectory(QDir::homePath());
				t_FileDialog.setAcceptMode(QFileDialog::AcceptOpen);
				t_FileDialog.setFileMode(QFileDialog::ExistingFile);
				if (t_FileDialog.exec() == QFileDialog::Accepted)
				{
					QStringList fs = t_FileDialog.selectedFiles();
					QFileInfo file_info(fs[0]);
					QFileIconProvider icon_provider;
					QIcon icon = icon_provider.icon(file_info);
					t_ToolButton->setIcon(icon);
					t_ToolButton->setIconSize(t_ToolButton->size());
					Toolbtn_FilePath[t_ToolButton] = fs[0];
					t_ToolButton->setMinimumSize(QSize(50, 50));
					t_ToolButton->setMaximumSize(QSize(50, 50));
					t_Layout->insertWidget(t_Layout->count() - 1,t_ToolButton);
					t_ToolButton->setContextMenuPolicy(Qt::CustomContextMenu);
					connect(t_ToolButton, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(Slot_ShowMenu(const QPoint &)));
					connect(t_ToolButton, SIGNAL(clicked()), this, SLOT(Slot_ButtonClicked()));
				}
				else {
					delete t_ToolButton;
				}
				return true;
			}
		}
	}
	return false;
}

void Working::Slot_TodayTimeUpdata()
{
    QDateTime NowTime = QDateTime::currentDateTime();
    ui->label_Time_HMS->setText(NowTime.toString("hh:mm:ss"));
    ui->label_Time_YMD->setText(NowTime.toString("yyyy-MM-dd"));
}
