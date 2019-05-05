#ifndef RASPBERRYPIGPIOUI_H
#define RASPBERRYPIGPIOUI_H

#include <QMap>
#include <QWidget>
#include <QTcpSocket>
#include <QAbstractButton>
#include <QTimer>
namespace Ui {
class RaspberryPiGPIOUI;
}

class RaspberryPiGPIOUI : public QWidget
{
    Q_OBJECT

signals:
    void Sig_RecvData();
public:
    explicit RaspberryPiGPIOUI(QWidget *parent = 0);
    ~RaspberryPiGPIOUI();
private slots:
    void Slot_RecvData();
    void Slot_ButtonToggled(QAbstractButton *button, bool checked);
    void Slot_TextChanged(const QString &text);
    void Slto_Clicked();

    void Slot_Connected();
    void Slot_Disconnected();
    void Slot_Error(QAbstractSocket::SocketError socketError);
    void Slot_ReadyRead();
    void Slot_TimeOut();
private:
    QMap<QString, QString> ObjName_Text;

private:
    QByteArray RecvedData;
    bool IsConnect;
    QTcpSocket TCPSocket;
    Ui::RaspberryPiGPIOUI *ui;
    QMap<char,char> Board_WiringPI;
    QMap<char,char> WiringPI_Board;
    bool SendCommand;
    QTimer CommandTimer;
};

#endif // RASPBERRYPIGPIOUI_H
