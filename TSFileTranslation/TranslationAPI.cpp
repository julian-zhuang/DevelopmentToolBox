#include "TranslationAPI.h"
#include "ui_TranslationAPI.h"

TranslationAPI::TranslationAPI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TranslationAPI)
{
    ui->setupUi(this);
}

TranslationAPI::~TranslationAPI()
{
    delete ui;
}
