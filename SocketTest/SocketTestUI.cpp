#include "SocketTestUI.h"
#include "ui_SocketTestUI.h"
#include <QDebug>
#include <QFile>
#include <QApplication>
#include "DelegateContral.h"
#include <QDomDocument>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QButtonGroup>
#include <QDesktopServices>
#include <QtEndian>
#include <QDateTime>

#include "SocketTestUI.h"
#include "ui_SocketTestUI.h"

#define DateStr "[" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz") + "] "

void SocketTestUI::Slot_PusBtnClicked()
{
    QPushButton *PusBtn = (QPushButton *)sender();
    qDebug() << PusBtn->objectName();
    if (PusBtn == ui->pushButton_ByteOrderNew) {
        QString ByteOrderName = QInputDialog::getText(this, tr("Please enter a name"), ("Name"), QLineEdit::Normal, ("No name Endian"));
        if (ByteOrderName.length() == 0) {
            QMessageBox::information(this, tr("Info"), tr("You need to enter a name"), QMessageBox::Ok);
            return;
        }
        if (ByteOrders.contains(ByteOrderName) == true) {
            QMessageBox::information(this, tr("Info"), tr("Name already exists"), QMessageBox::Ok);
            return;
        }
        ByteOrders[ByteOrderName].clear();

        QString CurrentItemA = ui->comboBox_Client_ByteOrders->currentText();
        QString CurrentItemB = ui->comboBox_Server_ByteOrders->currentText();

        ui->comboBox_Client_ByteOrders->clear();
        ui->comboBox_Server_ByteOrders->clear();
        ui->comboBox_ByteOrders->clear();

        for (auto i = ByteOrders.begin(); i != ByteOrders.end(); ++i) {
            ui->comboBox_Client_ByteOrders->addItem(i.key());
            ui->comboBox_Server_ByteOrders->addItem(i.key());
            ui->comboBox_ByteOrders->addItem(i.key());
        }

        ui->comboBox_Client_ByteOrders->activated(CurrentItemA);
        ui->comboBox_Server_ByteOrders->activated(CurrentItemB);
        ui->comboBox_ByteOrders->activated(ByteOrderName);
    }
    if (PusBtn == ui->pushButton_ByteOrderDel) {
        ui->treeWidget_ByteOrder->clear();
        ui->treeWidget_Client_ByteOrder->clear();
        ui->treeWidget_Server_ByteOrder->clear();

        QString ByteOrderName = ui->comboBox_ByteOrders->currentText();
        ui->comboBox_ByteOrders->removeItem(ui->comboBox_ByteOrders->findText(ByteOrderName));
        ui->comboBox_Client_ByteOrders->removeItem(ui->comboBox_Client_ByteOrders->findText(ByteOrderName));
        ui->comboBox_Server_ByteOrders->removeItem(ui->comboBox_Server_ByteOrders->findText(ByteOrderName));
        ByteOrders.remove(ByteOrderName);

        ui->comboBox_ByteOrders->activated(ui->comboBox_ByteOrders->currentText());
        ui->comboBox_Client_ByteOrders->activated(ui->comboBox_Client_ByteOrders->currentText());
        ui->comboBox_Server_ByteOrders->activated(ui->comboBox_Server_ByteOrders->currentText());
    }
    //Client
    if (PusBtn == ui->pushButton_Client_Server_Start){
        ui->pushButton_Client_Server_Start->setEnabled(false);
        if (ui->checkBox_ClientTCP->checkState() == Qt::Checked){
            if (TCP_Client_IsConnect){
                TCP_Client_IsConnect = false;
                TCP_Client.disconnectFromHost();
            }else{
                TCP_Client.connectToHost(QHostAddress(ui->lineEdit_Client_Server->text()),ui->spinBox_Client_Server_Port->value());
            }
        }else{
            if (UDP_Client_IsBindPort == true){
                UDP_Client.close();
                UDP_Client_IsBindPort = false;
                ui->pushButton_Client_Server_Start->setText(tr("Start"));
                QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Client_Log);
                LogItem->setText(0, DateStr + tr("[UDP][Client] Stop"));
                ui->lineEdit_Client_Server->setEnabled(true);
                ui->spinBox_Client_Server_Port->setEnabled(true);
                ui->checkBox_ClientTCP->setEnabled(true);
                ui->checkBox_ClientUDP->setEnabled(true);
            }else{
                QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
                QStringList InputIP = ui->lineEdit_Client_Server->text().split(".");
                if (InputIP.count() != 4){
                    QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Client_Log);
                    LogItem->setText(0, DateStr + tr("The IP address is incorrect."));
                }
                QStringList StrList;
                //获取所有网络接口的列表
                foreach(QNetworkInterface interface,list)
                {  //遍历每一个网络接口
                    QList<QNetworkAddressEntry> entryList = interface.addressEntries();
                    //获取IP地址条目列表，每个条目中包含一个IP地址，一个子网掩码和一个广播地址
                    foreach(QNetworkAddressEntry entry,entryList)
                    {
                        StrList.append(entry.ip().toString());
                    }
                }
                foreach(QString var, StrList){
                    QStringList m_List = var.split(".");
                    if (m_List.count() != 4){
                        continue;
                    }
                    if (m_List[0] == InputIP[0] && m_List[1] == InputIP[1] && m_List[2] == InputIP[2]){
                        InputIP = m_List;
                    }
                }

                if (UDP_Client.bind(QHostAddress(InputIP.join(".")),ui->spinBox_Client_Server_Port->value()) == true){
                    UDP_Client_IsBindPort = true;
                    ui->pushButton_Client_Server_Start->setText(tr("Stop"));
                    QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Client_Log);
                    LogItem->setText(0, DateStr + tr("[UDP][Client] Bind Port") + "[" + ui->spinBox_Client_Server_Port->text() + "]");
                    ui->lineEdit_Client_Server->setEnabled(false);
                    ui->spinBox_Client_Server_Port->setEnabled(false);
                    ui->checkBox_ClientTCP->setEnabled(false);
                    ui->checkBox_ClientUDP->setEnabled(false);
                }else{
                    UDP_Client_IsBindPort = false;
                    ui->pushButton_Client_Server_Start->setText(tr("Start"));
                    ui->lineEdit_Client_Server->setEnabled(true);
                    ui->spinBox_Client_Server_Port->setEnabled(true);
                    ui->checkBox_ClientTCP->setEnabled(true);
                    ui->checkBox_ClientUDP->setEnabled(true);
                }
            }
        }
        ui->pushButton_Client_Server_Start->setEnabled(true);
    }

    if (PusBtn == ui->pushButton_Client_SendTo) {
        bool IsBigEndian = ui->checkBox_Client_BigSend->checkState();
        QByteArray WaitSenddata;
        int RetV = GetByteOrder(ui->treeWidget_Client_ByteOrder,ui->comboBox_Client_ByteOrders->currentText(),WaitSenddata,IsBigEndian);
        if (RetV <0 ){
            QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Client_Log);
            LogItem->setText(0, DateStr + ("TCP Serialization Failed![")+ QString::number(RetV) +"]");
        }
        if (ui->checkBox_ClientTCP->checkState() == Qt::Checked) {
            //Send
            int SendDataLenth = TCP_Client.write(WaitSenddata);
            QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Client_Log);
            LogItem->setText(0, DateStr + ("TCP Send To ")+ ui->lineEdit_Client_Server->text() + ":" + ui->spinBox_Client_Server_Port->text() +(" Success:[")+QString::number(SendDataLenth)+("]Byte"));
            QTreeWidgetItem *DataItem = new QTreeWidgetItem(LogItem);
            DataItem->setText(0,QString(WaitSenddata.toHex()).toUpper());
        }
        else {
            //Send
            int SendDataLenth = UDP_Client.writeDatagram(WaitSenddata,QHostAddress(ui->lineEdit_Client_Server->text()),ui->spinBox_Client_Server_Port->value());
            QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Client_Log);
            LogItem->setText(0, DateStr + ("UDP Send To ")+ ui->lineEdit_Client_Server->text() + ":" + ui->spinBox_Client_Server_Port->text() +(" Success:[")+QString::number(SendDataLenth)+("]Byte"));
            QTreeWidgetItem *DataItem = new QTreeWidgetItem(LogItem);
            DataItem->setText(0,QString(WaitSenddata.toHex()).toUpper());
        }
    }
    //Server
    if (PusBtn == ui->pushButton_Server_Start){
        bool IsBigEndian = ui->checkBox_Server_BigSend->checkState();
        ui->pushButton_Server_Start->setEnabled(false);
        ui->comboBox_Server_Server->setEnabled(false);
        ui->spinBox_Server_Server_Port->setEnabled(false);
        if (ui->checkBox_ServerTCP->checkState() == Qt::Checked){
            if (TCP_Server.isListening()){
                foreach(auto var, Server_Clitents){
                    QTcpSocket *  TcpSocket = (QTcpSocket *)var;
                    QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Server_Log);
                    LogItem->setText(0, DateStr + tr("[TCP][Client]Disconnect ") + TcpSocket->peerAddress().toString() + ":" + QString::number(TcpSocket->peerPort()) + "");
                    TcpSocket->disconnectFromHost();
                }
                Server_Clitents.clear();
                TCP_Server.close();
                ui->comboBox_Server_ClientList->clear();
                ui->pushButton_Server_Start->setText(("Start"));
                ui->comboBox_Server_Server->setEnabled(true);
                ui->spinBox_Server_Server_Port->setEnabled(true);
                ui->checkBox_ServerTCP->setEnabled(true);
                ui->checkBox_ServerUDP->setEnabled(true);

                QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Server_Log);
                LogItem->setText(0, DateStr + tr("TCP Server Stop"));

            }else{
                if (TCP_Server.listen(QHostAddress(ui->comboBox_Server_Server->currentText()),ui->spinBox_Server_Server_Port->value())){
                    QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Server_Log);
                    LogItem->setText(0, DateStr + tr("TCP Server Listen[")+ui->spinBox_Server_Server_Port->text()+tr("] Success!"));
                    ui->pushButton_Server_Start->setText(("Stop"));
                    ui->checkBox_ServerTCP->setEnabled(false);
                    ui->checkBox_ServerUDP->setEnabled(false);
                }else{
                    QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Server_Log);
                    LogItem->setText(0, DateStr + tr("TCP Server Listen[")+ui->spinBox_Server_Server_Port->text()+tr("] Failed!"));
                    ui->comboBox_Server_Server->setEnabled(true);
                    ui->spinBox_Server_Server_Port->setEnabled(true);
                    ui->checkBox_ServerTCP->setEnabled(true);
                    ui->checkBox_ServerUDP->setEnabled(true);
                }
            }
        }else{
            if (UDP_Server_IsBindPort){
                UDP_Server.close();
                UDP_Server_IsBindPort = false;
                ui->pushButton_Server_Start->setText(("Start"));
                QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Server_Log);
                LogItem->setText(0, DateStr + ("UDP Server Stop"));
                ui->comboBox_Server_Server->setEnabled(true);
                ui->spinBox_Server_Server_Port->setEnabled(true);
                ui->checkBox_ServerTCP->setEnabled(true);
                ui->checkBox_ServerUDP->setEnabled(true);
            }else{
                if (UDP_Server.bind(QHostAddress::LocalHost, ui->spinBox_Server_Server_Port->value())){
                    UDP_Server_IsBindPort = true;
                    QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Server_Log);
                    LogItem->setText(0, DateStr + ("UDP Server Bind[")+ui->spinBox_Server_Server_Port->text()+tr("] Success!"));
                    ui->pushButton_Server_Start->setText(("Stop"));
                    ui->comboBox_Server_Server->setEnabled(false);
                    ui->spinBox_Server_Server_Port->setEnabled(false);
                    ui->checkBox_ServerTCP->setEnabled(false);
                    ui->checkBox_ServerUDP->setEnabled(false);

                }else{
                    UDP_Server_IsBindPort = false;
                    QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Server_Log);
                    LogItem->setText(0, DateStr + ("UDP Server Bind[")+ui->spinBox_Server_Server_Port->text()+tr("] Failed!"));
                    ui->comboBox_Server_Server->setEnabled(true);
                    ui->spinBox_Server_Server_Port->setEnabled(true);
                    ui->checkBox_ServerTCP->setEnabled(true);
                    ui->checkBox_ServerUDP->setEnabled(true);
                }
            }
        }
        ui->pushButton_Server_Start->setEnabled(true);
    }
    if (PusBtn == ui->pushButton_Server_Send){
        bool IsBigEndian = ui->checkBox_Client_BigSend->checkState();
        QByteArray WaitSenddata;
        int RetV = GetByteOrder(ui->treeWidget_Server_ByteOrder,ui->comboBox_Server_ByteOrders->currentText(),WaitSenddata,IsBigEndian);
        if (RetV < 0){
           QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Server_Log);
           LogItem->setText(0, DateStr + tr("Serialization Failed![")+ QString::number(RetV) + "]");
           return;
        }
        if (ui->checkBox_ServerTCP->checkState() == Qt::Checked){
            if (Server_Clitents.contains(ui->comboBox_Server_ClientList->currentText()) == true){
                QTcpSocket *TCPSocket = (QTcpSocket *)(Server_Clitents[ui->comboBox_Server_ClientList->currentText()]);
                unsigned SendLenth = TCPSocket->write(WaitSenddata);
                QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Server_Log);
                LogItem->setText(0, "[UDP][Server]Send to " + ui->comboBox_Server_ClientList->currentText() + "[" + QString::number(SendLenth) +"]");
                QTreeWidgetItem *DataItem = new QTreeWidgetItem(LogItem);
                DataItem->setText(0,QString(WaitSenddata.toHex()).toUpper());
            }
        }
        else {
            //Send
            unsigned SendLenth = UDP_Client.writeDatagram(WaitSenddata,QHostAddress(ui->comboBox_Server_ClientList->currentText()),ui->spinBox_Client_Server_Port->value());
            QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Server_Log);
            LogItem->setText(0, "[UDP][Server]Send to " + ui->comboBox_Server_ClientList->currentText() + "[" + QString::number(SendLenth) +"]");
            QTreeWidgetItem *DataItem = new QTreeWidgetItem(LogItem);
            DataItem->setText(0,QString(WaitSenddata.toHex()).toUpper());
        }
    }
    //Repeater
    if (PusBtn == ui->pushButton_Repeater_Src_Server_Start)
    {
        if (ui->checkBox_RepeaterTCP_Src->checkState() == Qt::Checked){
            //TCP
            if (Repeater_Src_TCP_Server.isListening()){
                foreach(auto var, Repeater_Clitents){
                    QTcpSocket *  TcpSocket = (QTcpSocket *)var;
                    QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
                    LogItem->setText(0, DateStr + tr("[TCP][Client]Disconnect ") + TcpSocket->peerAddress().toString() + ":" + QString::number(TcpSocket->peerPort()) + "");
                    TcpSocket->disconnectFromHost();
                }
                Repeater_Clitents.clear();
                Repeater_Src_TCP_Server.close();
                ui->comboBox_Repeeater_Clients->clear();
                ui->pushButton_Repeater_Src_Server_Start->setText(("Start"));
                ui->comboBox_Repeater_Src_Server->setEnabled(true);
                ui->spinBox_Repeater_Src_Server_Port->setEnabled(true);
                ui->checkBox_RepeaterTCP_Src->setEnabled(true);
                ui->checkBox_RepeaterUDP_Src->setEnabled(true);
                QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
                LogItem->setText(0, DateStr + tr("TCP Server Stop"));
            }else{
                if (Repeater_Src_TCP_Server.listen(QHostAddress(ui->comboBox_Repeater_Src_Server->currentText()),ui->spinBox_Repeater_Src_Server_Port->value())){
                    QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
                    LogItem->setText(0, DateStr + tr("TCP Server Listen[")+ui->spinBox_Repeater_Src_Server_Port->text()+tr("] Success!"));
                    ui->pushButton_Repeater_Src_Server_Start->setText(("Stop"));
                    ui->comboBox_Repeater_Src_Server->setEnabled(false);
                    ui->spinBox_Repeater_Src_Server_Port->setEnabled(false);
                    ui->checkBox_RepeaterTCP_Src->setEnabled(false);
                    ui->checkBox_RepeaterUDP_Src->setEnabled(false);
                }else{
                    QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
                    LogItem->setText(0, DateStr + tr("TCP Server Listen[")+ui->spinBox_Repeater_Src_Server_Port->text()+tr("] Failed!"));
                    ui->pushButton_Repeater_Src_Server_Start->setText(("Start"));
                    ui->comboBox_Repeater_Src_Server->setEnabled(true);
                    ui->spinBox_Repeater_Src_Server_Port->setEnabled(true);
                    ui->checkBox_RepeaterTCP_Src->setEnabled(true);
                    ui->checkBox_RepeaterUDP_Src->setEnabled(true);
                }
            }
        }else{
            //UDP
            if (Repeater_UDP_Server_IsBindPort){
                Repeater_Src_UDP_Server.close();
                Repeater_UDP_Server_IsBindPort = false;
                QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
                LogItem->setText(0, DateStr + ("UDP Server Stop"));
                ui->pushButton_Repeater_Src_Server_Start->setText(("Start"));
                ui->comboBox_Repeater_Src_Server->setEnabled(true);
                ui->spinBox_Repeater_Src_Server_Port->setEnabled(true);
                ui->checkBox_RepeaterTCP_Src->setEnabled(true);
                ui->checkBox_RepeaterUDP_Src->setEnabled(true);
            }else{
                if (UDP_Server.bind(QHostAddress::LocalHost, ui->spinBox_Server_Server_Port->value())){
                    Repeater_UDP_Server_IsBindPort = true;
                    QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
                    LogItem->setText(0, DateStr + ("UDP Server Bind[")+ui->spinBox_Server_Server_Port->text()+tr("] Success!"));
                    ui->pushButton_Repeater_Src_Server_Start->setText(("Stop"));
                    ui->comboBox_Repeater_Src_Server->setEnabled(false);
                    ui->spinBox_Repeater_Src_Server_Port->setEnabled(false);
                    ui->checkBox_RepeaterTCP_Src->setEnabled(false);
                    ui->checkBox_RepeaterUDP_Src->setEnabled(false);
                }else{
                    Repeater_UDP_Server_IsBindPort = false;
                    QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
                    LogItem->setText(0, DateStr + ("UDP Server Bind[")+ui->spinBox_Server_Server_Port->text()+tr("] Failed!"));
                    ui->pushButton_Repeater_Src_Server_Start->setText(("Start"));
                    ui->comboBox_Repeater_Src_Server->setEnabled(true);
                    ui->spinBox_Repeater_Src_Server_Port->setEnabled(true);
                    ui->checkBox_RepeaterTCP_Src->setEnabled(true);
                    ui->checkBox_RepeaterUDP_Src->setEnabled(true);
                }
            }
        }
    }

    if (PusBtn == ui->pushButton_Repeater_Des_Client_Start)
    {
        ui->pushButton_Repeater_Des_Client_Start->setEnabled(false);
        if (ui->checkBox_RepeaterTCP_Des->checkState() == Qt::Checked){
            if (Repeater_Des_TCP_Client_Isconnect){
                Repeater_Des_TCP_Client_Isconnect = false;
                Repeater_Des_TCP_Client.disconnectFromHost();
            }else{
                Repeater_Des_TCP_Client.connectToHost(QHostAddress(ui->lineEdit_Repeater_Des_Client->text()),ui->spinBox_Repeater_Des_Server_Port->value());
            }
        }else{
            if (Repeater_Des_UDP_Client_IsBindPort == true){
                Repeater_Des_UDP_Client.close();
                Repeater_Des_UDP_Client_IsBindPort = false;
                ui->pushButton_Repeater_Des_Client_Start->setText(tr("Start"));
                QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
                LogItem->setText(0, DateStr + tr("[UDP][Client] Stop"));
                ui->checkBox_RepeaterTCP_Des->setEnabled(true);
                ui->checkBox_RepeaterUDP_Des->setEnabled(true);
                ui->lineEdit_Repeater_Des_Client->setEnabled(true);
                ui->spinBox_Repeater_Des_Server_Port->setEnabled(true);
            }else{
                QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
                QStringList InputIP = ui->lineEdit_Repeater_Des_Client->text().split(".");
                if (InputIP.count() != 4){
                    QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
                    LogItem->setText(0, DateStr + tr("The IP address is incorrect."));
                }
                QStringList StrList;
                //获取所有网络接口的列表
                foreach(QNetworkInterface interface,list)
                {  //遍历每一个网络接口
                    QList<QNetworkAddressEntry> entryList = interface.addressEntries();
                    //获取IP地址条目列表，每个条目中包含一个IP地址，一个子网掩码和一个广播地址
                    foreach(QNetworkAddressEntry entry,entryList)
                    {
                        StrList.append(entry.ip().toString());
                    }
                }
                foreach(QString var, StrList){
                    QStringList m_List = var.split(".");
                    if (m_List.count() != 4){
                        continue;
                    }
                    if (m_List[0] == InputIP[0] && m_List[1] == InputIP[1] && m_List[2] == InputIP[2]){
                        InputIP = m_List;
                    }
                }

                if (Repeater_Des_UDP_Client.bind(QHostAddress(InputIP.join(".")),ui->spinBox_Repeater_Des_Server_Port->value()) == true){
                    Repeater_Des_UDP_Client_IsBindPort = true;
                    ui->pushButton_Repeater_Des_Client_Start->setText(tr("Stop"));
                    QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
                    LogItem->setText(0, DateStr + tr("[UDP][Client] Bind Port") + "[" + ui->spinBox_Repeater_Des_Server_Port->text() + "]");
                    ui->checkBox_RepeaterTCP_Des->setEnabled(false);
                    ui->checkBox_RepeaterUDP_Des->setEnabled(false);
                    ui->lineEdit_Repeater_Des_Client->setEnabled(false);
                    ui->spinBox_Repeater_Des_Server_Port->setEnabled(false);
                }else{
                    Repeater_Des_UDP_Client_IsBindPort = false;
                    ui->pushButton_Repeater_Des_Client_Start->setText(tr("Start"));
                    ui->checkBox_RepeaterTCP_Des->setEnabled(true);
                    ui->checkBox_RepeaterUDP_Des->setEnabled(true);
                    ui->lineEdit_Repeater_Des_Client->setEnabled(true);
                    ui->spinBox_Repeater_Des_Server_Port->setEnabled(true);
                }
            }
        }
        ui->pushButton_Repeater_Des_Client_Start->setEnabled(true);
    }
}

