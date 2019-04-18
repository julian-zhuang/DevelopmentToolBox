#ifndef MEMBERINFOCARD_H
#define MEMBERINFOCARD_H

#include <QWidget>

namespace Ui {
class MemberInfoCard;
}

class MemberInfoCard : public QWidget
{
    Q_OBJECT

public:
    explicit MemberInfoCard(QWidget *parent = 0);
    ~MemberInfoCard();

private:
    Ui::MemberInfoCard *ui;
};

#endif // MEMBERINFOCARD_H
