#include "TranslationAPI.h"
#include "ui_TranslationAPI.h"

TranslationAPI::TranslationAPI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TranslationAPI)
{
    Url = "";
    APIID = "";;
    APIKey = "";;
    FromLan = "";;
    ToLan = "";
    EnableAPI = true;
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(Slot_accepted()));
    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(Slot_rejected()));
}

TranslationAPI::~TranslationAPI()
{
    delete ui;
}

void TranslationAPI::Slot_accepted()
{
    Url = ui->lineEdit_Url->text();
    APIID = ui->lineEdit_ApiID->text();
    APIKey = ui->lineEdit_APIKey->text();
    FromLan = ui->lineEdit_From->text();
    ToLan = ui->lineEdit_To->text();
    IsAccepted = true;
    if (ui->checkBox_EnableAPI->checkState() == Qt::Checked){
        EnableAPI = true;
    }else{
        EnableAPI = false;
    }
    this->close();
}

void TranslationAPI::Slot_rejected()
{
    IsAccepted = false;
    this->close();
}

void TranslationAPI::Init()
{
    ui->lineEdit_Url->setText(Url);
    ui->lineEdit_ApiID->setText(APIID);
    ui->lineEdit_APIKey->setText(APIKey);
    ui->lineEdit_From->setText(FromLan);
    ui->lineEdit_To->setText(ToLan);
    IsAccepted = false;
    if (EnableAPI == true){
        ui->checkBox_EnableAPI->setEnabled(Qt::Checked);
        ui->checkBox_EnableAPI->toggled(true);
    }else{
        ui->checkBox_EnableAPI->setEnabled(Qt::Unchecked);
        ui->checkBox_EnableAPI->toggled(false);
    }
}