void SocketTestUI::Slot_ClickBoxClicked(int state)
{
    QCheckBox *CheckBox = (QCheckBox *)sender();
    qDebug() << CheckBox->objectName() << "\t" << state;
    //Client
    if (CheckBox == ui->checkBox_ClientTCP) {
        if (state == Qt::Checked) {
            ui->checkBox_ClientUDP->setChecked(Qt::Unchecked);
            ui->pushButton_Client_Server_Start->setText(tr("Connect"));
        }
        else {
            ui->checkBox_ClientUDP->setChecked(Qt::Checked);
            ui->pushButton_Client_Server_Start->setText(tr("Start"));
        }
    }
    if (CheckBox == ui->checkBox_ClientUDP) {
        if (state == Qt::Checked) {
            ui->checkBox_ClientTCP->setChecked(Qt::Unchecked);
            ui->pushButton_Client_Server_Start->setText(tr("Start"));
        }
        else {
            ui->checkBox_ClientTCP->setChecked(Qt::Checked);
            ui->pushButton_Client_Server_Start->setText(tr("Connect"));
        }
    }
    if (CheckBox == ui->checkBox_Client_BigSend) {
        if (state == Qt::Checked) {
            ui->checkBox_Client_LittleSend->setChecked(Qt::Unchecked);
        }
        else {
            ui->checkBox_Client_LittleSend->setChecked(Qt::Checked);
        }
    }
    if (CheckBox == ui->checkBox_Client_LittleSend) {
        if (state == Qt::Checked) {
            ui->checkBox_Client_BigSend->setChecked(Qt::Unchecked);
        }
        else {
            ui->checkBox_Client_BigSend->setChecked(Qt::Checked);
        }
    }
    //Server
    if (CheckBox == ui->checkBox_ServerTCP) {
        if (state == Qt::Checked) {
            ui->checkBox_ServerUDP->setChecked(Qt::Unchecked);
            //ui->lineEdit_Server_Client->setEnabled(false);
            //ui->spinBox_Server_Client_Port->setEnabled(false);
        }
        else {
            ui->checkBox_ServerUDP->setChecked(Qt::Checked);
            //ui->lineEdit_Server_Client->setEnabled(true);
            //ui->spinBox_Server_Client_Port->setEnabled(true);
        }
    }
    if (CheckBox == ui->checkBox_ServerUDP) {
        if (state == Qt::Checked) {
            ui->checkBox_ServerTCP->setChecked(Qt::Unchecked);
            //ui->lineEdit_Server_Client->setEnabled(true);
            //ui->spinBox_Server_Client_Port->setEnabled(true);
        }
        else {
            ui->checkBox_ServerTCP->setChecked(Qt::Checked);
            //ui->lineEdit_Server_Client->setEnabled(false);
            //ui->spinBox_Server_Client_Port->setEnabled(false);
        }
    }
    if (CheckBox == ui->checkBox_Server_BigSend) {
        if (state == Qt::Checked) {
            ui->checkBox_Server_LittleSend->setChecked(Qt::Unchecked);
        }
        else {
            ui->checkBox_Server_LittleSend->setChecked(Qt::Checked);
        }
    }
    if (CheckBox == ui->checkBox_Server_LittleSend) {
        if (state == Qt::Checked) {
            ui->checkBox_Server_BigSend->setChecked(Qt::Unchecked);
        }
        else {
            ui->checkBox_Server_BigSend->setChecked(Qt::Checked);
        }
    }

    //Repeater
    if (CheckBox == ui->checkBox_RepeaterTCP_Src) {
        if (state == Qt::Checked) {
            ui->checkBox_RepeaterUDP_Src->setChecked(Qt::Unchecked);
        }
        else {
            ui->checkBox_RepeaterUDP_Src->setChecked(Qt::Checked);
        }
    }
    if (CheckBox == ui->checkBox_RepeaterUDP_Src) {
        if (state == Qt::Checked) {
            ui->checkBox_RepeaterTCP_Src->setChecked(Qt::Unchecked);
        }
        else {
            ui->checkBox_RepeaterTCP_Src->setChecked(Qt::Checked);
        }
    }
    if (CheckBox == ui->checkBox_RepeaterTCP_Des) {
        if (state == Qt::Checked) {
            ui->checkBox_RepeaterUDP_Des->setChecked(Qt::Unchecked);
            ui->pushButton_Repeater_Des_Client_Start->setText("Connect");
        }
        else {
            ui->checkBox_RepeaterUDP_Des->setChecked(Qt::Checked);
            ui->pushButton_Repeater_Des_Client_Start->setText("Start");
        }
    }
    if (CheckBox == ui->checkBox_RepeaterUDP_Des) {
        if (state == Qt::Checked) {
            ui->checkBox_RepeaterTCP_Des->setChecked(Qt::Unchecked);
            ui->pushButton_Repeater_Des_Client_Start->setText("Start");
        }
        else {
            ui->checkBox_RepeaterTCP_Des->setChecked(Qt::Checked);
            ui->pushButton_Repeater_Des_Client_Start->setText("Connect");
        }
    }
}

