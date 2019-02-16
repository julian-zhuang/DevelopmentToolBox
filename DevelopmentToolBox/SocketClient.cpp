#include "SocketClient.h"
#include "ui_SocketClient.h"
#include <QHostAddress>
#include <QDateTime>
SocketClient::SocketClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SocketClient)
{
    ui->setupUi(this);

	Tcp_Connect_A = false;
	Tcp_Connect_B = false;
	Ucp_Connect_A = false;
	Ucp_Connect_B = false;

	connect(ui->pushButton_ConnectA, SIGNAL(clicked()), this, SLOT(Slot_BtnConnectClicked()));
	connect(ui->pushButton_ConnectB, SIGNAL(clicked()), this, SLOT(Slot_BtnConnectClicked()));
	Tcp_Client_A = new QTcpSocket;
	Tcp_Client_B = new QTcpSocket;

	Udp_Client_A = new QUdpSocket;
	Udp_Client_B = new QUdpSocket;

	connect(Tcp_Client_A, SIGNAL(connected()), this, SLOT(Slot_Socketconnected()));
	connect(Tcp_Client_A, SIGNAL(disconnected()), this, SLOT(Slot_Socketdisconnected()));
	connect(Tcp_Client_A, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(Slot_Socketerror(QAbstractSocket::SocketError)));
	connect(Tcp_Client_A, SIGNAL(readyRead()), this, SLOT(Slot_SocketreadyRead()));

	connect(Udp_Client_A, SIGNAL(readyRead()), this, SLOT(Slot_SocketreadyRead()));

	connect(Tcp_Client_B, SIGNAL(connected()), this, SLOT(Slot_Socketconnected()));
	connect(Tcp_Client_B, SIGNAL(disconnected()), this, SLOT(Slot_Socketdisconnected()));
	connect(Tcp_Client_B, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(Slot_Socketerror(QAbstractSocket::SocketError)));
	connect(Tcp_Client_B, SIGNAL(readyRead()), this, SLOT(Slot_SocketreadyRead()));

	connect(Udp_Client_A, SIGNAL(readyRead()), this, SLOT(Slot_SocketreadyRead()));

	connect(ui->comboBox_Protocol_ClientA, SIGNAL(currentIndexChanged(int)), this, SLOT(Slot_currentIndexChanged(int)));
	connect(ui->comboBox_Protocol_ClientB, SIGNAL(currentIndexChanged(int)), this, SLOT(Slot_currentIndexChanged(int)));
	connect(ui->treeWidget_Protocol, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(Slot_itemDoubleClicked(QTreeWidgetItem *, int)));
	connect(ui->treeWidget_Protocol, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(Slot_currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)));

	m_MItemDelegate = new MItemDelegate;
	ui->treeWidget_Protocol->setItemDelegate(m_MItemDelegate);
	ui->treeWidget_Protocol->setColumnWidth(0, 200);

	m_TreeWidgetMenu = new QMenu;
	m_ActionProtocolAddGroup = new QAction("Add Protocol");
	m_TreeWidgetMenu->addAction(m_ActionProtocolAddGroup);
	m_ActionProtocolAddMember = new QAction("Add Member");
	m_TreeWidgetMenu->addAction(m_ActionProtocolAddMember);
	m_ActionDeleteMember = new QAction(tr("Delete Member"));
	m_TreeWidgetMenu->addAction(m_ActionDeleteMember);
	m_ActionDeleteGroup = new QAction(tr("Delete Protocol"));
	m_TreeWidgetMenu->addAction(m_ActionDeleteGroup);
	m_ActionSendToServerA = new QAction(tr("Send To A"));
	m_TreeWidgetMenu->addAction(m_ActionSendToServerA);
	m_ActionSendToServerB = new QAction(tr("Send To B"));
	m_TreeWidgetMenu->addAction(m_ActionSendToServerB);
	connect(m_TreeWidgetMenu, SIGNAL(triggered(QAction *)), this, SLOT(Slot_triggered(QAction *)));
	ui->treeWidget_Protocol->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->treeWidget_Protocol, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(Slot_customContextMenuRequested(const QPoint &)));
}

SocketClient::~SocketClient()
{
    delete ui;
}

