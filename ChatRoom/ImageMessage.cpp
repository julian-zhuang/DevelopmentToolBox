#include "ImageMessage.h"
#include "ui_ImageMessage.h"

ImageMessage::ImageMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageMessage)
{
    ui->setupUi(this);
}

ImageMessage::~ImageMessage()
{
    delete ui;
}
