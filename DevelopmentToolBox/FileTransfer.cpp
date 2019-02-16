#include "FileTransfer.h"
#include "ui_FileTransfer.h"

FileTransfer::FileTransfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileTransfer)
{
    ui->setupUi(this);
}

FileTransfer::~FileTransfer()
{
    delete ui;
}
