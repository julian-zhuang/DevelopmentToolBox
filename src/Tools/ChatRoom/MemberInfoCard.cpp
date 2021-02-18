#include "MemberInfoCard.h"
#include "ui_MemberInfoCard.h"

MemberInfoCard::MemberInfoCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemberInfoCard)
{
    ui->setupUi(this);
}

MemberInfoCard::~MemberInfoCard()
{
    delete ui;
}