void SocketTestUI::Slot_CustomContextMenuRequested(const QPoint &pos)
{
    m_FocuseTreeWidget = (QTreeWidget *)sender();

    if (m_FocuseTreeWidget == ui->treeWidget_ByteOrder) {
        m_ByteOrder->exec(QCursor::pos());
    }
    else if (m_FocuseTreeWidget == ui->treeWidget_Client_Log ||
        m_FocuseTreeWidget == ui->treeWidget_Server_Log ||
        m_FocuseTreeWidget == ui->treeWidget_Repeater_Log) {

        QTreeWidgetItem * t_CurrentItem = m_FocuseTreeWidget->currentItem();
        m_Clear->setEnabled(true);
        m_Clear->setEnabled(true);
        if (t_CurrentItem == nullptr) {
            m_Analysis->setEnabled(false);
            m_Analysis->setVisible(false);
        }
        else {
            m_Analysis->setEnabled(true);
            m_Analysis->setVisible(true);
        }
        m_Log->exec(QCursor::pos());
    }
}

void SocketTestUI::Slot_triggered(QAction *action)
{
    QMenu *Menu = (QMenu *)sender();
    QString ActionText = action->text();
    if (m_FocuseTreeWidget == nullptr) {
        return;
    }
    if (Menu == m_ByteOrder) {
        if (ActionText == "XML") {
            auto ByteOrderFilePath = QFileDialog::getExistingDirectory(this, "Please select a directory.");
            QString ByteOrderName = ui->comboBox_ByteOrders->currentText();

            if (ByteOrders.contains(ByteOrderName) == false) {
                QMessageBox::information(this, tr("Info"), "Export Failed", QMessageBox::Ok);
            }
            QDomDocument doc;
            QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
            doc.appendChild(instruction);

            QDomElement RootNode = doc.createElement("Protocol");
            doc.appendChild(RootNode);

            QDomElement ByteOrderNode = doc.createElement("ByteOrder");
            ByteOrderNode.setAttribute("Name", ByteOrderName);
            RootNode.appendChild(ByteOrderNode);

            unsigned int ByteOrderLength = 0;
            foreach(FieldInformation var, ByteOrders[ByteOrderName]) {
                QDomElement Item = doc.createElement("Item");
                ByteOrderNode.appendChild(Item);
                Item.setAttribute("Name", var.Name);
                Item.setAttribute("Type", var.Type);
                Item.setAttribute("Length", var.Length);
                Item.setAttribute("Value", var.Value);
                Item.setAttribute("Note", var.Note);
                ByteOrderLength += var.Length;
            }

            ByteOrderNode.setAttribute("Length", ByteOrderLength);

            QFile file(ByteOrderFilePath + "/" + ByteOrderName + ".xml");
            if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
                QTextStream out(&file);
                out.setCodec("utf-8");
                doc.save(out, 4, QDomNode::EncodingFromTextStream);
                file.close();
                QDesktopServices::openUrl(QUrl(ByteOrderFilePath));
            }
            else {
                QMessageBox::information(this, tr("Info"), "Failed to write to file!", QMessageBox::Ok);
            }
        }
        if (ActionText == "C Struct") {
            QString Str = "struct " + ui->comboBox_ByteOrders->currentText() + "{\n    ";
            QTreeWidgetItemIterator it(ui->treeWidget_ByteOrder);
            while (*it) {
                QString TypeStr = (*it)->text(1);
                if (TypeStr == "Str") {
                    Str += "char[" + (*it)->text(2) + "] " + (*it)->text(0) + ";\t//" + (*it)->text(4) + "\n    ";
                }
                else if (TypeStr == "Bool") {
                    Str += "bool " + (*it)->text(0) + ";\t//" + (*it)->text(4) + "\n    ";
                }
                else if (TypeStr == "Int8") {
                    Str += "char " + (*it)->text(0) + ";\t//" + (*it)->text(4) + "\n    ";
                }
                else if (TypeStr == "Int16") {
                    Str += "short " + (*it)->text(0) + ";\t//" + (*it)->text(4) + "\n    ";
                }
                else if (TypeStr == "Int32") {
                    Str += "int " + (*it)->text(0) + ";\t//" + (*it)->text(4) + "\n    ";
                }
                else if (TypeStr == "Int64") {
                    Str += "long long ing " + (*it)->text(0) + ";\t//" + (*it)->text(4) + "\n    ";
                }
                else if (TypeStr == "UInt8") {
                    Str += "unsigned char " + (*it)->text(0) + ";\t//" + (*it)->text(4) + "\n    ";
                }
                else if (TypeStr == "UInt16") {
                    Str += "unsigned short " + (*it)->text(0) + ";\t//" + (*it)->text(4) + "\n";
                }
                else if (TypeStr == "UInt32") {
                    Str += "unsigned int " + (*it)->text(0) + ";\t//" + (*it)->text(4) + "\n    ";
                }
                else if (TypeStr == "UInt64") {
                    Str += "unsigned long long int " + (*it)->text(0) + ";\t//" + (*it)->text(4) + "\n    ";
                }
                else if (TypeStr == "Float") {
                    Str += "float " + (*it)->text(0) + ";\t//" + (*it)->text(4) + "\n    ";
                }
                else if (TypeStr == "Double") {
                    Str += "double " + (*it)->text(0) + ";\t//" + (*it)->text(4) + "\n";
                }
                ++it;
            }
            Str += "}\n";
            TextEdit->clear();
            TextEdit->setWindowTitle(tr("C Struct"));
            TextEdit->setText(Str);
            TextEdit->show();
        }
        if (ActionText == tr("Add Failed")) {
            QTreeWidgetItem *Item = new QTreeWidgetItem(ui->treeWidget_ByteOrder);
            Item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
            Item->setText(0, tr("Failed"));
            Item->setText(1, "Str");
            Item->setText(2, "1");
            Item->setText(3, "");
            Item->setText(4, "");
        }
        if (ActionText == tr("Del Failed")) {
            QTreeWidgetItem *Item = ui->treeWidget_ByteOrder->currentItem();
            if (Item != nullptr) {
                delete Item;
            }
        }
    }

    if (Menu == m_Log) {
       QTreeWidgetItem * t_TreeItem = m_FocuseTreeWidget->currentItem();
       if (ActionText == tr("Clear")){
           m_FocuseTreeWidget->clear();
       }
       if (ActionText == tr("Analysis")){
           if (t_TreeItem->parent() != nullptr){
               return;
           }
       }
   }
}