void SocketClient::Slot_BtnConnectClicked()
{
	if (sender() == ui->pushButton_ConnectA) {
		if (ui->comboBox_Protocol_ClientA->currentIndex() == 0) {
			//TCP
			if (Tcp_Connect_A) {
				Tcp_Connect_A = false;
				//TCP已经连接
				Tcp_Client_A->disconnect();
				Tcp_Client_A->waitForDisconnected(5000);
				Tcp_Client_A->close();
				ui->pushButton_ConnectA->setText(tr("Connect"));
			}
			else {
				Tcp_Connect_A = true;
				//TCP未连接
				Tcp_Client_A->connectToHost(ui->lineEdit_ServerAddress_ClientA->text(), ui->spinBox_Port_ClientA->value(), QTcpSocket::ReadWrite);
				ui->pushButton_ConnectA->setText(tr("DisConnect"));
			}
			//更新按钮状态
			ui->lineEdit_ServerAddress_ClientA->setEnabled(!Tcp_Client_A);
			ui->spinBox_Port_ClientA->setEnabled(!Tcp_Client_A);
			ui->comboBox_Protocol_ClientA->setEnabled(!Tcp_Client_A);
		}
		if (ui->comboBox_Protocol_ClientA->currentIndex() == 1) {
			//UDP
			if (Ucp_Connect_A) {
				Ucp_Connect_A = false;
				//UDP已经启用
				Udp_Client_A->close();
				ui->pushButton_ConnectB->setText(tr("Start"));
			}
			else {
				//UDP连接没有启用
				if (Udp_Client_A->bind(QHostAddress::LocalHost, ui->spinBox_Port_ClientA->value())) {
					Ucp_Connect_A = false;
					ui->pushButton_ConnectB->setText(tr("Start"));
				}
				else {
					Ucp_Connect_A = true;
					ui->pushButton_ConnectB->setText(tr("Stop"));
				}
			}
			//更新按钮状态
			ui->lineEdit_ServerAddress_ClientA->setEnabled(!Ucp_Connect_A);
			ui->spinBox_Port_ClientA->setEnabled(!Tcp_Client_A);
			ui->comboBox_Protocol_ClientA->setEnabled(!Ucp_Connect_A);
		}
	}
	if (sender() == ui->pushButton_ConnectB) {
		if (ui->comboBox_Protocol_ClientB->currentIndex() == 0) {
			//TCP
			if (Tcp_Connect_B) {
				Tcp_Connect_B = !Tcp_Connect_B;
				//TCP已经连接
				Tcp_Client_B->disconnect();
				Tcp_Client_B->waitForDisconnected(5000);
				Tcp_Client_B->close();
				ui->pushButton_ConnectB->setText(tr("Connect"));
			}
			else {
				Tcp_Connect_B = !Tcp_Connect_B;
				//TCP未连接
				Tcp_Client_B->connectToHost(ui->lineEdit_ServerAddress_ClientA->text(), ui->spinBox_Port_ClientB->value(), QTcpSocket::ReadWrite);
				ui->pushButton_ConnectB->setText(tr("DisConnect"));
			}
			//更新按钮状态
			ui->lineEdit_ServerAddress_ClientB->setEnabled(!Tcp_Connect_B);
			ui->spinBox_Port_ClientB->setEnabled(!Tcp_Client_A);
			ui->comboBox_Protocol_ClientB->setEnabled(!Tcp_Connect_B);
		}
		if (ui->comboBox_Protocol_ClientB->currentIndex() == 1) {
			//UDP
			if (Ucp_Connect_B) {
				Ucp_Connect_B = !Ucp_Connect_B;
				Udp_Client_B->close();
				ui->pushButton_ConnectB->setText(tr("Start"));
			}
			else {
				if (Udp_Client_B->bind(QHostAddress::LocalHost, ui->spinBox_Port_ClientA->value())) {
					Ucp_Connect_B = !Ucp_Connect_B;
					ui->pushButton_ConnectB->setText(tr("Stop"));
				}
				else {
					Ucp_Connect_B = !Ucp_Connect_B;
					ui->pushButton_ConnectB->setText(tr("Stop"));
				}
			}
			//更新按钮状态
			ui->lineEdit_ServerAddress_ClientB->setEnabled(!Ucp_Connect_B);
			ui->spinBox_Port_ClientB->setEnabled(!Tcp_Client_A);
			ui->comboBox_Protocol_ClientB->setEnabled(!Ucp_Connect_B);
		}
	}
}

