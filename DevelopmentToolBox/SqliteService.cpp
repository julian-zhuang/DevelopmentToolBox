#include "SqliteService.h"
#include <QDateTime>
#include <QtDebug>
#include <QMessageBox>
#include <quuid.h>
#include <QFile>
SqliteService * SqliteService::m_pSqliteService = nullptr;

SqliteService *SqliteService::GetInstance()
{
    if (m_pSqliteService == nullptr){
        m_pSqliteService =new SqliteService;
    }
    return m_pSqliteService;
}

void SqliteService::DestoryInstance()
{
    delete m_pSqliteService;
}

int SqliteService::StartTask(QString TaskID)
{
	QDateTime t_Dt = QDateTime::currentDateTime();
	SqlQuery_Mutex.lock();
	m_pSqlQuery->prepare("UPDATE main.TaskList SET StartTime = :StartTime WHERE ID=:ID;");
	m_pSqlQuery->bindValue(":ID", TaskID);
	m_pSqlQuery->bindValue(":StartTime", t_Dt.toTime_t());
	m_pSqlQuery->exec();
	QString ErrorInfo = m_pSqlQuery->lastError().text();
	SqlQuery_Mutex.unlock();
	return t_Dt.toTime_t();
}

int SqliteService::CreatTask(QString TaskID, QString TaskName, QString Content)
{
	SqlQuery_Mutex.lock();
	m_pSqlQuery->prepare("INSERT INTO main.TaskList(ID, Name, Content, TaskState, CreateTime, StartTime, EndTime, isDelete, DeleteTime) VALUES (:ID, :Name, :Content, :TaskState, :CreateTime, :StartTime, :EndTime, :isDelete, :DeleteTime);");
	m_pSqlQuery->bindValue(":ID", TaskID);
	m_pSqlQuery->bindValue(":Name", TaskName);
	m_pSqlQuery->bindValue(":Content", Content);
	m_pSqlQuery->bindValue(":TaskState", "");
	m_pSqlQuery->bindValue(":CreateTime", QDateTime::currentDateTime().toTime_t());
	m_pSqlQuery->bindValue(":StartTime", 0);
	m_pSqlQuery->bindValue(":EndTime", 0);
	m_pSqlQuery->bindValue(":isDelete", 0);
	m_pSqlQuery->bindValue(":DeleteTime", 0);
	m_pSqlQuery->exec();
	QString ErrorInfo = m_pSqlQuery->lastError().text();
	SqlQuery_Mutex.unlock();
	return 0;
}

int SqliteService::DeleteTask(QString TaskID)
{
	QDateTime t_Dt = QDateTime::currentDateTime();
	SqlQuery_Mutex.lock();
	m_pSqlQuery->prepare("UPDATE main.TaskList SET DeleteTime=:DeleteTime,isDelete=:isDelete WHERE ID=:ID;");
	m_pSqlQuery->bindValue(":ID", TaskID);
	m_pSqlQuery->bindValue(":DeleteTime", t_Dt.toTime_t());
	m_pSqlQuery->bindValue(":isDelete", 1);
	m_pSqlQuery->exec();
	QString ErrorInfo = m_pSqlQuery->lastError().text();
	SqlQuery_Mutex.unlock();
	return t_Dt.toTime_t();
}

int SqliteService::EndTask(QString TaskID)
{
	QDateTime t_Dt = QDateTime::currentDateTime();
	SqlQuery_Mutex.lock();
	m_pSqlQuery->prepare("UPDATE main.TaskList SET EndTime=:EndTime WHERE ID=:ID;");
	m_pSqlQuery->bindValue(":ID", TaskID);
	m_pSqlQuery->bindValue(":EndTime", t_Dt.toTime_t());
	m_pSqlQuery->exec();
	QString ErrorInfo = m_pSqlQuery->lastError().text();
	SqlQuery_Mutex.unlock();
	return t_Dt.toTime_t();
}

int SqliteService::ChangeTask(QString TaskID, QString Name, QString Content)
{
	SqlQuery_Mutex.lock();
	m_pSqlQuery->prepare("UPDATE main.TaskList SET Content=:Content,Name=:Name WHERE ID=:ID;");
	m_pSqlQuery->bindValue(":ID", TaskID);
	m_pSqlQuery->bindValue(":Name", Name);
	m_pSqlQuery->bindValue(":Content", Content);
	m_pSqlQuery->exec();
	QString ErrorInfo = m_pSqlQuery->lastError().text();
	SqlQuery_Mutex.unlock();
	return 0;
}

