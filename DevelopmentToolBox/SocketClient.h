#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QWidget>
#include <qtcpsocket.h>
#include <qudpsocket.h>
#include <QMenu>
#include <QAction>
#include <QTreeWidgetItem>
#include <MItemDelegate.h>

namespace Ui {
class SocketClient;
}

class SocketClient : public QWidget
{
    Q_OBJECT

public:
    explicit SocketClient(QWidget *parent = nullptr);
    ~SocketClient();
private slots:
	void Slot_BtnConnectClicked();
	void Slot_Socketconnected();
	void Slot_Socketdisconnected();
	void Slot_Socketerror(QAbstractSocket::SocketError socketError);
	void Slot_SockethostFound();
	void Slot_SocketreadyRead();

	void Slot_triggered(QAction *action);

	void Slot_currentIndexChanged(int index);
	void Slot_customContextMenuRequested(const QPoint &pos);

	void Slot_itemDoubleClicked(QTreeWidgetItem *item, int column);

	void Slot_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
	QString HexSeparation(QByteArray Data);
private:
    Ui::SocketClient *ui;

	QTcpSocket * Tcp_Client_A;
	bool Tcp_Connect_A;

	QTcpSocket * Tcp_Client_B;
	bool Tcp_Connect_B;

	QUdpSocket * Udp_Client_A;
	bool Ucp_Connect_A;
	
	QUdpSocket * Udp_Client_B;
	bool Ucp_Connect_B;

	QMenu *m_TreeWidgetMenu;
	QAction *m_ActionProtocolAddGroup;
	QAction *m_ActionProtocolAddMember;
	QAction *m_ActionDeleteGroup;
	QAction *m_ActionDeleteMember;
	QAction *m_ActionSendToServerA;
	QAction *m_ActionSendToServerB;
	MItemDelegate* m_MItemDelegate;
};

#endif // SOCKETCLIENT_H
