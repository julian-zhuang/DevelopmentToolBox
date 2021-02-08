#include "SqliteService.h"
#include <QDateTime>
#include <QtDebug>
#include <QMessageBox>
#include <quuid.h>
#include <QFile>
#include <QApplication>

SqliteService * SqliteService::m_pSqliteService = nullptr;

SqliteService *SqliteService::GetInstance()
{
    if (m_pSqliteService == nullptr){
        m_pSqliteService = new SqliteService;
    }
    return m_pSqliteService;
}

void SqliteService::DestoryInstance()
{
    delete m_pSqliteService;
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

SqliteService::SqliteService()
{
    OpenDataBase();
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
    SqliteDataBase.setDatabaseName(QApplication::applicationDirPath() + "/SearchFile/SearchFile.db");
	if (!SqliteDataBase.open()) {
        QString kl = SqliteDataBase.lastError().text();
        return -1;
	}
	else {
		m_pSqlQuery = new QSqlQuery(SqliteDataBase);
	}
    if (!SqliteDataBase.tables().contains("FileIndex") || !SqliteDataBase.tables().contains("DirectoryList")){
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