void SocketClient::Slot_Socketconnected()
{
	if (sender() == Tcp_Client_A) {
		Tcp_Connect_A = true;
		ui->pushButton_ConnectA->setText(tr("Disconnect"));
		QTreeWidgetItem* t_Item = new QTreeWidgetItem;
		t_Item->setText(0, "Server A (" + ui->comboBox_Protocol_ClientA->currentText() + ") Connected");
		ui->treeWidget_Log->addTopLevelItem(t_Item);
	}
	if (sender() == Tcp_Client_B) {
		Tcp_Connect_B = true;
		ui->pushButton_ConnectB->setText(tr("Disconnect"));
		QTreeWidgetItem* t_Item = new QTreeWidgetItem;
		t_Item->setText(0, "Server B (" + ui->comboBox_Protocol_ClientB->currentText() + ") Connected");
		ui->treeWidget_Log->addTopLevelItem(t_Item);
	}
}

void SocketClient::Slot_Socketdisconnected()
{
	if (sender() == Tcp_Client_A) {
		Tcp_Connect_A = false;
		ui->pushButton_ConnectA->setText(tr("Connect"));
		QTreeWidgetItem* t_Item = new QTreeWidgetItem;
		t_Item->setText(0, "Server A (" + ui->comboBox_Protocol_ClientB->currentText() + ") Disconnect");
		ui->treeWidget_Log->addTopLevelItem(t_Item);
	}
	if (sender() == Tcp_Client_B) {
		Tcp_Connect_B = false;
		ui->pushButton_ConnectB->setText(tr("Connect"));
		QTreeWidgetItem* t_Item = new QTreeWidgetItem;
		t_Item->setText(0, "Server B (" + ui->comboBox_Protocol_ClientB->currentText() + ") Disconnect");
		ui->treeWidget_Log->addTopLevelItem(t_Item);
	}
}

void SocketClient::Slot_Socketerror(QAbstractSocket::SocketError socketError)
{
	if (sender() == Tcp_Client_A) {
		QTreeWidgetItem* t_Item = new QTreeWidgetItem;
		t_Item->setText(0, "Server A (TCP) Error");
		ui->treeWidget_Log->addTopLevelItem(t_Item);
		return;
	}
	if (sender() == Tcp_Client_B) {
		QTreeWidgetItem* t_Item = new QTreeWidgetItem;
		t_Item->setText(0, "Server A (TCP) Error");
		ui->treeWidget_Log->addTopLevelItem(t_Item);
		return;
	}
	if (sender() == Udp_Client_A) {
		QTreeWidgetItem* t_Item = new QTreeWidgetItem;
		t_Item->setText(0, "Server A (UDP) Error");
		ui->treeWidget_Log->addTopLevelItem(t_Item);
		return;
	}
	if (sender() == Udp_Client_B) {
		QTreeWidgetItem* t_Item = new QTreeWidgetItem;
		t_Item->setText(0, "Server B (UDP) Error");
		ui->treeWidget_Log->addTopLevelItem(t_Item);
		return;
	}
}

void SocketClient::Slot_SockethostFound()
{

}

