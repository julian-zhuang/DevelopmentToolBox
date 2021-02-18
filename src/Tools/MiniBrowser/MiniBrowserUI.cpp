#include "MiniBrowserUI.h"
#include "ui_MiniBrowserUI.h"

MiniBrowserUI::MiniBrowserUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MiniBrowserUI)
{
    ui->setupUi(this);
}

MiniBrowserUI::~MiniBrowserUI()
{
    delete ui;
}
