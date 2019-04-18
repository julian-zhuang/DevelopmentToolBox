#ifndef LOCALINFOMATION_H
#define LOCALINFOMATION_H

#include <QWidget>

namespace Ui {
class LocalInfoMation;
}

class LocalInfoMation : public QWidget
{
    Q_OBJECT

public:
    explicit LocalInfoMation(QWidget *parent = 0);
    ~LocalInfoMation();

private:
    Ui::LocalInfoMation *ui;
};

#endif // LOCALINFOMATION_H
