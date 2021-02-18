#ifndef FILEMESSAGE_H
#define FILEMESSAGE_H

#include <QWidget>

namespace Ui {
class FileMessage;
}

class FileMessage : public QWidget
{
    Q_OBJECT

public:
    explicit FileMessage(QWidget *parent = 0);
    ~FileMessage();

private:
    Ui::FileMessage *ui;
};

#endif // FILEMESSAGE_H