void SocketTestUI::Slot_activated(const QString &text)
{
    QComboBox *ComboBox = (QComboBox *)sender();
    if (ByteOrders.contains(text) == false) {
        return;
    }
    ComboBox->setCurrentText(text);
    QTreeWidgetItem *Item = nullptr;
    QList<QTreeWidgetItem*> Items;
    Items.clear();

    if (ComboBox == ui->comboBox_Client_ByteOrders) {
        ui->treeWidget_Client_ByteOrder->clear();

        foreach(auto var, ByteOrders[text]) {
            Item = new QTreeWidgetItem;
            Item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
            Item->setText(0, var.Name);
            Item->setText(1, var.Type);
            Item->setText(2, QString::number(var.Length));
            Item->setText(3, var.Value);
            Item->setText(4, var.Note);
            Items.push_back(Item);
        }
        ui->treeWidget_Client_ByteOrder->addTopLevelItems(Items);
    }
    if (ComboBox == ui->comboBox_Server_ByteOrders) {
        ui->treeWidget_Server_ByteOrder->clear();

        foreach(auto var, ByteOrders[text]) {
            Item = new QTreeWidgetItem;
            Item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
            Item->setText(0, var.Name);
            Item->setText(1, var.Type);
            Item->setText(2, QString::number(var.Length));
            Item->setText(3, var.Value);
            Item->setText(4, var.Note);
            Items.push_back(Item);
        }
        ui->treeWidget_Server_ByteOrder->addTopLevelItems(Items);
    }

    if (ComboBox == ui->comboBox_ByteOrders) {
        ui->treeWidget_ByteOrder->clear();
        foreach(auto var, ByteOrders[text]) {
            Item = new QTreeWidgetItem;
            Item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
            Item->setText(0, var.Name);
            Item->setText(1, var.Type);
            Item->setText(2, QString::number(var.Length));
            Item->setText(3, var.Value);
            Item->setText(4, var.Note);
            Items.push_back(Item);
        }
        ui->treeWidget_ByteOrder->addTopLevelItems(Items);
    }
}

void SocketTestUI::Slot_activated(int index)
{

}

void SocketTestUI::Slot_CurrentChanged(int index)
{
    qDebug() << index;

    QTreeWidgetItem *Item = nullptr;
    QList<QTreeWidgetItem*> Items;
    Items.clear();

    QString ByteOrderName = "";
    if (index == 0) {
        ui->treeWidget_Client_ByteOrder->clear();
        ByteOrderName = ui->comboBox_Client_ByteOrders->currentText();
        if (ByteOrders.contains(ByteOrderName) == false) {
            return;
        }
        foreach(auto var, ByteOrders[ByteOrderName]) {
            Item = new QTreeWidgetItem;
            Item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
            Item->setText(0, var.Name);
            Item->setText(1, var.Type);
            Item->setText(2, QString::number(var.Length));
            Item->setText(3, var.Value);
            Item->setText(4, var.Note);
            Items.push_back(Item);
        }
        ui->treeWidget_Client_ByteOrder->addTopLevelItems(Items);
    }
    if (index == 1) {
        ui->treeWidget_Server_ByteOrder->clear();
        ByteOrderName = ui->comboBox_Server_ByteOrders->currentText();
        if (ByteOrders.contains(ByteOrderName) == false) {
            return;
        }
        foreach(auto var, ByteOrders[ByteOrderName]) {
            Item = new QTreeWidgetItem;
            Item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
            Item->setText(0, var.Name);
            Item->setText(1, var.Type);
            Item->setText(2, QString::number(var.Length));
            Item->setText(3, var.Value);
            Item->setText(4, var.Note);
            Items.push_back(Item);
        }
        ui->treeWidget_Server_ByteOrder->addTopLevelItems(Items);
    }
    if (index == 2) {

    }
    if (index == 3) {
        ui->treeWidget_ByteOrder->clear();
        ByteOrderName = ui->comboBox_ByteOrders->currentText();
        if (ByteOrders.contains(ByteOrderName) == false) {
            return;
        }
        foreach(auto var, ByteOrders[ByteOrderName]) {
            Item = new QTreeWidgetItem;
            Item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
            Item->setText(0, var.Name);
            Item->setText(1, var.Type);
            Item->setText(2, QString::number(var.Length));
            Item->setText(3, var.Value);
            Item->setText(4, var.Note);
            Items.push_back(Item);
        }
        ui->treeWidget_ByteOrder->addTopLevelItems(Items);
    }
}