void SocketClient::Slot_SocketreadyRead()
{
	if (sender() == Tcp_Client_A) {
		QByteArray RecvData = Tcp_Client_A->readAll();
		QTreeWidgetItem* t_Item = new QTreeWidgetItem;
		t_Item->setText(0, "Server A (TCP)" + tr("Recv:") + QString::number(RecvData.length()));
		ui->treeWidget_Log->addTopLevelItem(t_Item);
		QTreeWidgetItem *t_ItemB = new QTreeWidgetItem;
		t_ItemB->setText(0, HexSeparation(RecvData));
		t_ItemB->setData(0, 0, RecvData);
		t_Item->addChild(t_Item);
		return;
	}
	if (sender() == Tcp_Client_B) {
		QByteArray RecvData = Tcp_Client_B->readAll();
		QTreeWidgetItem* t_Item = new QTreeWidgetItem;
		t_Item->setText(0, "Server B (TCP)" + tr("Recv:") + QString::number(RecvData.length()));
		ui->treeWidget_Log->addTopLevelItem(t_Item);
		QTreeWidgetItem *t_ItemB = new QTreeWidgetItem;
		t_ItemB->setText(0, HexSeparation(RecvData));
		t_ItemB->setData(0, 0, RecvData);
		t_Item->addChild(t_Item);
		return;
	}
	if (sender() == Udp_Client_A) {
		QByteArray RecvData = Udp_Client_A->readAll();
		QTreeWidgetItem* t_Item = new QTreeWidgetItem;
		t_Item->setText(0, "Server B (UDP)" + tr("Recv:") + QString::number(RecvData.length()));
		ui->treeWidget_Log->addTopLevelItem(t_Item);
		QTreeWidgetItem *t_ItemB = new QTreeWidgetItem;
		t_ItemB->setText(0, HexSeparation(RecvData));
		t_ItemB->setData(0, 0, RecvData);
		t_Item->addChild(t_Item);
		return;
	}
	if (sender() == Udp_Client_B) {
		QByteArray RecvData = Udp_Client_B->readAll();
		QTreeWidgetItem* t_Item = new QTreeWidgetItem;
		t_Item->setText(0, "Server B (UDP)" + tr("Recv:") + QString::number(RecvData.length()));
		ui->treeWidget_Log->addTopLevelItem(t_Item);
		QTreeWidgetItem *t_ItemB = new QTreeWidgetItem;
		t_ItemB->setText(0, HexSeparation(RecvData));
		t_ItemB->setData(0, 0, RecvData);
		t_Item->addChild(t_Item);
		return;
	}
}

void SocketClient::Slot_triggered(QAction * action)
{
	QTreeWidgetItem *m_Item = ui->treeWidget_Protocol->currentItem();
	if (action == m_ActionProtocolAddGroup) {
		m_Item = new QTreeWidgetItem;
		m_Item->setData(0, 0, 0);
		m_Item->setText(0, "New Protocol");
		m_Item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		ui->treeWidget_Protocol->addTopLevelItem(m_Item);
		ui->treeWidget_Protocol->setCurrentItem(m_Item);
		return;
	}
	if (action == m_ActionProtocolAddMember) {
		if (m_Item->parent() == nullptr) {
			QTreeWidgetItem *t_Item = new QTreeWidgetItem;
			t_Item->setData(0, 0, 1);
			t_Item->setText(0, "New Member");
			t_Item->setText(1, "Str");
			t_Item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
			ui->treeWidget_Protocol->setCurrentItem(t_Item);
			m_Item->addChild(t_Item);
			ui->treeWidget_Protocol->setCurrentItem(t_Item);
		}
		else {
			QTreeWidgetItem *t_Item = new QTreeWidgetItem;
			t_Item->setData(0, 0, 1);
			t_Item->setText(0, "New Member");
			t_Item->setText(1, "Str");
			t_Item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
			ui->treeWidget_Protocol->setCurrentItem(t_Item);
			m_Item->parent()->addChild(t_Item);
			ui->treeWidget_Protocol->setCurrentItem(t_Item);
		}
		return;
	}
	if (action == m_ActionDeleteGroup) {
		if (m_Item == nullptr) {
			return;
		}
		while (m_Item->childCount()) {
			auto t_Item = m_Item->takeChild(0);
			delete t_Item;
		}
		delete m_Item;
	}
	if (action == m_ActionDeleteMember) {
		if (m_Item->parent() == nullptr) {
			return;
		}
		delete m_Item;
	}
	if (action == m_ActionSendToServerA) {
		if (m_Item == nullptr) {
			return;
		}
		if (m_Item->childCount() == 0) {
			return;
		}
		//组包
		return;
	}
	if (action == m_ActionSendToServerB) {
		if (m_Item == nullptr) {
			return;
		}
		if (m_Item->childCount() == 0) {
			return;
		}
		//组包
		return;
	}
}

