#include "TaskWidget.h"
#include "ui_TaskWidget.h"
#include <QDateTime>

TaskWidget::TaskWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskWidget)
{
    ui->setupUi(this);
	ui->label_StateTime->setText("");
}

TaskWidget::~TaskWidget()
{
    delete ui;
}

void TaskWidget::SetTaskName(QString Str)
{
	ui->label_TaskName->setText(Str);
}

void TaskWidget::SetTaskContent(QString Str)
{
    ui->label_TaskContent->setText(Str);
}

void TaskWidget::SetTaskState(QString Str)
{
	ui->label_StateTime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->labelTaskState->setText(Str);
}

QString TaskWidget::GetTaskName()
{
    return ui->label_TaskName->text();
}

QString TaskWidget::GetTaskContent()
{
    return ui->label_TaskContent->text();
}

QString TaskWidget::GetTaskState()
{
    return ui->labelTaskState->text();
}