void SocketTestUI::Slot_ItemChanged(QTreeWidgetItem *item, int column)
{
    QString ByteOrderName = ui->comboBox_ByteOrders->currentText();
    if (ByteOrders.contains(ByteOrderName) == false) {
        return;
    }
    QTreeWidgetItemIterator it(ui->treeWidget_ByteOrder);
    ByteOrders[ByteOrderName].clear();
    while (*it) {
        FieldInformation FieldInfo;
        FieldInfo.Name = (*it)->text(0);
        FieldInfo.Type = (*it)->text(1);
        FieldInfo.Length = (*it)->text(2).toUInt();
        FieldInfo.Value = (*it)->text(3);
        FieldInfo.Note = (*it)->text(4);
        ByteOrders[ByteOrderName].push_back(FieldInfo);
        (*it)->text(0);
        ++it;
    }
}

void SocketTestUI::Slot_Connected()
{
    QAbstractSocket *AbstractSocket = (QAbstractSocket *)sender();
    SocketUserData *UserData = (SocketUserData *)AbstractSocket->userData(0);
    if (UserData != nullptr){
        QTcpSocket * TcpSocket = nullptr;
        if (UserData->Type == 1){
            TcpSocket = (QTcpSocket * )AbstractSocket;
            if (UserData->From == 1){
                TCP_Client_IsConnect = true;
                QTreeWidgetItem* LogItem = new QTreeWidgetItem(ui->treeWidget_Client_Log);
                LogItem->setText(0, DateStr + tr("Connected to ") + ui->lineEdit_Client_Server->text() +":"+ui->spinBox_Client_Server_Port->text() + tr(" successfully"));
                ui->pushButton_Client_Server_Start->setText("DisConnect");
                ui->lineEdit_Client_Server->setEnabled(false);
                ui->spinBox_Client_Server_Port->setEnabled(false);
            }
            if (UserData->From == 4){
                Repeater_Des_TCP_Client_Isconnect = true;
                QTreeWidgetItem* LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
                LogItem->setText(0, DateStr + tr("Connected to ") + ui->lineEdit_Repeater_Des_Client->text() +":"+ui->spinBox_Repeater_Des_Server_Port->text() + tr(" successfully"));
                ui->pushButton_Repeater_Des_Client_Start->setText("DisConnect");
            }
        }
    }
}

void SocketTestUI::Slot_Disconnected()
{
    QAbstractSocket *AbstractSocket = (QAbstractSocket *)sender();
    SocketUserData *UserData = (SocketUserData *)AbstractSocket->userData(0);
    if (UserData != nullptr){
        QTcpSocket * TcpSocket = nullptr;
        if (UserData->Type == 1){
            TcpSocket = (QTcpSocket * )AbstractSocket;
            if (UserData->From == 1){
                TCP_Client_IsConnect = false;
                QTreeWidgetItem* LogItem = new QTreeWidgetItem(ui->treeWidget_Client_Log);
                LogItem->setText(0, DateStr + tr("Connection disconnected from ") + ui->lineEdit_Client_Server->text() +":"+ui->spinBox_Client_Server_Port->text());
                ui->pushButton_Client_Server_Start->setText("Connect");
                ui->lineEdit_Client_Server->setEnabled(true);
                ui->spinBox_Client_Server_Port->setEnabled(true);
            }
            if (UserData->From == 4){
                Repeater_Des_TCP_Client_Isconnect = false;
                QTreeWidgetItem* LogItem = new QTreeWidgetItem(ui->treeWidget_Client_Log);
                LogItem->setText(0, DateStr + tr("Connection disconnected from ") + ui->lineEdit_Repeater_Des_Client->text() +":"+ui->spinBox_Repeater_Des_Server_Port->text());
                ui->pushButton_Repeater_Des_Client_Start->setText("Connect");
            }
        }
    }
}

void SocketTestUI::Slot_Error(QAbstractSocket::SocketError socketError)
{
    QAbstractSocket *AbstractSocket = (QAbstractSocket *)sender();
    SocketUserData *UserData = (SocketUserData *)AbstractSocket->userData(0);
    if (UserData != nullptr){
        QString LogStr = "";
        if (UserData->Type == 1){
            LogStr += tr("[TCP]");
        }
        if (UserData->Type == 2){
            LogStr += tr("[UDP]");
        }
        if (UserData->Mode == 1){
            LogStr += ("[Client]");
        }
        if (UserData->Mode == 1){
            LogStr += ("[Server]");
        }
        LogStr += tr("An error occurred") + "["+QString::number(socketError)+"]";
        if (UserData->From == 1){
            QTreeWidgetItem* LogItem = new QTreeWidgetItem(ui->treeWidget_Client_Log);
            LogItem->setText(0, DateStr + LogStr);
        }
        if (UserData->From == 2){
            QTreeWidgetItem* LogItem = new QTreeWidgetItem(ui->treeWidget_Server_Log);
            LogItem->setText(0, DateStr + LogStr);
        }
        if (UserData->From == 3){
            QTreeWidgetItem* LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
            LogItem->setText(0, DateStr + LogStr);
        }
        if (UserData->From == 4){
            QTreeWidgetItem* LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
            LogItem->setText(0, DateStr + LogStr);
        }
    }

    // QAbstractSocket::ConnectionRefusedError
    // QAbstractSocket::RemoteHostClosedError
    // QAbstractSocket::HostNotFoundError
    // QAbstractSocket::SocketAccessError
    // QAbstractSocket::SocketResourceError
    // QAbstractSocket::SocketTimeoutError
    // QAbstractSocket::DatagramTooLargeError
    // QAbstractSocket::NetworkError
    // QAbstractSocket::AddressInUseError
    // QAbstractSocket::SocketAddressNotAvailableError
    // QAbstractSocket::UnsupportedSocketOperationError
    // QAbstractSocket::ProxyAuthenticationRequiredError
    // QAbstractSocket::ProxyConnectionClosedError
    // QAbstractSocket::ProxyConnectionTimeoutError
    // QAbstractSocket::ProxyNotFoundError
    // QAbstractSocket::ProxyProtocolError
    // QAbstractSocket::UnknownSocketError
}

