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

    int CreatTask(QString TaskID,QString TaskName,QString Content);
    int StartTask(QString TaskID);
    int DeleteTask(QString TaskID);
    int EndTask(QString TaskID);
	int ChangeTask(QString TaskID, QString Name, QString Content);
    QList<TaskInfo> GetTask();

    void SetToolsInfo(QList<ToolsInfo> Tools);
    QList<ToolsInfo> GetToolsInfo();

	QString GetWorkLog(QString Time);
    int AddWorkLog(QString Time,QString LogContent);

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