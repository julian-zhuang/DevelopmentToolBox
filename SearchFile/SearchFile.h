#ifndef SEARCHFILE_H
#define SEARCHFILE_H

#include <QWidget>
#include "FileIndexThread.h"
#include <QSqlQueryModel>
#include <QTimer>
#include <QMenu>
namespace Ui {
class SearchFile;
}

class SearchFile : public QWidget
{
    Q_OBJECT
public slots:
    void Slot_SearchDirectoryConfig();
	void Slot_UpdataClick();
	void Slot_FileIndexThreadFinish();
	void Slot_FindFile(QString FileName,int Count);
	void Slot_Indexing();
	void Slot_AdvCheckBoxClick(bool Check);
	void Slot_LineEditTextChange(const QString &text);
	void Slot_TimeOut();
	void Slot_ShowMenu(const QPoint &pos);
	void Slot_MenuClick(QAction *Action);
	//void Slot_customContextMenuRequested(const QPoint &pos);
public:
    explicit SearchFile(QWidget *parent = nullptr);
    ~SearchFile();

private:
    Ui::SearchFile *ui;
	FileIndexThread *t_FileIndexThread;
	QSqlQueryModel * m_pModel;
	QTimer ChangeTimer;
	QMenu m_TableViewMenu;
};

#endif // SEARCHFILE_H
