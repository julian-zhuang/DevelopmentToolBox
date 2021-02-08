#include "TabButton.h"
#include "ui_TabButton.h"

TabButton::TabButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabButton)
{
    ui->setupUi(this);
}

TabButton::~TabButton()
{
    delete ui;
}
