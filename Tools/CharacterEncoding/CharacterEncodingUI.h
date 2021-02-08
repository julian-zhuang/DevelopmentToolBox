#ifndef CHARACTERENCODINGUI_H
#define CHARACTERENCODINGUI_H

#include <QWidget>

namespace Ui {
class CharacterEncodingUI;
}

class CharacterEncodingUI : public QWidget
{
    Q_OBJECT

public slots:
    void Slot_HashTextChange();
    void Slot_TranscodingTextChange();
public:
    explicit CharacterEncodingUI(QWidget *parent = 0);
    ~CharacterEncodingUI();

private:
    Ui::CharacterEncodingUI *ui;
};

#endif // CHARACTERENCODINGUI_H
