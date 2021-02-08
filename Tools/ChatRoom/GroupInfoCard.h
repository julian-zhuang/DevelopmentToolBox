#ifndef GROUPINFOCARD_H
#define GROUPINFOCARD_H

#include <QWidget>

namespace Ui {
class GroupInfoCard;
}

class GroupInfoCard : public QWidget
{
    Q_OBJECT

public:
    explicit GroupInfoCard(QWidget *parent = 0);
    ~GroupInfoCard();

private:
    Ui::GroupInfoCard *ui;
};

#endif // GROUPINFOCARD_H
