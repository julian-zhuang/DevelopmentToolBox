#ifndef STRMESSAGE_H
#define STRMESSAGE_H

#include <QWidget>

namespace Ui {
class StrMessage;
}

class StrMessage : public QWidget
{
    Q_OBJECT

public:
    explicit StrMessage(QWidget *parent = 0);
    ~StrMessage();

private:
    Ui::StrMessage *ui;
};

#endif // STRMESSAGE_H
