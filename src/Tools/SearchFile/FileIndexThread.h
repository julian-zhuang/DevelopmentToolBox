#ifndef FILEINDEXTHREAD_H
#define FILEINDEXTHREAD_H
#include <QThread>
#include <QList>
#include "SqliteService.h"
class FileIndexThread : public QThread
{
	Q_OBJECT
signals:
	void Sig_ThreadFinish();
	void Sig_FindFile(QString FileName, int);
	void Sig_Indexing();
public:
    FileIndexThread() = delete;
    FileIndexThread(QStringList Paths){m_Paths = Paths;}
    void run() override;
private:
	QList<FileIndex> m_Fileindex;
    QStringList m_Paths;
    void TraverseDirectory (QString Path);
};

#endif // FILEINDEXTHREAD_H