void SocketClient::Slot_currentIndexChanged(int index)
{
	if (sender() == ui->comboBox_Protocol_ClientA) {
		if (index == 0) {
			ui->pushButton_ConnectA->setText(tr("Connect"));
			//TCP
			return;
		}
		if (index == 1) {
			ui->pushButton_ConnectA->setText(tr("Start"));
			//UDP
			return;
		}
	}
	if (sender() == ui->comboBox_Protocol_ClientB) {
		if (index == 0) {
			ui->pushButton_ConnectB->setText(tr("Connect"));
			//TCP
			return;
		}
		if (index == 1) {
			ui->pushButton_ConnectB->setText(tr("Start"));
			//UDP
			return;
		}
	}
}

void SocketClient::Slot_customContextMenuRequested(const QPoint & pos)
{
	QTreeWidgetItem *m_Item = ui->treeWidget_Protocol->currentItem();
	if (m_Item == nullptr) {
		m_ActionProtocolAddGroup->setEnabled(true);
		m_ActionProtocolAddGroup->setVisible(true);

		m_ActionProtocolAddMember->setEnabled(false);
		m_ActionProtocolAddMember->setVisible(false);

		m_ActionDeleteMember->setEnabled(false);
		m_ActionDeleteMember->setVisible(false);

		m_ActionDeleteGroup->setEnabled(false);
		m_ActionDeleteGroup->setVisible(false);

		m_ActionSendToServerA->setEnabled(false);
		m_ActionSendToServerA->setVisible(false);

		m_ActionSendToServerB->setEnabled(false);
		m_ActionSendToServerB->setVisible(false);
		m_TreeWidgetMenu->exec(QCursor::pos());
		return;
	}
	if (m_Item->parent() == nullptr) {
		m_ActionProtocolAddGroup->setEnabled(true);
		m_ActionProtocolAddGroup->setVisible(true);

		m_ActionProtocolAddMember->setEnabled(true);
		m_ActionProtocolAddMember->setVisible(true);

		m_ActionDeleteMember->setEnabled(false);
		m_ActionDeleteMember->setVisible(false);

		m_ActionDeleteGroup->setEnabled(true);
		m_ActionDeleteGroup->setVisible(true);

		m_ActionSendToServerA->setEnabled(true);
		m_ActionSendToServerA->setVisible(true);

		m_ActionSendToServerB->setEnabled(true);
		m_ActionSendToServerB->setVisible(true);
		m_TreeWidgetMenu->exec(QCursor::pos());
		return;
	}
	if (m_Item->parent() != nullptr) {
		m_ActionProtocolAddGroup->setEnabled(true);
		m_ActionProtocolAddGroup->setVisible(true);

		m_ActionProtocolAddMember->setEnabled(true);
		m_ActionProtocolAddMember->setVisible(true);

		m_ActionDeleteMember->setEnabled(true);
		m_ActionDeleteMember->setVisible(true);

		m_ActionDeleteGroup->setEnabled(false);
		m_ActionDeleteGroup->setVisible(false);

		m_ActionSendToServerA->setEnabled(false);
		m_ActionSendToServerA->setVisible(false);

		m_ActionSendToServerB->setEnabled(false);
		m_ActionSendToServerB->setVisible(false);
		m_TreeWidgetMenu->exec(QCursor::pos());
		return;
	}
}

void SocketClient::Slot_itemDoubleClicked(QTreeWidgetItem * item, int column)
{
	/*if (item->parent() == nullptr && column == 0) {
		ui->treeWidget_Protocol->openPersistentEditor(item, 0);
	}
	if (item->parent() != nullptr) {
		ui->treeWidget_Protocol->openPersistentEditor(item, column);
	}*/
}

void SocketClient::Slot_currentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous)
{
	//ui->treeWidget_Protocol->closePersistentEditor(previous, 0);
	//ui->treeWidget_Protocol->closePersistentEditor(previous, 1);
	//ui->treeWidget_Protocol->closePersistentEditor(previous, 2);
}

QString SocketClient::HexSeparation(QByteArray Data)
{
	QString SrcStr = Data.toHex();
	QString RetStr = "";
	int j = 0;
	for (int i = 0; i < SrcStr.length() / 2; i++) {
		j *= i * 2;
		RetStr += SrcStr.mid(j, 2) + " ";
	}
	return RetStr;
}
