#ifndef MINIBROWSERUI_H
#define MINIBROWSERUI_H

#include <QWidget>

namespace Ui {
class MiniBrowserUI;
}

class MiniBrowserUI : public QWidget
{
    Q_OBJECT

public:
    explicit MiniBrowserUI(QWidget *parent = 0);
    ~MiniBrowserUI();

private:
    Ui::MiniBrowserUI *ui;
};

#endif // MINIBROWSERUI_H
