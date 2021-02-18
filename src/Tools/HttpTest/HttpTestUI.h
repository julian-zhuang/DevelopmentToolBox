#ifndef HTTPTESTUI_H
#define HTTPTESTUI_H

#include <QWidget>

namespace Ui {
class HttpTestUI;
}

class HttpTestUI : public QWidget
{
    Q_OBJECT

public:
    explicit HttpTestUI(QWidget *parent = 0);
    ~HttpTestUI();

private:
    Ui::HttpTestUI *ui;
};

#endif // HTTPTESTUI_H
