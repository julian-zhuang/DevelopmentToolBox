#include "RaspberryPiGPIOUI.h"
#include "ui_RaspberryPiGPIOUI.h"
#include <QDebug>
#include <QHostAddress>

RaspberryPiGPIOUI::RaspberryPiGPIOUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RaspberryPiGPIOUI)
{
    ui->setupUi(this);
    IsConnect = false;
    connect(&TCPSocket,SIGNAL(connected()),this,SLOT(Slot_Connected()));
    connect(&TCPSocket,SIGNAL(disconnected()),this,SLOT(Slot_Disconnected()));
    connect(&TCPSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));
    connect(&TCPSocket,SIGNAL(readyRead()),this,SLOT(Slot_ReadyRead()));
    connect(ui->pushButton_connect,SIGNAL(clicked()),this,SLOT(Slto_Clicked()));
    for (int i = 1 ; i <= 40 ; i++){
        QRadioButton *RadioBtn_HIG = this->findChild<QRadioButton*>("radioBtn_HIG_" + QString::number(i));
        QRadioButton *RadioBtn_LOW = this->findChild<QRadioButton*>("radioBtn_LOW_" + QString::number(i));
        if (RadioBtn_HIG != nullptr && RadioBtn_LOW != nullptr ){
            QButtonGroup *p_QButtonGroup = new QButtonGroup;
            p_QButtonGroup->addButton(RadioBtn_HIG);
            p_QButtonGroup->addButton(RadioBtn_LOW);
            connect(p_QButtonGroup,SIGNAL(buttonToggled(QAbstractButton*,bool)),this,SLOT(Slot_ButtonToggled(QAbstractButton*,bool)));
        }
        QRadioButton *RadioBtn_IN = this->findChild<QRadioButton*>("radioBtn_IN_" + QString::number(i));
        QRadioButton *RadioBtn_OUT = this->findChild<QRadioButton*>("radioBtn_OUT_" + QString::number(i));
        if (RadioBtn_IN != nullptr && RadioBtn_OUT != nullptr ){
            QButtonGroup *p_QButtonGroup = new QButtonGroup;
            p_QButtonGroup->addButton(RadioBtn_IN);
            p_QButtonGroup->addButton(RadioBtn_OUT);
            connect(p_QButtonGroup,SIGNAL(buttonToggled(QAbstractButton*,bool)),this,SLOT(Slot_ButtonToggled(QAbstractButton*,bool)));
        }
        QLineEdit *LineEdit = this->findChild<QLineEdit*>("lineEdit_Note_" + QString::number(i));
        if (LineEdit != nullptr){
            connect(LineEdit,SIGNAL(textChanged(QString)),this,SLOT(Slot_TextChanged(QString)));
        }
    }
}

RaspberryPiGPIOUI::~RaspberryPiGPIOUI()
{
    delete ui;
}

void RaspberryPiGPIOUI::Slot_ButtonToggled(QAbstractButton *button, bool checked)
{
    QString ObjName = button->objectName();
    QStringList StrList = ObjName.split("_");
    if (StrList[1] == "HIG"){
        qDebug() << StrList << checked;
    }
    if (StrList[1] == "LOW"){
        qDebug() << StrList << checked;
    }
    if (StrList[1] == "IN"){
        qDebug() << StrList << checked;
    }
    if (StrList[1] == "OUT"){
        qDebug() << StrList << checked;
    }
}

void RaspberryPiGPIOUI::Slot_TextChanged(const QString &text)
{
    QLineEdit *LineEdit = (QLineEdit *)sender();
    QString ObjName = LineEdit->objectName();
    qDebug() << ObjName;
    ObjName_Text[ObjName] = text;
}

void RaspberryPiGPIOUI::Slto_Clicked()
{
    if (IsConnect == false){
        TCPSocket.connectToHost(QHostAddress(ui->lineEdit_Addr->text()),ui->spinBox_Port->value());
    }else{
        TCPSocket.disconnect();
        TCPSocket.close();
    }
}

void RaspberryPiGPIOUI::Slot_Connected()
{
    IsConnect = true;
    QByteArray WaitData;
    WaitData.clear();
    WaitData.append(0x10);
    QString UserPassWD = ui->lineEdit_Username->text() + '@' +ui->lineEdit_Password->text();
    WaitData.append(UserPassWD.toUtf8());
    TCPSocket.write(WaitData);
    ui->pushButton_connect->setText("Disconnect");
    ui->lineEdit_Addr->setEnabled(false);
    ui->lineEdit_Username->setEnabled(false);
    ui->lineEdit_Password->setEnabled(false);
}

void RaspberryPiGPIOUI::Slot_Disconnected()
{
    IsConnect = false;
    ui->pushButton_connect->setText("Connect");
    ui->lineEdit_Addr->setEnabled(true);
    ui->lineEdit_Username->setEnabled(true);
    ui->lineEdit_Password->setEnabled(true);
}

void RaspberryPiGPIOUI::Slot_Error(QAbstractSocket::SocketError socketError)
{

}

void RaspberryPiGPIOUI::Slot_ReadyRead()
{

}
