#ifndef SOCKETTRANSFER_H
#define SOCKETTRANSFER_H

#include <QWidget>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qudpsocket.h>

namespace Ui {
class SocketTransfer;
}

class SocketTransfer : public QWidget
{
    Q_OBJECT

public:
    explicit SocketTransfer(QWidget *parent = nullptr);
    ~SocketTransfer();

private slots:
	void Slot_ReadyRead();
	void Slot_StartBtnClick();
	void Slot_TcpClientConnect();
private:
    Ui::SocketTransfer *ui;

	QTcpServer *Server_Src;
	QTcpSocket *Client_Des;

	QUdpSocket *UdpSocket_Src;
	QUdpSocket *UdpSocket_Des;
};

#endif // SOCKETTRANSFER_H
