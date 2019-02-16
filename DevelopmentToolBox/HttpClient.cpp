#include "HttpClient.h"
#include "ui_HttpClient.h"

HttpClient::HttpClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HttpClient)
{
    ui->setupUi(this);
}

HttpClient::~HttpClient()
{
    delete ui;
}
