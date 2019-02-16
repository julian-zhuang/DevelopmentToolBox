#ifndef CALCULATION_H
#define CALCULATION_H

#include <QWidget>

namespace Ui {
class Calculation;
}

class Calculation : public QWidget
{
    Q_OBJECT
public slots:
    void Slot_HashTextChange();
    void Slot_TranscodingTextChange();
public:
    explicit Calculation(QWidget *parent = nullptr);
    ~Calculation();

private:
    Ui::Calculation *ui;
};

#endif // CALCULATION_H
