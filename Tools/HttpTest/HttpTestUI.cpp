#include "HttpTestUI.h"
#include "ui_HttpTestUI.h"

HttpTestUI::HttpTestUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HttpTestUI)
{
    ui->setupUi(this);
}

HttpTestUI::~HttpTestUI()
{
    delete ui;
}