void SocketTestUI::Slot_ReadyRead()
{
    QAbstractSocket *AbstractSocket = (QAbstractSocket *)sender();
    SocketUserData *UserData = (SocketUserData *)AbstractSocket->userData(0);
    if (UserData != nullptr){
        QString LogStr = "";
        QByteArray RecvData;
        RecvData.clear();
        if (UserData->Type == 1){
            LogStr += tr("[TCP]");
        }
        if (UserData->Type == 2){
            LogStr += tr("[UDP]");
        }
        if (UserData->Mode == 1){
            LogStr += ("[Client]");
            if (UserData->Type == 1){
                QTcpSocket *TcpSocket = (QTcpSocket *)AbstractSocket;
                RecvData = TcpSocket->readAll();
                LogStr += TcpSocket->peerAddress().toString() + ":" + QString::number(TcpSocket->peerPort());
            }
            if (UserData->Type == 2){
                QUdpSocket *UDPSocket = (QUdpSocket *)AbstractSocket;
                QHostAddress Client;
                unsigned int DataLenth = UDPSocket->pendingDatagramSize();
                RecvData.resize(DataLenth);
                unsigned short ClientPort = 0;
                UDPSocket->readDatagram(RecvData.data(), DataLenth, &Client, &ClientPort);
                QString SokcetName = Client.toString() + ":" + QString::number(ClientPort);
                LogStr += SokcetName;
            }
            LogStr += " " + tr("Received data ") + "[" + QString::number(RecvData.length()) + "] bytes";
        }
        if (UserData->Mode == 2){
            LogStr += ("[Server]");
            if (UserData->Type == 2){
                QUdpSocket *UDPSocket = (QUdpSocket *)AbstractSocket;
                QHostAddress Client;
                unsigned int DataLenth = UDPSocket->pendingDatagramSize();
                RecvData.resize(DataLenth);
                unsigned short ClientPort = 0;
                UDPSocket->readDatagram(RecvData.data(), DataLenth, &Client, &ClientPort);
                QString SokcetName = Client.toString() + ":" + QString::number(ClientPort);
                if (Server_Clitents.contains(SokcetName) == false){
                    ui->comboBox_Server_ClientList->addItem(Client.toString());
                    Server_Clitents[SokcetName] == nullptr;
                }
                LogStr += SokcetName;
            }
            LogStr += " " + tr("Received data ") + "[" + QString::number(RecvData.length()) + "] bytes";
        }
        if (UserData->From == 1){
            QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Client_Log);
            LogItem->setText(0,DateStr + LogStr);
            QTreeWidgetItem *Datatem = new QTreeWidgetItem(LogItem);
            Datatem->setText(0, QString(RecvData.toHex()).toUpper());
        }
        if (UserData->From == 2){
            QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Server_Log);
            LogItem->setText(0,DateStr + LogStr);
            QTreeWidgetItem *Datatem = new QTreeWidgetItem(LogItem);
            Datatem->setText(0, QString(RecvData.toHex()).toUpper());
        }
        if (UserData->From == 3){            
            if (ui->checkBox_RepeaterTCP_Des->checkState() == Qt::Checked){
                if (Repeater_Des_TCP_Client_Isconnect){
                    unsigned int SendLenth = Repeater_Des_TCP_Client.write(RecvData);
                    LogStr += "------>" + tr("Send to ") + ui->lineEdit_Repeater_Des_Client->text()+":"+ui->spinBox_Repeater_Des_Server_Port->text();
                    LogStr += "[" + QString::number(SendLenth) + "] bytes";
                }
            }else{
                unsigned int SendLenth = Repeater_Des_UDP_Client.writeDatagram(RecvData,QHostAddress(ui->lineEdit_Repeater_Des_Client->text()),ui->spinBox_Repeater_Des_Server_Port->value());
                LogStr += "------>" + tr("Send to ") + ui->lineEdit_Repeater_Des_Client->text()+":"+ui->spinBox_Repeater_Des_Server_Port->text();
                LogStr += "[" + QString::number(SendLenth) + "] bytes";
            }

            QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
            LogItem->setText(0,DateStr + LogStr);
            QTreeWidgetItem *Datatem = new QTreeWidgetItem(LogItem);
            Datatem->setText(0, QString(RecvData.toHex()).toUpper());

        }
        if (UserData->From == 4){
            if (Repeater_Clitents.contains(ui->comboBox_Repeeater_Clients->currentText()) == true){
                if (ui->checkBox_RepeaterTCP_Src->checkState() == Qt::Checked){
                    QTcpSocket * TcpSocket = (QTcpSocket * )(Repeater_Clitents[ui->comboBox_Repeeater_Clients->currentText()]);
                    unsigned int SendLenth = TcpSocket->write(RecvData);
                    LogStr += "------>" + tr("Send to ") + TcpSocket->peerAddress().toString() + ":" + QString::number(TcpSocket->peerPort());
                    LogStr += "[" + QString::number(SendLenth) + "] bytes";
                }else{
                    unsigned int SendLenth = Repeater_Src_UDP_Server.writeDatagram(RecvData,QHostAddress(ui->comboBox_Repeeater_Clients->currentText()),ui->spinBox_Repeater_Src_Server_Port->value());
                    LogStr += "------>" + tr("Send to ") + ui->comboBox_Repeeater_Clients->currentText() + ":" + ui->spinBox_Repeater_Src_Server_Port->text();
                    LogStr += "[" + QString::number(SendLenth) + "] bytes";
                }
            }

            QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
            LogItem->setText(0,DateStr + LogStr);
            QTreeWidgetItem *Datatem = new QTreeWidgetItem(LogItem);
            Datatem->setText(0, QString(RecvData.toHex()).toUpper());
        }
    }
}

void SocketTestUI::Slot_NewConnection()
{
    QTcpServer *ServerSocket = (QTcpServer *)sender();
    SocketUserData *UserData = (SocketUserData *)(ServerSocket->userData(0));
    if (UserData != nullptr){
        QString LogStr = "";
        QString QTcpSocketName = "";
        QTcpSocket * TCPSocket = nullptr;
        if (UserData->Type == 1){
            LogStr += tr("[TCP]");
        }
        if (UserData->Type == 2){
            LogStr += tr("[UDP]");
        }
        if (UserData->Mode == 2){
            LogStr += tr("[Server]");
            LogStr += tr("New client connection ");
            TCPSocket = ServerSocket->nextPendingConnection();

            SocketUserData *ServerScoketUserData = (SocketUserData *)ServerSocket->userData(0);

            SocketUserData *UserData = new SocketUserData;
            UserData->Type = 1;
            UserData->Mode = 1;
            UserData->From = ServerScoketUserData->From;
            TCPSocket->setUserData(0, UserData);
            connect(TCPSocket,SIGNAL(connected()),this,SLOT(Slot_Connected()));
            connect(TCPSocket,SIGNAL(disconnected()),this,SLOT(Slot_Disconnected()));
            connect(TCPSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));
            connect(TCPSocket,SIGNAL(readyRead()),this,SLOT(Slot_ReadyRead()));

            QTcpSocketName = TCPSocket->peerAddress().toString() + ":" + QString::number(TCPSocket->peerPort());
            LogStr += QTcpSocketName;
        }
        if (UserData->From == 1){

        }
        if (UserData->From == 2){
            QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Server_Log);
            LogItem->setText(0,DateStr + LogStr);
            if (Server_Clitents.contains(QTcpSocketName) == false){
                Server_Clitents[QTcpSocketName] = TCPSocket;
                ui->comboBox_Server_ClientList->addItem(QTcpSocketName);
            }
        }
        if (UserData->From == 3){
            QTreeWidgetItem *LogItem = new QTreeWidgetItem(ui->treeWidget_Repeater_Log);
            LogItem->setText(0,DateStr + LogStr);
            if (Repeater_Clitents.contains(QTcpSocketName) == false){
                Repeater_Clitents[QTcpSocketName] = TCPSocket;
                ui->comboBox_Repeeater_Clients->addItem(QTcpSocketName);
            }
        }
        if (UserData->From == 4){

        }
    }
}

int SocketTestUI::GetByteOrder(QTreeWidget *TreeWidget, QString ByteOrderName, QByteArray &Des, bool BigEndian)
{
    if (TreeWidget == nullptr){
        return -1;
    }
    if (ByteOrders.contains(ByteOrderName) == false){
        return -2;
    }
    Des.clear();
    QTreeWidgetItemIterator it(TreeWidget);
    while(*it){
        QString DataType = (*it)->text(1);
        if (DataType == "Str"){
            Des.append((*it)->text(3));
        }else if (DataType == "Bool"){
            char Boolvalue = (*it)->text(3).toUInt();
            Des.append(Boolvalue);
        }else if (DataType == "Int8"){
            char Value = (*it)->text(3).toInt();
            Des.append((char *)&Value, 1);
        }else if (DataType == "Int16"){
            short Value = (*it)->text(3).toShort();
            if (char((0x0001))){
                //Little
                if (BigEndian){
                    short BigValue = qToBigEndian<qint16>(Value);
                    Des.append((char *)&BigValue, 2);
                }else{
                    Des.append((char *)&Value, 2);
                }
            }else{
                //Big
                if (BigEndian){
                    Des.append((char *)&Value, 2);
                }else{
                    short BigValue = qToLittleEndian<qint16>(Value);
                    Des.append((char *)&BigValue, 2);
                }
            }
        }else if (DataType == "Int32"){
            int Value = (*it)->text(3).toInt();
            if (char((0x0001))){
                //Little
                if (BigEndian){
                    int LittleValue = qToBigEndian<qint32>(Value);
                    Des.append((char *)&LittleValue, 4);
                }else{
                    Des.append((char *)&Value, 4);
                }
            }else{
                //Big
                if (BigEndian){
                    Des.append((char *)&Value, 4);
                }else{
                    int BigValue = qToLittleEndian<qint32>(Value);
                    Des.append((char *)&BigValue, 4);
                }
            }
        }else if (DataType == "Int64"){
            long long int Value = (*it)->text(3).toLongLong();
            if (char((0x0001))){
                //Little
                if (BigEndian){
                    long long int LittleValue = qToBigEndian<qint64>(Value);
                    Des.append((char *)&LittleValue, 8);
                }else{
                    Des.append((char *)&Value, 8);
                }
            }else{
                //Big
                if (BigEndian){
                    Des.append((char *)&Value, 8);
                }else{
                    long long int BigValue = qToLittleEndian<qint64>(Value);
                    Des.append((char *)&BigValue, 8);
                }
            }
        }else if (DataType == "UInt8"){
            unsigned char Value = (*it)->text(3).toUInt();
            Des.append((char *)&Value, 1);
        }else if (DataType == "UInt16"){
            unsigned short Value = (*it)->text(3).toShort();
            if (char((0x0001))){
                //Little
                if (BigEndian){
                    unsigned short LittleValue = qToBigEndian<quint16>(Value);
                    Des.append((char *)&LittleValue, 2);
                }else{
                    Des.append((char *)&Value, 2);
                }
            }else{
                //Big
                if (BigEndian){
                    Des.append((char *)&Value, 2);
                }else{
                    unsigned short BigValue = qToLittleEndian<quint16>(Value);
                    Des.append((char *)&BigValue, 2);
                }
            }

        }else if (DataType == "UInt32"){
            unsigned int Value = (*it)->text(3).toInt();
            if (char((0x0001))){
                //Little
                if (BigEndian){
                    unsigned int LittleValue = qToBigEndian<quint32>(Value);
                    Des.append((char *)&LittleValue, 4);
                }else{
                    Des.append((char *)&Value, 4);
                }
            }else{
                //Big
                if (BigEndian){
                    Des.append((char *)&Value, 4);
                }else{
                    unsigned int BigValue = qToLittleEndian<quint32>(Value);
                    Des.append((char *)&BigValue, 4);
                }
            }
        }else if (DataType == "UInt64"){
            unsigned long long int Value = (*it)->text(3).toULongLong();
            if (char((0x0001))){
                //Little
                if (BigEndian){
                    unsigned long long int LittleValue = qToBigEndian<quint64>(Value);
                    Des.append((char *)&LittleValue, 8);
                }else{
                    Des.append((char *)&Value, 8);
                }
            }else{
                //Big
                if (BigEndian){
                    Des.append((char *)&Value, 8);
                }else{
                    unsigned long long int BigValue = qToLittleEndian<quint64>(Value);
                    Des.append((char *)&BigValue, 8);
                }
            }
        }else if (DataType == "Float"){
            float Value = (*it)->text(3).toFloat();
            if (char((0x0001))){
                //Little
                if (BigEndian){
                    unsigned long long int LittleValue = qToBigEndian<qint32>(Value);
                    Des.append((char *)&LittleValue, 8);
                }else{
                    Des.append((char *)&Value, 8);
                }
            }else{
                //Big
                if (BigEndian){
                    Des.append((char *)&Value, 8);
                }else{
                    unsigned long long int BigValue = qToLittleEndian<qint32>(Value);
                    Des.append((char *)&BigValue, 8);
                }
            }
        }else if (DataType == "Double"){
            double Value = (*it)->text(3).toDouble();
            if (char((0x0001))){
                //Little
                if (BigEndian){
                    long long int  LittleValue = qToBigEndian<qint64>(Value);
                    Des.append((char *)&LittleValue, 8);
                }else{
                    Des.append((char *)&Value, 8);
                }
            }else{
                //Big
                if (BigEndian){
                    Des.append((char *)&Value, 8);
                }else{
                    long long int  BigValue = qToLittleEndian<qint64>(Value);
                    Des.append((char *)&BigValue, 8);
                }
            }
        }else{
            return -3;
        }
        ++it;
    }
    return 0;
}