QList<TaskInfo> SqliteService::GetTask()
{
	QList<TaskInfo> ReturnVal;
	ReturnVal.clear();
	SqlQuery_Mutex.lock();
	m_pSqlQuery->prepare("SELECT * FROM main.TaskList");
	if (!m_pSqlQuery->exec()) {
		SqlQuery_Mutex.unlock();
		return ReturnVal;
	}
	while(m_pSqlQuery->next()) {
		TaskInfo t_TI;
		t_TI.ID = m_pSqlQuery->value("ID").toString();
		t_TI.Name = m_pSqlQuery->value("Name").toString();
		t_TI.Content = m_pSqlQuery->value("Content").toString();
		t_TI.State= m_pSqlQuery->value("TaskState").toString();
		t_TI.CreateTime = m_pSqlQuery->value("CreateTime").toUInt();
		t_TI.StartTime = m_pSqlQuery->value("StartTime").toUInt();
		t_TI.EndTime = m_pSqlQuery->value("EndTime").toUInt();
		t_TI.isDelete = m_pSqlQuery->value("isDelete").toUInt();
		t_TI.DeleteTime = m_pSqlQuery->value("DeleteTime").toUInt();
		ReturnVal.append(t_TI);
	}
	SqlQuery_Mutex.unlock();
	return ReturnVal;
}

QString SqliteService::GetWorkLog(QString Time)
{
	QString LogContent;

	SqlQuery_Mutex.lock();
	m_pSqlQuery->prepare("SELECT * FROM main.WorkLog WHERE Time=:Time;");
	m_pSqlQuery->bindValue(":Time", Time);
	if (!m_pSqlQuery->exec()) {
		SqlQuery_Mutex.unlock();
		return "";
	}
	if (m_pSqlQuery->first()) {
		LogContent = m_pSqlQuery->value("Content").toString();
		SqlQuery_Mutex.unlock();
	}
	else {
		SqlQuery_Mutex.unlock();
	}
	
	return LogContent;
}


int SqliteService::AddWorkLog(QString Time, QString LogContent)
{
	SqlQuery_Mutex.lock();
    m_pSqlQuery->prepare("SELECT * FROM main.WorkLog WHERE Time=:Time");
    m_pSqlQuery->bindValue(":Time",Time);
    m_pSqlQuery->exec();
	if (m_pSqlQuery->first()) {
		m_pSqlQuery->prepare("UPDATE main.WorkLog SET Content=:Content WHERE Time=:Time");
		m_pSqlQuery->bindValue(":Time", Time);
		m_pSqlQuery->bindValue(":Content", LogContent);
		if (!m_pSqlQuery->exec()) {
			SqlQuery_Mutex.unlock();
			return -1;
		}
		SqlQuery_Mutex.unlock();
	}
	else {
		m_pSqlQuery->prepare("INSERT INTO main.WorkLog(\"Time\", \"Content\") VALUES (:Time, :Content);");
		m_pSqlQuery->bindValue(":Time", Time);
		m_pSqlQuery->bindValue(":Content", LogContent);
		if (!m_pSqlQuery->exec()) {
			QString ErrorInfo = SqliteDataBase.lastError().text();
			SqlQuery_Mutex.unlock();
			return -1;
		}
		SqlQuery_Mutex.unlock();
	}
    return 0;
}

QStringList SqliteService::GetDirectoryList()
{
    QStringList RetVal;
    RetVal.clear();
    SqlQuery_Mutex.lock();
    m_pSqlQuery->prepare("SELECT * FROM main.DirectoryList;");
    if (!m_pSqlQuery->exec()){
        return RetVal;
    }
    while(m_pSqlQuery->next()){
        RetVal.append(m_pSqlQuery->value(0).toString());
    }
    SqlQuery_Mutex.unlock();
    return RetVal;
}

int SqliteService::UpdataFile(QStringList Directorys)
{
    SqlQuery_Mutex.lock();
    m_pSqlQuery->prepare("DELETE FROM main.DirectoryList");
    m_pSqlQuery->exec();
    //SqliteDataBase.transaction();
    foreach(auto var,Directorys){
        m_pSqlQuery->prepare("INSERT INTO main.DirectoryList (DirectoryPath) VALUES (:DirectoryPath)");
        m_pSqlQuery->bindValue(":DirectoryPath",var);
        m_pSqlQuery->exec();
    }
    //SqliteDataBase.commit();
    SqlQuery_Mutex.unlock();
    return 0;
}

