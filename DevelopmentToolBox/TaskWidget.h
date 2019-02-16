#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>

namespace Ui {
class TaskWidget;
}

class TaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskWidget(QWidget *parent = nullptr);
    ~TaskWidget();
	void SetTaskName(QString Str);
	void SetTaskContent(QString Str);
	void SetTaskState(QString Str);

    QString GetTaskName();
    QString GetTaskContent();
    QString GetTaskState();
private:
    Ui::TaskWidget *ui;
};

#endif // TASKWIDGET_H
