#ifndef CHATROOMUI_H
#define CHATROOMUI_H

#include <QWidget>

namespace Ui {
class ChatRoomUI;
}

class ChatRoomUI : public QWidget
{
    Q_OBJECT

public:
    explicit ChatRoomUI(QWidget *parent = 0);
    ~ChatRoomUI();
private slots:
    void Slot_ToolBtnClicked();

private:
    Ui::ChatRoomUI *ui;
};

#endif // CHATROOMUI_H
