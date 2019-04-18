#include "FileIndexThread.h"
#include <QDir>
#include <QDateTime>
#include <QCryptographicHash>
#include <SqliteService.h>
void FileIndexThread::run()
{
    m_Fileindex.clear();
    foreach(auto var,m_Paths){
        TraverseDirectory(var);
    }
	emit Sig_Indexing();
	SqliteService::GetInstance()->UpdataFileIndex(m_Fileindex);
	emit Sig_ThreadFinish();
}

void FileIndexThread::TraverseDirectory(QString Path)
{
    QDir dir;
    dir.setPath (Path);
    QFileInfoList list = dir.entryInfoList ();
    for ( int i = 0 ; i < list.size (); ++ i) {
        QFileInfo fileInfo = list.at (i);
        if (fileInfo.isFile ()) {
            FileIndex t_FI;
			auto jk = QCryptographicHash::hash(fileInfo.filePath().toLatin1(), QCryptographicHash::Md5);
            t_FI.Key = QCryptographicHash::hash(fileInfo.filePath().toLatin1(),QCryptographicHash::Md5).toHex();
            t_FI.Name = fileInfo.fileName();
            t_FI.Path = fileInfo.path();
            t_FI.Type = fileInfo.suffix();
            t_FI.Size = fileInfo.size();
            t_FI.ChangeTime = fileInfo.created().toTime_t();
            t_FI.ChangeTime = fileInfo.lastModified().toTime_t();
            t_FI.InterviewTime = fileInfo.lastRead().toTime_t();
            m_Fileindex.append(t_FI);
			emit Sig_FindFile(t_FI.Name, m_Fileindex.count());
        }
        else {
            if (fileInfo.fileName () == "." || fileInfo.fileName () == ".." ) {
             continue ;
            }
            TraverseDirectory (fileInfo.absoluteFilePath ()); //递归调用
        }
    }
}
