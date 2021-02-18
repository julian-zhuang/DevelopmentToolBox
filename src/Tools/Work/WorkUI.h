#ifndef WORKLOGUI_H
#define WORKLOGUI_H

#include <QWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QFileDialog>
#include <QToolButton>
#include <QUuid>
#include <QFileIconProvider>
#include <QHBoxLayout>
#include <QMenu>
#include <QDomComment>
#include <QDomNode>
#include <QFile>
#include <QTextStream>
namespace Ui {
class WorkUI;
}

class WorkUI : public QWidget
{
    Q_OBJECT
private slots:
    void Slot_ButtonClicked();
    void Slot_TodayTimeUpdata();
    void Slot_MenuClick(QAction *action);
    void Slot_ShowMenu(const QPoint &pos);
    void Slot_TextChange();
public:
    explicit WorkUI(QWidget *parent = 0);
    ~WorkUI();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::WorkUI *ui;

    QToolButton * FocusToolBtn;
    QMenu *m_TaskListMenu;
    QAction * ListWig_ModifyIcon;
    QAction * ListWig_Delete;

    QHBoxLayout *t_Layout;
    QMap<QWidget *, QString> Toolbtn_FilePath;
    QMap<QWidget *, QString> Toolbtn_FileName;
    QMap<QWidget *, QString> Toolbtn_FileIcon;
    QMap<QString, QString> DateStr_LogConnect;
    QTimer m_TodayTimeUpdata;

    QMap<QString, unsigned int> StartWorkTime;
    QMap<QString, unsigned int> StopWorkTime;
private:
    QDomNode FindNode(QDomNode &Node,QString NodeName);
};

#endif // WORKLOGUI_H
