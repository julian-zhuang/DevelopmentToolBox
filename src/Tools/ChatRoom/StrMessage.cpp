#include "StrMessage.h"
#include "ui_StrMessage.h"

StrMessage::StrMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StrMessage)
{
    ui->setupUi(this);
}

StrMessage::~StrMessage()
{
    delete ui;
}