int SocketTestUI::ByteOrderAnalyze(QByteArray &Src, QString ByteOrderName, QList<SocketTestUI::FieldInformation> &Des, bool BigEndian)
{
    if (ByteOrders.contains(ByteOrderName) == false) {
        return -1;
    }
    QByteArray Src_Img = Src;
    QList<FieldInformation> ByteOrder = ByteOrders[ByteOrderName];

    unsigned int DataLenth = 0;
    foreach(auto var, ByteOrder) {
        DataLenth += var.Length;
    }
    if (Src_Img.length() < DataLenth) {
        return -2;
    }

    unsigned int BytePos = 0;
    Des.clear();
    foreach(auto var, ByteOrder) {
        QString DataType = var.Type;
        if (DataType == "Str") {
            var.Value = Src.mid(BytePos, var.Length);
            BytePos += var.Length;
        }
        else if (DataType == "Bool") {
            var.Value = QString::number(*(Src.mid(BytePos, var.Length).data()));
            BytePos += var.Length;
        }
        else if (DataType == "Int8") {
            char Value = *(Src.mid(BytePos, var.Length).data());
            var.Value = QString::number(Value);
            BytePos += var.Length;
        }
        else if (DataType == "Int16") {
            short Value = *((short *)Src.mid(BytePos, var.Length).data());
            if (char((0x0001))) {
                //Little
                if (BigEndian == true) {
                    Value = qToBigEndian<qint16>(Value);
                }
            }
            else {
                //Big
                if (BigEndian == false) {
                    Value = qToLittleEndian<qint16>(Value);
                }
            }
            var.Value = QString::number(Value);
            BytePos += var.Length;
        }
        else if (DataType == "Int32") {
            int Value = *((int *)Src.mid(BytePos, var.Length).data());
            if (char((0x0001))) {
                //Little
                if (BigEndian == true) {
                    Value = qToBigEndian<qint32>(Value);
                }
            }
            else {
                //Big
                if (BigEndian == false) {
                    Value = qToLittleEndian<qint32>(Value);
                }
            }
            var.Value = QString::number(Value);
            BytePos += var.Length;
        }
        else if (DataType == "Int64") {
            long long int Value = *((long long int *)Src.mid(BytePos, var.Length).data());
            if (char((0x0001))) {
                //Little
                if (BigEndian == true) {
                    Value = qToBigEndian<qint64>(Value);
                }
            }
            else {
                //Big
                if (BigEndian == false) {
                    Value = qToLittleEndian<qint64>(Value);
                }
            }
            var.Value = QString::number(Value);
            BytePos += var.Length;
        }
        else if (DataType == "UInt8") {
            unsigned char Value = *((unsigned char *)Src.mid(BytePos, var.Length).data());
            var.Value = QString::number(Value);
            BytePos += var.Length;
        }
        else if (DataType == "UInt16") {
            unsigned short Value = *((short *)Src.mid(BytePos, var.Length).data());
            if (char((0x0001))) {
                //Little
                if (BigEndian == true) {
                    Value = qToBigEndian<quint16>(Value);
                }
            }
            else {
                //Big
                if (BigEndian == false) {
                    Value = qToLittleEndian<quint16>(Value);
                }
            }
            var.Value = QString::number(Value);
            BytePos += var.Length;
        }
        else if (DataType == "UInt32") {
            unsigned int Value = *((unsigned int *)Src.mid(BytePos, var.Length).data());
            if (char((0x0001))) {
                //Little
                if (BigEndian == true) {
                    Value = qToBigEndian<quint32>(Value);
                }
            }
            else {
                //Big
                if (BigEndian == false) {
                    Value = qToLittleEndian<quint32>(Value);
                }
            }
            var.Value = QString::number(Value);
            BytePos += var.Length;
        }
        else if (DataType == "UInt64") {
            unsigned long long int Value = *((unsigned long long int *)Src.mid(BytePos, var.Length).data());
            if (char((0x0001))) {
                //Little
                if (BigEndian == true) {
                    Value = qToBigEndian<quint64>(Value);
                }
            }
            else {
                //Big
                if (BigEndian == false) {
                    Value = qToLittleEndian<quint64>(Value);
                }
            }
            var.Value = QString::number(Value);
            BytePos += var.Length;
        }
        else if (DataType == "Float") {
            int Value = *((int *)Src.mid(BytePos, var.Length).data());
            if (char((0x0001))) {
                //Little
                if (BigEndian == true) {
                    Value = qToBigEndian<quint32>(Value);
                }
            }
            else {
                //Big
                if (BigEndian == false) {
                    Value = qToLittleEndian<qint32>(Value);
                }
            }
            var.Value = QString::number(Value);
            BytePos += var.Length;
        }
        else if (DataType == "Double") {
            long long int Value = *((long long int *)Src.mid(BytePos, var.Length).data());
            if (char((0x0001))) {
                //Little
                if (BigEndian == true) {
                    Value = qToBigEndian<quint64>(Value);
                }
            }
            else {
                //Big
                if (BigEndian == false) {
                    Value = qToLittleEndian<qint64>(Value);
                }
            }
            var.Value = QString::number(Value);
            BytePos += var.Length;
        }
        else {
            return -3;
        }
        Des.append(var);
    }
    return 0;
}

