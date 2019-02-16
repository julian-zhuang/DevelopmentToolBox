#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QUdpSocket>

namespace Ui {
class SocketServer;
}

class SocketServer : public QWidget
{
    Q_OBJECT

public:
    explicit SocketServer(QWidget *parent = nullptr);
    ~SocketServer();
private slots:
	void Slot_BtnConnectClicked();
	void Slot_Socketconnected();
	void Slot_Socketdisconnected();
	void Slot_Socketerror(QAbstractSocket::SocketError socketError);
	void Slot_SockethostFound();
	void Slot_SocketreadyRead();

	void Slot_acceptError(QAbstractSocket::SocketError socketError);
	void Slot_newConnection();

private:
    Ui::SocketServer *ui;
	bool ServerA_Start;
	QTcpServer *TCPServer_A;
	QUdpSocket *UdpSocket_A;
	
	bool ServerB_Start;
	QTcpServer *TCPServer_B;
	QUdpSocket *UdpSocket_B;
};

#endif // SOCKETSERVER_H
