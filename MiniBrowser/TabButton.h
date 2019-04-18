#ifndef TABBUTTON_H
#define TABBUTTON_H

#include <QWidget>

namespace Ui {
class TabButton;
}

class TabButton : public QWidget
{
    Q_OBJECT

public:
    explicit TabButton(QWidget *parent = 0);
    ~TabButton();

private:
    Ui::TabButton *ui;
};

#endif // TABBUTTON_H
