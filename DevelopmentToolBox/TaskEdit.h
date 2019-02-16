#ifndef TASKEDIT_H
#define TASKEDIT_H

#include <QDialog>

namespace Ui {
class TaskEdit;
}

class TaskEdit : public QDialog
{
    Q_OBJECT

public:
    explicit TaskEdit(QString TaskName,QString Taskcontent, QWidget *parent = nullptr);
    ~TaskEdit();
	QString TaskID;
    QString TaskName;
    QString Taskcontent;
private:
    Ui::TaskEdit *ui;
private slots:
	void Slot_TextChange(const QString &);
	void Slot_TextChange();
};

#endif // TASKEDIT_H
