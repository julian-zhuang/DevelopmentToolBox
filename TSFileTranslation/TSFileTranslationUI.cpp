#include "TSFileTranslationUI.h"
#include "ui_TSFileTranslationUI.h"

TSFileTranslationUI::TSFileTranslationUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TSFileTranslationUI)
{
    ui->setupUi(this);
}

TSFileTranslationUI::~TSFileTranslationUI()
{
    delete ui;
}
