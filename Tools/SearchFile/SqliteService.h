#ifndef SQLITESERVICE_H
#define SQLITESERVICE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMutex>

struct TaskInfo{
    QString ID;
    QString Name;
	QString Content;
	QString State;
    unsigned int CreateTime;
    unsigned int StartTime;
    unsigned int EndTime;
    unsigned int isDelete;
    unsigned int DeleteTime;
};

struct FileIndex{
    QString Key;
    QString Name;
    QString Path;
    unsigned int Size;
    QString Type;
    unsigned int CreationTime;
    unsigned int ChangeTime;
    unsigned int InterviewTime;
};

struct ToolsInfo{
    QString Name;
    QString Path;
};

class SqliteService
{
public:
    static SqliteService* GetInstance();
    static void DestoryInstance();

    QStringList GetDirectoryList();
    int UpdataFile(QStringList Directorys);

    void UpdataFileIndex(QList<FileIndex> FI);
    QStringList GetAllFileType();

    void Init();
	int OpenDataBase();
	QSqlQuery * m_pSqlQuery;

private:
	QMutex SqlQuery_Mutex;
    static SqliteService *m_pSqliteService;
    SqliteService();
    ~SqliteService();
private:
    QSqlDatabase SqliteDataBase;
};

#endif // SQLITESERVICE_H
