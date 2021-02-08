#include "FileMessage.h"
#include "ui_FileMessage.h"

FileMessage::FileMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileMessage)
{
    ui->setupUi(this);
}

FileMessage::~FileMessage()
{
    delete ui;
}
