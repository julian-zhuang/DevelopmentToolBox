#include "CharacterEncodingUI.h"
#include "ui_CharacterEncodingUI.h"
#include <QCryptographicHash>
#include <QByteArray>

void CharacterEncodingUI::Slot_HashTextChange()
{
    QByteArray SrcByttery = ui->textEdit_Hash_Src->toPlainText().toUtf8();
    if (ui->comboBox_Algorithm->currentText() == "MD4"){
        ui->textEdit_Hash_Des->setText(QCryptographicHash::hash(SrcByttery,QCryptographicHash::Md4).toHex());
        return;
    }
    if (ui->comboBox_Algorithm->currentText() == "MD5"){
        ui->textEdit_Hash_Des->setText(QCryptographicHash::hash(SrcByttery,QCryptographicHash::Md5).toHex());
        return;
    }
    if (ui->comboBox_Algorithm->currentText() == "SHA1"){
        ui->textEdit_Hash_Des->setText(QCryptographicHash::hash(SrcByttery,QCryptographicHash::Sha1).toHex());
        return;
    }
    if (ui->comboBox_Algorithm->currentText() == "SHA224"){
        ui->textEdit_Hash_Des->setText(QCryptographicHash::hash(SrcByttery,QCryptographicHash::Sha224).toHex());
        return;
    }
    if (ui->comboBox_Algorithm->currentText() == "SHA256"){
        ui->textEdit_Hash_Des->setText(QCryptographicHash::hash(SrcByttery,QCryptographicHash::Sha256).toHex());
        return;
    }
    if (ui->comboBox_Algorithm->currentText() == "SHA384"){
        ui->textEdit_Hash_Des->setText(QCryptographicHash::hash(SrcByttery,QCryptographicHash::Sha384).toHex());
        return;
    }
    if (ui->comboBox_Algorithm->currentText() == "SHA512"){
        ui->textEdit_Hash_Des->setText(QCryptographicHash::hash(SrcByttery,QCryptographicHash::Sha512).toHex());
        return;
    }
    if (ui->comboBox_Algorithm->currentText() == "SHA3_224"){
        ui->textEdit_Hash_Des->setText(QCryptographicHash::hash(SrcByttery,QCryptographicHash::Sha3_224).toHex());
        return;
    }
    if (ui->comboBox_Algorithm->currentText() == "SHA3_256"){
        ui->textEdit_Hash_Des->setText(QCryptographicHash::hash(SrcByttery,QCryptographicHash::Sha3_256).toHex());
        return;
    }
    if (ui->comboBox_Algorithm->currentText() == "SHA3_384"){
        ui->textEdit_Hash_Des->setText(QCryptographicHash::hash(SrcByttery,QCryptographicHash::Sha3_384).toHex());
        return;
    }
    if (ui->comboBox_Algorithm->currentText() == "SHA3_512"){
        ui->textEdit_Hash_Des->setText(QCryptographicHash::hash(SrcByttery,QCryptographicHash::Sha3_512).toHex());
        return;
    }
}

void CharacterEncodingUI::Slot_TranscodingTextChange()
{
    QByteArray SrcByttery = ui->textEdit_Transcoding_Src->toPlainText().toUtf8();
    if(ui->comboBox_Coding->currentText() == "BASE64"){
        ui->textEdit_Transcoding_Des->setText(SrcByttery.toBase64());
    }
    if(ui->comboBox_Coding->currentText() == "HEX"){
        ui->textEdit_Transcoding_Des->setText(SrcByttery.toHex());
    }
}

CharacterEncodingUI::CharacterEncodingUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterEncodingUI)
{
    ui->setupUi(this);
    connect(ui->textEdit_Hash_Src,SIGNAL(textChanged()),this,SLOT(Slot_HashTextChange()));
    connect(ui->comboBox_Algorithm,SIGNAL(currentIndexChanged(int)),this,SLOT(Slot_HashTextChange()));
    connect(ui->textEdit_Transcoding_Src,SIGNAL(textChanged()),this,SLOT(Slot_TranscodingTextChange()));
    connect(ui->comboBox_Coding,SIGNAL(currentIndexChanged(int)),this,SLOT(Slot_TranscodingTextChange()));
}

CharacterEncodingUI::~CharacterEncodingUI()
{
    delete ui;
}
