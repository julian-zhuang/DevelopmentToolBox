#include "SocketServer.h"
#include "ui_SocketServer.h"
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include <qdebug.h>
#include <QList>

SocketServer::SocketServer(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SocketServer)
{
	ui->setupUi(this);
	TCPServer_A = new QTcpServer;
	UdpSocket_A = nullptr;

	TCPServer_B = new QTcpServer;
	UdpSocket_B = nullptr;

	ServerA_Start = false;
	ServerB_Start = false;

	connect(ui->pushButton_StartA, SIGNAL(clicked()), this, SLOT(Slot_BtnConnectClicked()));
	connect(ui->pushButton_StartB, SIGNAL(clicked()), this, SLOT(Slot_BtnConnectClicked()));

	foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
	{
		foreach(QNetworkAddressEntry entry, interface.addressEntries())
		{
			ui->comboBox_ServerA->addItem(entry.ip().toString());
			ui->comboBox_ServerB->addItem(entry.ip().toString());
		}
	}
}

SocketServer::~SocketServer()
{
	delete ui;
}

void SocketServer::Slot_BtnConnectClicked()
{
	if (sender() == ui->pushButton_StartA) {
		if (ui->comboBox_ProtocolA->currentIndex() == 0) {
			if (TCPServer_A == nullptr) {
				TCPServer_A = new QTcpServer;
			}
			else {
				TCPServer_A->close();
				delete TCPServer_A;
				TCPServer_A = nullptr;
			}

			if (ServerA_Start) {

			}
			else {
				if (TCPServer_A->listen(QHostAddress(ui->comboBox_ServerA->currentText()), ui->spinBox_PortA->value())) {
					ServerA_Start = true;
					QTreeWidgetItem * Item = new QTreeWidgetItem;
					Item->setText(0, ui->comboBox_ServerA->currentText() + ":" + QString::number(ui->spinBox_PortA->value()) + " " + "Start seccess");
					ui->treeWidget_Log->addTopLevelItem(Item);
				}
				else {
					ServerA_Start = false;
					QTreeWidgetItem * Item = new QTreeWidgetItem;
					Item->setText(0, ui->comboBox_ServerA->currentText() + ":" + QString::number(ui->spinBox_PortA->value()) + " " + "Start Faild");
					ui->treeWidget_Log->addTopLevelItem(Item);
				}
			}
			ui->comboBox_ServerA->setEnabled(!ServerA_Start);
			ui->spinBox_PortA->setHidden(!ServerA_Start);
		}
		return;
	}
	if (ui->comboBox_ProtocolA->currentIndex() == 1) {
		if (UdpSocket_A == nullptr) {
			UdpSocket_A = new QUdpSocket;
		}
		else {
			UdpSocket_A->close();
			delete UdpSocket_A;
			UdpSocket_A = nullptr;
		}
		if (ServerA_Start) {
			ServerA_Start = false;
			ui->spinBox_PortA->setEnabled(true);
			ui->pushButton_StartA->setText(tr("Start"));
		}
		else {
			ServerA_Start = true;
			ui->spinBox_PortA->setEnabled(false);
			UdpSocket_A->bind(ui->spinBox_PortA->value());
			ui->pushButton_StartA->setText(tr("Stop"));
		}
		return;
	}
	return;
	if (sender() == ui->pushButton_StartB) {
		if (ui->comboBox_ProtocolB->currentIndex() == 0) {
			if (TCPServer_B == nullptr) {
				TCPServer_B = new QTcpServer;
			}
			else {
				TCPServer_B->close();
				delete TCPServer_B;
				TCPServer_B = nullptr;
			}
			if (ServerB_Start) {
				ServerB_Start = false;
				ui->pushButton_StartB->setEnabled(true);
			}
			else {
				ServerB_Start = true;
				ui->pushButton_StartB->setEnabled(false);
				TCPServer_B->listen(QHostAddress::Any, ui->spinBox_PortA->value());
				connect(TCPServer_B, SIGNAL(newConnection()), this, SLOT(Slot_TcpClientConnect()));
			}
			return;
		}
		if (ui->comboBox_ProtocolB->currentIndex() == 1) {
			if (UdpSocket_B == nullptr) {
				UdpSocket_B = new QUdpSocket;
			}
			else {
				UdpSocket_B->close();
				delete UdpSocket_B;
				UdpSocket_B = nullptr;
			}
			if (ServerB_Start) {
				ServerB_Start = false;
				ui->pushButton_StartB->setEnabled(true);
				ui->pushButton_StartB->setText(tr("Start"));
			}
			else {
				ServerB_Start = true;
				UdpSocket_B->bind(ui->spinBox_PortB->value());
				ui->pushButton_StartB->setEnabled(false);
				ui->pushButton_StartB->setText(tr("Stop"));
			}
			return;
		}
		return;
	}
}

void SocketServer::Slot_Socketconnected()
{
}

void SocketServer::Slot_Socketdisconnected()
{
}

void SocketServer::Slot_Socketerror(QAbstractSocket::SocketError socketError)
{
}

void SocketServer::Slot_SockethostFound()
{
}

void SocketServer::Slot_SocketreadyRead()
{
}

void SocketServer::Slot_acceptError(QAbstractSocket::SocketError socketError)
{
}

void SocketServer::Slot_newConnection()
{
	if (sender() == TCPServer_A) {
		QTcpSocket * Client = TCPServer_A->nextPendingConnection();
		connect(Client, SIGNAL(readyRead()), this, SLOT(Slot_SocketreadyRead()));
		connect(Client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(Slot_Socketerror(QAbstractSocket::SocketError)));
		QTreeWidgetItem * Item = new QTreeWidgetItem;
		Item->setText(0, Client->peerAddress().toString() + Client->peerPort() + " " + "Connect");
		ui->treeWidget_Log->addTopLevelItem(Item);
		return;
	}
	if (sender() == TCPServer_B) {
		QTcpSocket * Client = TCPServer_B->nextPendingConnection();
		connect(Client, SIGNAL(readyRead()), this, SLOT(Slot_SocketreadyRead()));
		connect(Client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(Slot_Socketerror(QAbstractSocket::SocketError)));
		QTreeWidgetItem * Item = new QTreeWidgetItem;
		Item->setText(0, Client->peerAddress().toString() + Client->peerPort() + " " + "Connect");
		ui->treeWidget_Log->addTopLevelItem(Item);
		return;
	}
	if (sender() == UdpSocket_A) {
		QTreeWidgetItem * Item = new QTreeWidgetItem;
		//Item->setText(0, Client->peerAddress().toString() + Client->peerPort() + " " + "Connect");
		return;
	}
	if (sender() == UdpSocket_B) {

		return;
	}
}
