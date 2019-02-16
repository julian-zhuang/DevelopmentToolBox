#ifndef SETSHORTCUTS_H
#define SETSHORTCUTS_H

#include <QWidget>

namespace Ui {
class SetShortcuts;
}

class SetShortcuts : public QWidget
{
    Q_OBJECT

public:
    explicit SetShortcuts(QWidget *parent = nullptr);
    ~SetShortcuts();

private:
    Ui::SetShortcuts *ui;
};

#endif // SETSHORTCUTS_H
