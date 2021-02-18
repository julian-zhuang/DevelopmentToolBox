#ifndef TERMINALUI_H
#define TERMINALUI_H

#include <QWidget>

namespace Ui {
class TerminalUI;
}

class TerminalUI : public QWidget
{
    Q_OBJECT

public:
    explicit TerminalUI(QWidget *parent = 0);
    ~TerminalUI();

private:
    Ui::TerminalUI *ui;
};

#endif // TERMINALUI_H
