#include "GroupInfoCard.h"
#include "ui_GroupInfoCard.h"

GroupInfoCard::GroupInfoCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupInfoCard)
{
    ui->setupUi(this);
}

GroupInfoCard::~GroupInfoCard()
{
    delete ui;
}
