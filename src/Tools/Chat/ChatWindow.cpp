#include "ChatWindow.h"
#include "ui_ChatWindow.h"
#include <PostService.h>

ChatWindow::ChatWindow(QString id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWindow)
{
    m_Local_ID = id;
    ui->setupUi(this);
    ui->stackedWidget->setVisible(false);

    connect(ui->pushButton_Send, &QPushButton::clicked, []{

    });
}

ChatWindow::~ChatWindow()
{
    delete ui;
}
