#ifndef WORKING_H
#define WORKING_H

#include <QWidget>
#include <QTimer>
#include <QMenu>
#include "SqliteService.h"
#include <QMap>
#include<QHBoxLayout>

namespace Ui {
class Working;
}

class Working : public QWidget
{
    Q_OBJECT

public:
    explicit Working(QWidget *parent = nullptr);
    ~Working();
private slots:
    void Slot_TodayTimeUpdata();
    void Slot_MenuClick(QAction *action);
    void Slot_ShowMenu(const QPoint &pos);
	void Slot_EditingFinished();
	void Slot_TextChange();
	void Slot_DateTimeChanged(const QDateTime &datetime);
	void Slot_ButtonClicked();
private:
    void InitToolBar();
	void TasklistUpdata();
private:
	QTimer m_timerTextEditChange;
	
    QWidget *CurrentSelection;
    QTimer m_TodayTimeUpdata;
	QMenu *m_ToolMenu;
	QMenu *m_TaskListMenu;
    Ui::Working *ui;
	QToolButton *t_ToolButton;
	QHBoxLayout *t_Layout;

	//工具栏
	QAction *Tool_Delete;

	//任务列表
	QAction *ListWig_Creat;
	QAction *ListWig_Edit;
	QAction *ListWig_Delete;
	QAction *ListWig_Start;
	QAction *ListWig_Complete;
protected:
	QMap<QWidget *, QString> Toolbtn_FilePath;
	bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // WORKING_H
