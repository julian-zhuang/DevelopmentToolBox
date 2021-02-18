#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(QString id, QWidget *parent = nullptr);
    ~ChatWindow();

private:
    Ui::ChatWindow *ui;

public:
    QString m_Local_ID;
};

#endif // CHATWINDOW_H
