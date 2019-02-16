#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QToolBar>
#include <QToolButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStringList ToolStrs;
    QList<QToolButton *> ToolList;

private slots:
    void Slot_ToolClicked();

    //void Slot_triggered(QAction *action);


};

#endif // MAINWINDOW_H
