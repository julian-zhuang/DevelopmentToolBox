#include "RaspberryPiGPIOUI.h"
#include "ui_RaspberryPiGPIOUI.h"

RaspberryPiGPIOUI::RaspberryPiGPIOUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RaspberryPiGPIOUI)
{
    ui->setupUi(this);
}

RaspberryPiGPIOUI::~RaspberryPiGPIOUI()
{
    delete ui;
}
