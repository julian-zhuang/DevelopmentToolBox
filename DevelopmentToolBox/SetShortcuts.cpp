#include "SetShortcuts.h"
#include "ui_SetShortcuts.h"
#include <QFileDialog>
SetShortcuts::SetShortcuts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetShortcuts)
{
    ui->setupUi(this);
}

SetShortcuts::~SetShortcuts()
{
    delete ui;
}
