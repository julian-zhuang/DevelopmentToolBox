#include "SocketTransfer.h"
#include "ui_SocketTransfer.h"

SocketTransfer::SocketTransfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SocketTransfer)
{
    ui->setupUi(this);
	connect(ui->pushButton_SocketTransfer_Strat_Tcp, SIGNAL(clicked()), this, SLOT(Slot_StartBtnClick()));
	connect(ui->pushButton_SocketTransfer_Strat_Udp, SIGNAL(clicked()), this, SLOT(Slot_StartBtnClick()));
}

SocketTransfer::~SocketTransfer()
{
    delete ui;
}

void SocketTransfer::Slot_ReadyRead()
{

}

void SocketTransfer::Slot_StartBtnClick()
{
	if (sender() == ui->pushButton_SocketTransfer_Strat_Tcp) {
		Server_Src = new QTcpServer;
		Server_Src->listen(QHostAddress::Any, ui->comboBox_SocketTransfer_SrcPort->currentText().toUInt());
		connect(Server_Src, SIGNAL(newConnection()), this, SLOT(Slot_TcpClientConnect()));
		Client_Des = new QTcpSocket;
	}
	if (sender() == ui->pushButton_SocketTransfer_Strat_Udp) {
		UdpSocket_Src->bind(ui->comboBox_SocketTransfer_SrcPort_2->currentText().toUInt());
		UdpSocket_Des = new QUdpSocket;
	}
}

void SocketTransfer::Slot_TcpClientConnect()
{
	Server_Src = new QTcpServer;
	QTcpSocket *t_TcpSocket =  Server_Src->nextPendingConnection();
	if (t_TcpSocket->peerAddress().toString() == ui->comboBox_SocketTransfer_SrcAddr_2->currentText()) {

	}
}
