#include "TaskEdit.h"
#include "ui_TaskEdit.h"
#include <QUuid>

TaskEdit::TaskEdit(QString TaskName,QString Taskcontent, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskEdit)
{
    ui->setupUi(this);
    if (TaskName == ""){
        this->setWindowTitle(tr("Creat Task"));
		TaskID = QUuid::createUuid().toString();
    }else{
        this->setWindowTitle(tr("Edit Task"));
    }
    this->TaskName = TaskName;
    this->Taskcontent = Taskcontent;
    ui->lineEdit_TaskName->setText(this->TaskName);
    ui->textEdit_TaskContent->setText(this->Taskcontent);
	connect(ui->lineEdit_TaskName, SIGNAL(textChanged(const QString &)), this, SLOT(Slot_TextChange(const QString &)));
	connect(ui->textEdit_TaskContent,SIGNAL(textChanged()),this,SLOT(Slot_TextChange()));
}

TaskEdit::~TaskEdit()
{
    delete ui;
}

void TaskEdit::Slot_TextChange()
{
	this->Taskcontent = ui->textEdit_TaskContent->toPlainText();
}

void TaskEdit::Slot_TextChange(const QString &)
{
    this->TaskName = ui->lineEdit_TaskName->text();
}