SocketTestUI::SocketTestUI(QWidget *parent) : QWidget(parent), ui(new Ui::SocketTestUI)
{
    ui->setupUi(this);
    TextEdit = new QTextEdit(nullptr);
    foreach(QCheckBox* var, this->findChildren<QCheckBox *>()) {
        connect(var, &QCheckBox::stateChanged, this, &SocketTestUI::Slot_ClickBoxClicked);
    }

    foreach(QPushButton* var, this->findChildren<QPushButton *>()) {
        connect(var, &QAbstractButton::clicked, this, &SocketTestUI::Slot_PusBtnClicked);
    }

    foreach(QTreeWidget* var, this->findChildren<QTreeWidget *>()) {
        var->setContextMenuPolicy(Qt::CustomContextMenu);
    }

    foreach(QComboBox* var, this->findChildren<QComboBox *>()) {
        connect(var, SIGNAL(activated(QString)), this, SLOT(Slot_activated(QString)));
    }

    foreach(QTreeView* var, this->findChildren<QTreeView *>()) {
        var->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(var, &QWidget::customContextMenuRequested, this, &SocketTestUI::Slot_CustomContextMenuRequested);
    }

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(Slot_CurrentChanged(int)));
    connect(ui->treeWidget_ByteOrder, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(Slot_ItemChanged(QTreeWidgetItem*, int)));

    m_FocuseTreeWidget = nullptr;

    m_ByteOrder = new QMenu;
    m_NewField = new QAction("Add Failed");
    m_DelField = new QAction("Del Failed");
    m_ByteOrder->addAction(m_NewField);
    m_ByteOrder->addAction(m_DelField);
    m_Export = new QMenu("Export");
    m_ToXML = new QAction("XML");
    m_ToCStruct = new QAction("C Struct");
    m_Export->addAction(m_ToXML);
    m_Export->addAction(m_ToCStruct);
    m_ByteOrder->addMenu(m_Export);
    connect(m_ByteOrder, SIGNAL(triggered(QAction*)), this, SLOT(Slot_triggered(QAction*)));

    ui->treeWidget_ByteOrder->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget_ByteOrder, &QWidget::customContextMenuRequested, this, &SocketTestUI::Slot_CustomContextMenuRequested);

    m_Log = new QMenu;
    m_Clear = new QAction("Clear");
    m_Analysis = new QAction("Analysis");
    m_Log->addAction(m_Clear);
    m_Log->addAction(m_Analysis);
    connect(m_Log, SIGNAL(triggered(QAction*)), this, SLOT(Slot_triggered(QAction*)));

    CustomDelegate * t_CustomDelegate = new CustomDelegate(ui->treeWidget_ByteOrder);
    ui->treeWidget_ByteOrder->setItemDelegate(t_CustomDelegate);
    t_CustomDelegate = new CustomDelegate(ui->treeWidget_Client_ByteOrder);
    t_CustomDelegate->SetReadOnlyMode();
    ui->treeWidget_Client_ByteOrder->setItemDelegate(t_CustomDelegate);
    t_CustomDelegate = new CustomDelegate(ui->treeWidget_Server_ByteOrder);
    t_CustomDelegate->SetReadOnlyMode();
    ui->treeWidget_Server_ByteOrder->setItemDelegate(t_CustomDelegate);

    QFile XmlFile(QApplication::applicationDirPath() + "/SocketTest/Protocol.xml");
    if (!XmlFile.open(QFile::Text | QFile::ReadOnly)) {
        qDebug() << "Open " << QApplication::applicationDirPath() + "/SocketTest/Protocol.xml" << " failed";
    }

    QDomDocument XMLInfo;
    QString LogStr;
    if (!XMLInfo.setContent(&XmlFile, &LogStr)) {
        qDebug() << LogStr;
        XMLInfo.clear();
    }
    XmlFile.close();

    QDomNode ProtocolNode = FindNode(XMLInfo, "Protocol");
    QDomNode ByteOrderNode = ProtocolNode.firstChild();

    while (!ByteOrderNode.isNull()) {
        if (ByteOrderNode.nodeName() != "ByteOrder") {
            continue;
        }
        QString ByteOrderName = ByteOrderNode.attributes().namedItem("Name").nodeValue();
        if (ByteOrderName.length() == 0) {
            ByteOrderNode = ByteOrderNode.nextSibling();
            continue;
        }
        QDomNode Item = ByteOrderNode.firstChild();
        while (!Item.isNull()) {
            QDomNamedNodeMap NodeMap = Item.attributes();
            FieldInformation FieldInfo;
            FieldInfo.Name = NodeMap.namedItem("Name").nodeValue();
            FieldInfo.Type = NodeMap.namedItem("Type").nodeValue();
            FieldInfo.Length = NodeMap.namedItem("Length").nodeValue().toUInt();
            FieldInfo.Value = NodeMap.namedItem("Value").nodeValue();
            FieldInfo.Note = NodeMap.namedItem("Note").nodeValue();
            ByteOrders[ByteOrderName].push_back(FieldInfo);
            Item = Item.nextSibling();
        }
        ByteOrderNode = ByteOrderNode.nextSibling();
    }

    for (auto i = ByteOrders.begin(); i != ByteOrders.end(); ++i) {
        ui->comboBox_Client_ByteOrders->addItem(i.key());
        ui->comboBox_Server_ByteOrders->addItem(i.key());
        ui->comboBox_ByteOrders->addItem(i.key());
    }

    ui->comboBox_Client_ByteOrders->activated(ui->comboBox_Client_ByteOrders->currentText());
    ui->comboBox_Server_ByteOrders->activated(ui->comboBox_Server_ByteOrders->currentText());
    ui->comboBox_ByteOrders->activated(ui->comboBox_ByteOrders->currentText());

    //设置socket附加信息
    SocketUserData * UserData = nullptr;
    UserData = new SocketUserData;
    UserData->Type = 1;
    UserData->Mode = 1;
    UserData->From = 1;
    TCP_Client.setUserData(0, UserData);

    UserData = new SocketUserData;
    UserData->Type = 2;
    UserData->Mode = 1;
    UserData->From = 1;
    UDP_Client.setUserData(0, UserData);

    UserData = new SocketUserData;
    UserData->Type = 1;
    UserData->Mode = 2;
    UserData->From = 2;
    TCP_Server.setUserData(0, UserData);

    UserData = new SocketUserData;
    UserData->Type = 2;
    UserData->Mode = 2;
    UserData->From = 2;
    UDP_Server.setUserData(0, UserData);

    UserData = new SocketUserData;
    UserData->Type = 2;
    UserData->Mode = 2;
    UserData->From = 3;
    Repeater_Src_UDP_Server.setUserData(0, UserData);

    UserData = new SocketUserData;
    UserData->Type = 1;
    UserData->Mode = 2;
    UserData->From = 3;
    Repeater_Src_TCP_Server.setUserData(0, UserData);

    UserData = new SocketUserData;
    UserData->Type = 1;
    UserData->Mode = 1;
    UserData->From = 4;
    Repeater_Des_TCP_Client.setUserData(0, UserData);

    UserData = new SocketUserData;
    UserData->Type = 2;
    UserData->Mode = 1;
    UserData->From = 4;
    Repeater_Des_UDP_Client.setUserData(0, UserData);

    //连接socket的信号
    TCP_Client_IsConnect = false;
    connect(&TCP_Client,SIGNAL(connected()),this,SLOT(Slot_Connected()));
    connect(&TCP_Client,SIGNAL(disconnected()),this,SLOT(Slot_Disconnected()));
    connect(&TCP_Client,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));
    connect(&TCP_Client,SIGNAL(readyRead()),this,SLOT(Slot_ReadyRead()));

    UDP_Client_IsBindPort = false;
    connect(&UDP_Client,SIGNAL(readyRead()),this,SLOT(Slot_ReadyRead()));
    connect(&UDP_Client,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));

    UDP_Server_IsBindPort = false;
    connect(&TCP_Server,SIGNAL(newConnection()),this,SLOT(Slot_NewConnection()));
    connect(&TCP_Server,SIGNAL(acceptError(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));

    connect(&UDP_Server,SIGNAL(readyRead()),this,SLOT(Slot_ReadyRead()));
    connect(&UDP_Server,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));

    connect(&Repeater_Src_TCP_Server,SIGNAL(newConnection()),this,SLOT(Slot_NewConnection()));
    connect(&Repeater_Src_TCP_Server,SIGNAL(acceptError(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));

    Repeater_UDP_Server_IsBindPort = false;
    connect(&Repeater_Src_UDP_Server,SIGNAL(readyRead()),this,SLOT(Slot_ReadyRead()));
    connect(&Repeater_Src_UDP_Server,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));

    Repeater_Des_TCP_Client_Isconnect = false;
    connect(&Repeater_Des_TCP_Client,SIGNAL(connected()),this,SLOT(Slot_Connected()));
    connect(&Repeater_Des_TCP_Client,SIGNAL(disconnected()),this,SLOT(Slot_Disconnected()));
    connect(&Repeater_Des_TCP_Client,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));
    connect(&Repeater_Des_TCP_Client,SIGNAL(readyRead()),this,SLOT(Slot_ReadyRead()));

    Repeater_Des_UDP_Client_IsBindPort = false;
    connect(&Repeater_Des_UDP_Client,SIGNAL(readyRead()),this,SLOT(Slot_ReadyRead()));
    connect(&Repeater_Des_UDP_Client,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Slot_Error(QAbstractSocket::SocketError)));

    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    //获取所有网络接口的列表
    foreach(QNetworkInterface interface,list)
    {  //遍历每一个网络接口
        QList<QNetworkAddressEntry> entryList = interface.addressEntries();
        //获取IP地址条目列表，每个条目中包含一个IP地址，一个子网掩码和一个广播地址
        foreach(QNetworkAddressEntry entry,entryList)
        {
            ui->comboBox_Server_Server->addItem(entry.ip().toString());
            ui->comboBox_Repeater_Src_Server->addItem(entry.ip().toString());
        }
    }
}

SocketTestUI::~SocketTestUI()
{
    QDomDocument doc;
    QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
    doc.appendChild(instruction);

    QDomElement RootNode = doc.createElement("Protocol");//创建根节点
    doc.appendChild(RootNode);//添加根节点

    for (auto i = ByteOrders.begin(); i != ByteOrders.end(); ++i) {
        QDomElement ByteOrderNode = doc.createElement("ByteOrder");//创建元素节点
        ByteOrderNode.setAttribute("Name", i.key());
        RootNode.appendChild(ByteOrderNode);//添加元素节点到根节点
        unsigned int ByteOrderLength = 0;
        foreach(FieldInformation var, i.value()) {
            QDomElement Item = doc.createElement("Item");
            ByteOrderNode.appendChild(Item);
            Item.setAttribute("Name", var.Name);
            Item.setAttribute("Type", var.Type);
            Item.setAttribute("Length", var.Length);
            Item.setAttribute("Value", var.Value);
            Item.setAttribute("Note", var.Note);
            ByteOrderLength += var.Length;
        }
        ByteOrderNode.setAttribute("Length", ByteOrderLength);
    }

    QFile file(QApplication::applicationDirPath() + "/SocketTest/Protocol.xml");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&file);
        out.setCodec("utf-8");
        doc.save(out, 4, QDomNode::EncodingFromTextStream);
        file.close();
    }

    delete ui;
}

QDomNode SocketTestUI::FindNode(QDomNode &Node, QString NodeName)
{
    QDomNode t_Node = Node.firstChild();
    while (!t_Node.isNull()) {
        QString NodeNamea = t_Node.nodeName();
        QString NodeValuea = t_Node.nodeValue();
        if (t_Node.nodeName() == NodeName) {
            return t_Node;
        }
        t_Node = t_Node.nextSibling();
    }
    return QDomNode();
}
