#include "RaspberryPiGPIOUI.h"
#include "ui_RaspberryPiGPIOUI.h"
#include <QDebug>
#include <QHostAddress>
#include <QStringList>

RaspberryPiGPIOUI::RaspberryPiGPIOUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RaspberryPiGPIOUI)
{
    ui->setupUi(this);
    Board_WiringPI[3] = 8;
    Board_WiringPI[5] = 9;
    Board_WiringPI[7] = 7;
    Board_WiringPI[11] = 0;
    Board_WiringPI[13] = 2;
    Board_WiringPI[15] = 3;
    Board_WiringPI[19] = 12;
    Board_WiringPI[21] = 13;
    Board_WiringPI[23] = 14;
    Board_WiringPI[27] = 30;
    Board_WiringPI[29] = 21;
    Board_WiringPI[31] = 22;
    Board_WiringPI[33] = 23;
    Board_WiringPI[35] = 24;
    Board_WiringPI[37] = 25;

    Board_WiringPI[8] = 15;
    Board_WiringPI[10] = 16;
    Board_WiringPI[12] = 1;
    Board_WiringPI[16] = 4;
    Board_WiringPI[18] = 5;
    Board_WiringPI[22] = 6;
    Board_WiringPI[24] = 10;
    Board_WiringPI[26] = 11;
    Board_WiringPI[28] = 31;
    Board_WiringPI[32] = 26;
    Board_WiringPI[36] = 27;
    Board_WiringPI[38] = 28;
    Board_WiringPI[40] = 29;

    for (auto i = Board_WiringPI.begin(); i != Board_WiringPI.end(); ++i){
        WiringPI_Board[i.value()] = i.key();
    }

    IsConnect = false;
    connect(this,SIGNAL(Sig_RecvData()),this,SLOT(Slot_RecvData()));
    connect(&TCPSocket,SIGNAL(connected()),this,SLOT(Slot_Connected()));
    connect(&TCPSocket,SIGNAL(disconnected()),this,SLOT(Slot_Disconnected()));
    connect(&TCPSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));
    connect(&TCPSocket,SIGNAL(readyRead()),this,SLOT(Slot_ReadyRead()));
    connect(ui->pushButton_connect,SIGNAL(clicked()),this,SLOT(Slto_Clicked()));
    connect(&CommandTimer,SIGNAL(timeout()),this,SLOT(Slot_TimeOut()));
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

void RaspberryPiGPIOUI::Slot_RecvData()
{
    while(RecvedData.length()){
        char Command = RecvedData.mid(0,1).toInt();;
        RecvedData.remove(0,1);
        switch (Command) {
        case 0x30:
        {
            char IO = RecvedData.mid(0,1).toInt();
            RecvedData.remove(0,1);
            IO = WiringPI_Board[IO];
            char Mode = RecvedData.mid(0,1).toInt();
            RecvedData.remove(0,1);
            if (Mode == 100){
                auto RadioBtn = this->findChild<QRadioButton*>("radioBtn_HIG_" + QString::number(IO));
                RadioBtn->setChecked(Qt::Checked);
                QTreeWidgetItem *Item = new QTreeWidgetItem(ui->treeWidget);
                Item->setText(0,"IO State:HIG");
            }else if (Mode == -100){
                auto RadioBtn = this->findChild<QRadioButton*>("radioBtn_LOW_" + QString::number(IO));
                RadioBtn->setChecked(Qt::Unchecked);
                QTreeWidgetItem *Item = new QTreeWidgetItem(ui->treeWidget);
                Item->setText(0,"IO State:LOW");
            }
        }
            break;
        case 0x40:
        {
            // 系统版本信息
            unsigned int Datalenth = 0;
            Datalenth = *(unsigned int*)RecvedData.mid(0,4).data();
            RecvedData.remove(0,4);
            QString Str(RecvedData.mid(0,Datalenth));
        }
            break;
        case 0x41:
        {
            // Top命令信息
            unsigned int Datalenth = 0;
            Datalenth = *(unsigned int*)RecvedData.mid(0,4).data();
            RecvedData.remove(0,4);
            QString Str(RecvedData.mid(0,Datalenth));
         }
            break;
        default:
            break;
        }
    }
}

void RaspberryPiGPIOUI::Slot_ButtonToggled(QAbstractButton *button, bool checked)
{
    if (checked == false){
        return;
    }
    QString ObjName = button->objectName();
    QStringList StrList = ObjName.split("_");
    CommandTimer.start(20);
    QByteArray WaitSendData;
    WaitSendData.clear();
    if (StrList[1] == "IN"){
        char IO = StrList[2].toInt();
        IO = Board_WiringPI[IO];
        char Mode = 100;
        qDebug() <<  ObjName << QString::number(IO) << checked;
        WaitSendData.append(0x20);
        WaitSendData.append(IO);
        WaitSendData.append(Mode);
    }
    if (StrList[1] == "OUT"){
        char IO = StrList[2].toInt();
        IO = Board_WiringPI[IO];
        char Mode = -100;
        qDebug() << ObjName << QString::number(IO) << checked;
        WaitSendData.append(0x20);
        WaitSendData.append(IO);
        WaitSendData.append(Mode);
    }
    if (StrList[1] == "HIG"){
        char IO = StrList[2].toInt();
        IO = Board_WiringPI[IO];
        char Val = 100;
        qDebug() <<  ObjName << QString::number(IO) << checked;
        WaitSendData.append(0x30);
        WaitSendData.append(IO);
        WaitSendData.append(Val);
    }
    if (StrList[1] == "LOW"){
        char IO = StrList[2].toInt();
        IO = Board_WiringPI[IO];
        char Val = -100;
        qDebug() <<  ObjName << QString::number(IO) << checked;
        WaitSendData.append(0x30);
        WaitSendData.append(IO);
        WaitSendData.append(Val);
    }
    TCPSocket.write(WaitSendData);
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
    QByteArray Data = TCPSocket.readAll();
    RecvedData.append(Data);
    emit Sig_RecvData();
}

void RaspberryPiGPIOUI::Slot_TimeOut()
{
    SendCommand = false;
}
