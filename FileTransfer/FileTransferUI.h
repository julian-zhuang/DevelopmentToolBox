#ifndef FILETRANSFERUI_H
#define FILETRANSFERUI_H

#include <QWidget>

namespace Ui {
class FileTransferUI;
}

class FileTransferUI : public QWidget
{
    Q_OBJECT

public:
    explicit FileTransferUI(QWidget *parent = 0);
    ~FileTransferUI();

private:
    Ui::FileTransferUI *ui;
};

#endif // FILETRANSFERUI_H
