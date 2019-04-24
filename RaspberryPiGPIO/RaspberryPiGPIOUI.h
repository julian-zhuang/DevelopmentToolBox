#ifndef RASPBERRYPIGPIOUI_H
#define RASPBERRYPIGPIOUI_H

#include <QWidget>

namespace Ui {
class RaspberryPiGPIOUI;
}

class RaspberryPiGPIOUI : public QWidget
{
    Q_OBJECT

public:
    explicit RaspberryPiGPIOUI(QWidget *parent = 0);
    ~RaspberryPiGPIOUI();

private:
    Ui::RaspberryPiGPIOUI *ui;
};

#endif // RASPBERRYPIGPIOUI_H
