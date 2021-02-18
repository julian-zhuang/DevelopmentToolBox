#include "TerminalUI.h"
#include "ui_TerminalUI.h"

TerminalUI::TerminalUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TerminalUI)
{
    ui->setupUi(this);
}

TerminalUI::~TerminalUI()
{
    delete ui;
}
