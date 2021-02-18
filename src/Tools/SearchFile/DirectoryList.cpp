#include "DirectoryList.h"
#include "ui_DirectoryList.h"
#include <QFileDialog>
#include <QTreeWidgetItemIterator>
DirectoryList::DirectoryList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DirectoryList)
{
    ui->setupUi(this);
	connect(ui->pushButton_Commit, SIGNAL(clicked()), this, SLOT(Slot_CommitClicked()));
	connect(ui->pushButton_Cancel, SIGNAL(clicked()), this, SLOT(Slot_CancelClick()));
	connect(ui->pushButton_Add, SIGNAL(clicked()), this, SLOT(Slot_AddPathClick()));
	connect(ui->pushButton_Del, SIGNAL(clicked()), this, SLOT(Slot_DeletePathClick()));
}

DirectoryList::~DirectoryList()
{
    delete ui;
}

QStringList DirectoryList::GetDirectory()
{
    QStringList RetVal;
    QTreeWidgetItemIterator it(ui->treeWidget);
    while(*it){
        RetVal.append((*it)->text(0));
		++it;
    }
    return RetVal;
}

void DirectoryList::SetDirectoryList(QStringList PathList)
{
    ui->treeWidget->clear();
    QTreeWidgetItem * t_TWI;
    foreach(auto var,PathList){
        t_TWI = new QTreeWidgetItem(ui->treeWidget);
        t_TWI->setText(0,var);
        ui->treeWidget->addTopLevelItem(t_TWI);
    }
}

void DirectoryList::Slot_AddPathClick()
{
    QString Path = QFileDialog::getExistingDirectory(this);
    QTreeWidgetItem * t_TWI;
    t_TWI = new QTreeWidgetItem(ui->treeWidget);
    t_TWI->setText(0,Path);
    ui->treeWidget->addTopLevelItem(t_TWI);
}

void DirectoryList::Slot_DeletePathClick()
{
    if (ui->treeWidget->currentItem() != nullptr){
        delete ui->treeWidget->currentItem();
    }
}

void DirectoryList::Slot_CommitClicked()
{
    this->close();
}

void DirectoryList::Slot_CancelClick()
{
    this->close();
}
