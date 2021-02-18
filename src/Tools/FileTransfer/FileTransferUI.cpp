#include "FileTransferUI.h"
#include "ui_FileTransferUI.h"

FileTransferUI::FileTransferUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileTransferUI)
{
    ui->setupUi(this);
}

FileTransferUI::~FileTransferUI()
{
    delete ui;
}