void SqliteService::UpdataFileIndex(QList<FileIndex> FI)
{
	QSqlQuery t_sqlquery(SqliteDataBase);
	SqliteDataBase.transaction();
    foreach(auto var,FI){
		t_sqlquery.clear();
		t_sqlquery.prepare("INSERT INTO main.FileIndex (IndexKey,Name,Path,Size,Type,CreationTime,ChangeTime,InterviewTime) VALUES (:IndexKey,:Name,:Path,:Size,:Type,:CreationTime,:ChangeTime,:InterviewTime);");
		t_sqlquery.bindValue(":IndexKey",var.Key);
		t_sqlquery.bindValue(":Name",var.Name);
		t_sqlquery.bindValue(":Path",var.Path);
		t_sqlquery.bindValue(":Size",var.Size);
		t_sqlquery.bindValue(":Type","."+var.Type);
		t_sqlquery.bindValue(":CreationTime",var.CreationTime);
		t_sqlquery.bindValue(":ChangeTime",var.ChangeTime);
		t_sqlquery.bindValue(":InterviewTime",var.InterviewTime);
		t_sqlquery.exec();
		QString ErrorStr = t_sqlquery.lastError().text();
    }
	SqliteDataBase.commit();
}

QStringList SqliteService::GetAllFileType()
{
    QStringList Types;
    Types.clear();
    SqlQuery_Mutex.lock();
    m_pSqlQuery->prepare("select distinct type from main.FileIndex");
    if (!m_pSqlQuery->exec()){
        return Types;
    }
    while(m_pSqlQuery->next()){
        Types.append(m_pSqlQuery->value(0).toString());
    }
	SqlQuery_Mutex.unlock();
    return Types;
}

void SqliteService::SetToolsInfo(QList<ToolsInfo> Tools)
{
	SqlQuery_Mutex.lock();
	m_pSqlQuery->prepare("DELETE FROM main.ShortcutPath");
	m_pSqlQuery->exec();
	foreach(auto var, Tools) {
		m_pSqlQuery->prepare("INSERT INTO main.ShortcutPath(ToolBtnObjName,TagPath) VALUES (:ToolBtnObjName, :TagPath)");
		m_pSqlQuery->bindValue(":ToolBtnObjName", var.Name);
		m_pSqlQuery->bindValue(":TagPath", var.Path);
		m_pSqlQuery->exec();
	}
	SqlQuery_Mutex.unlock();
}

QList<ToolsInfo> SqliteService::GetToolsInfo()
{
	QList<ToolsInfo> t_RetuanVal;
	t_RetuanVal.clear();

	SqlQuery_Mutex.lock();
	m_pSqlQuery->prepare("SELECT * FROM main.ShortcutPath;");
	m_pSqlQuery->exec();
	ToolsInfo t_StrList;
	while (m_pSqlQuery->next()) {
		t_StrList.Name = m_pSqlQuery->value("ToolBtnObjName").toString();
		t_StrList.Path = m_pSqlQuery->value("TagPath").toString();
		t_RetuanVal.append(t_StrList);
	}
	SqlQuery_Mutex.unlock();
	return t_RetuanVal;
}

SqliteService::SqliteService()
{

}

SqliteService::~SqliteService()
{
    SqliteDataBase.close();
}

void SqliteService::Init()
{

}

int SqliteService::OpenDataBase()
{
	SqliteDataBase = QSqlDatabase::addDatabase("QSQLITE");
	SqliteDataBase.setDatabaseName("DevelopmentToolBox.db");
	if (!SqliteDataBase.open()) {
		return -1;
	}
	else {
		m_pSqlQuery = new QSqlQuery(SqliteDataBase);
	}
    if (!SqliteDataBase.tables().contains("ShortcutPath") || !SqliteDataBase.tables().contains("WorkLog")||!SqliteDataBase.tables().contains("TaskList")){
        QFile SqlFie(":/DataBaseInit.sql");
        SqlFie.open(QIODevice::ReadOnly);
        QStringList Sqls = QString(SqlFie.readAll()).split(";");
        foreach(auto var,Sqls){
            m_pSqlQuery->prepare(var);
            m_pSqlQuery->exec();
        }
    }
	return 0;
}
