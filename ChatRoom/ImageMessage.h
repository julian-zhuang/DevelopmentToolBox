#ifndef IMAGEMESSAGE_H
#define IMAGEMESSAGE_H

#include <QWidget>

namespace Ui {
class ImageMessage;
}

class ImageMessage : public QWidget
{
    Q_OBJECT

public:
    explicit ImageMessage(QWidget *parent = 0);
    ~ImageMessage();

private:
    Ui::ImageMessage *ui;
};

#endif // IMAGEMESSAGE_H
