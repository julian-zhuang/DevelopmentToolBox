#ifndef RASPBERRYPIGPIOUI_H
#define RASPBERRYPIGPIOUI_H

#include <QMap>
#include <QWidget>
#include <QTcpSocket>
#include <QAbstractButton>
namespace Ui {
class RaspberryPiGPIOUI;
}

class RaspberryPiGPIOUI : public QWidget
{
    Q_OBJECT

public:
    explicit RaspberryPiGPIOUI(QWidget *parent = 0);
    ~RaspberryPiGPIOUI();
private slots:
    void Slot_ButtonToggled(QAbstractButton *button, bool checked);
    void Slot_TextChanged(const QString &text);
    void Slto_Clicked();

    void Slot_Connected();
    void Slot_Disconnected();
    void Slot_Error(QAbstractSocket::SocketError socketError);
    void Slot_ReadyRead();
private:
    QMap<QString, QString> ObjName_Text;

private:
    bool IsConnect;
    QTcpSocket TCPSocket;
    Ui::RaspberryPiGPIOUI *ui;
};

#endif // RASPBERRYPIGPIOUI_H
