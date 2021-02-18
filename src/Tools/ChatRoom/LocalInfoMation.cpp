#include "LocalInfoMation.h"
#include "ui_LocalInfoMation.h"

LocalInfoMation::LocalInfoMation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LocalInfoMation)
{
    ui->setupUi(this);
}

LocalInfoMation::~LocalInfoMation()
{
    delete ui;
}
