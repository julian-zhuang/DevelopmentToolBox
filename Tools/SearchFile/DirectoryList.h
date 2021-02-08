#ifndef DIRECTORYLIST_H
#define DIRECTORYLIST_H

#include <QDialog>

namespace Ui {
class DirectoryList;
}

class DirectoryList : public QDialog
{
    Q_OBJECT

public:
    explicit DirectoryList(QWidget *parent = nullptr);
    ~DirectoryList();
    QStringList GetDirectory();
    void SetDirectoryList(QStringList PathList);
private slots:
    void Slot_AddPathClick();
    void Slot_DeletePathClick();
    void Slot_CommitClicked();
    void Slot_CancelClick();
private:
    Ui::DirectoryList *ui;
};

#endif // DIRECTORYLIST_H
