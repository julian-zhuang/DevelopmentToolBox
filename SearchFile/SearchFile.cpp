#include "SearchFile.h"
#include "ui_SearchFile.h"
#include "DirectoryList.h"
#include "SqliteService.h"
#include <qdir.h>
#include <QDesktopServices>
#include <qfiledialog.h>
void SearchFile::Slot_SearchDirectoryConfig()
{
    QStringList Directorys = SqliteService::GetInstance()->GetDirectoryList();
    DirectoryList m_DL(this);
    m_DL.SetDirectoryList(Directorys);
    m_DL.exec();
    Directorys = m_DL.GetDirectory();
    SqliteService::GetInstance()->UpdataFile(Directorys);
}

void SearchFile::Slot_UpdataClick()
{
	QStringList Directorys = SqliteService::GetInstance()->GetDirectoryList();
	t_FileIndexThread = new FileIndexThread(Directorys);
	connect(t_FileIndexThread, SIGNAL(Sig_ThreadFinish()), this, SLOT(Slot_FileIndexThreadFinish()));
	connect(t_FileIndexThread, SIGNAL(Sig_Indexing()), this, SLOT(Slot_Indexing()));
	connect(t_FileIndexThread, SIGNAL(Sig_FindFile(QString, int)), this, SLOT(Slot_FindFile(QString, int)));
	t_FileIndexThread->start();
	ui->label_State->setText(tr("Finding......"));
}

void SearchFile::Slot_FileIndexThreadFinish()
{
	ui->label_State->setText(tr("Update index Finish"));
	delete t_FileIndexThread;
	t_FileIndexThread = nullptr;
    ui->comboBox_Type->clear();
    auto StrList = SqliteService::GetInstance()->GetAllFileType();
    StrList.removeOne(".");
    ui->comboBox_Type->addItem(tr("All"));
    ui->comboBox_Type->addItems(StrList);
}

void SearchFile::Slot_FindFile(QString FileName, int Count)
{
	ui->label_State->setText(tr("Finding......(") + QString::number(Count) + ")" + FileName);
}

void SearchFile::Slot_Indexing()
{
	ui->label_State->setText(tr("Indexing......"));
}

void SearchFile::Slot_AdvCheckBoxClick(bool Check)
{
	
}

void SearchFile::Slot_LineEditTextChange(const QString & text)
{
	ChangeTimer.start(300);
}

void SearchFile::Slot_TimeOut()
{
	ChangeTimer.stop();
	if (ui->comboBox_Type->currentText() == tr("All")) {
		m_pModel->setQuery("SELECT Name,Type,Size,CreationTime,ChangeTime,InterviewTime,Path FROM main.FileIndex where name LIKE '" + ui->lineEdit->text() + "%'");
	}
	else {
		m_pModel->setQuery("SELECT Name,Type,Size,CreationTime,ChangeTime,InterviewTime,Path FROM main.FileIndex where name LIKE '" + ui->lineEdit->text() + "%'" + "AND Type='" + ui->comboBox_Type->currentText() + "'");
	}
}

void SearchFile::Slot_ShowMenu(const QPoint & pos)
{
	m_TableViewMenu.exec(QCursor::pos());
}

void SearchFile::Slot_MenuClick(QAction * Action)
{
	if (Action->text() == tr("Open Directory")) {
		QDesktopServices::openUrl(QUrl(m_pModel->index(ui->tableView->currentIndex().row(), 6).data().toString()));
		return;
	}
	if (Action->text() == tr("Copy To...")) {
		QString SrcFile = m_pModel->index(ui->tableView->currentIndex().row(), 6).data().toString();
		QString SrcFileName = m_pModel->index(ui->tableView->currentIndex().row(), 0).data().toString();
		QString DesDirectory = QFileDialog::getExistingDirectory();
		if (!DesDirectory.isEmpty()) {
			QFile::copy(SrcFile + "/" + SrcFileName, DesDirectory + "/" + SrcFileName);
		}
		return;
	}
}

SearchFile::SearchFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchFile)
{
    ui->setupUi(this);
    ui->checkBox_Adv->setVisible(false);
	ui->widget_AdvSearch->setVisible(false);

	connect(ui->pushButton_Updata, SIGNAL(clicked()), this, SLOT(Slot_UpdataClick()));
    connect(ui->pushButton_Config,SIGNAL(clicked()),this,SLOT(Slot_SearchDirectoryConfig()));
    connect(ui->checkBox_Adv, SIGNAL(toggled(bool)), ui->widget_AdvSearch, SLOT(setVisible(bool)));
	m_pModel = new QSqlQueryModel(ui->tableView);
	m_pModel->setQuery("SELECT Name,Type,Size,CreationTime,ChangeTime,InterviewTime,Path FROM main.FileIndex");
	m_pModel->setHeaderData(0, Qt::Horizontal, tr("Name"));
	m_pModel->setHeaderData(1, Qt::Horizontal, tr("Type"));
	m_pModel->setHeaderData(2, Qt::Horizontal, tr("Size"));
	m_pModel->setHeaderData(3, Qt::Horizontal, tr("CreationTime"));
	m_pModel->setHeaderData(4, Qt::Horizontal, tr("ChangeTime"));
	m_pModel->setHeaderData(5, Qt::Horizontal, tr("InterviewTime"));
	m_pModel->setHeaderData(6, Qt::Horizontal, tr("Path"));

	ui->tableView->setModel(m_pModel);
	connect(ui->lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(Slot_LineEditTextChange(const QString &)));
    connect(ui->comboBox_Type,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(Slot_LineEditTextChange(const QString &)));

    auto StrList = SqliteService::GetInstance()->GetAllFileType();
    StrList.removeOne("");
    ui->comboBox_Type->addItem(tr("All"));
    ui->comboBox_Type->addItems(StrList);
	connect(&ChangeTimer, SIGNAL(timeout()), this, SLOT(Slot_TimeOut()));
	ui->tableView->horizontalHeader()->setStretchLastSection(true);
	ui->tableView->verticalHeader()->setDefaultSectionSize(20);
	ui->tableView->verticalHeader()->setVisible(false);

	ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

	connect(ui->tableView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(Slot_ShowMenu(const QPoint &)));
	m_TableViewMenu.addAction(tr("Open Directory"));
	m_TableViewMenu.addAction(tr("Copy To..."));
	connect(&m_TableViewMenu, SIGNAL(triggered(QAction *)), this, SLOT(Slot_MenuClick(QAction *)));
}

SearchFile::~SearchFile()
{
    delete ui;
}
