#include "UrlAddressBar.h"
#include "ui_UrlAddressBar.h"
#include <QKeyEvent>
UrlAddressBar::UrlAddressBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UrlAddressBar)
{
    ui->setupUi(this);
    ui->lineEdit_Url->installEventFilter(this);
    UrlLoadState = 0;
    LoadFailed = new QIcon("://LoadFailed.png");
    Loadedsuccessfully = new QIcon("://shuaxin.png");
    loading = new QIcon("://jindushibai.png");
    Collected = new QIcon("://xiazai12.png");
    NotCollected = new QIcon("://guanzhu.png");
    foreach(QToolButton* var, this->findChildren<QToolButton *>()) {
        connect(var,SIGNAL(clicked(bool)),this,SLOT(Slot_PusbuttonClicked(bool)));
    }
}

UrlAddressBar::~UrlAddressBar()
{
    delete ui;
}

void UrlAddressBar::Slot_UrlChanged(const QUrl &url)
{
    ui->lineEdit_Url->setText(url.toString());
}

void UrlAddressBar::Slot_LoadFinished(bool ok)
{
    if (ok == true){
        ui->toolButton_Refresh->setIcon(*Loadedsuccessfully);
        UrlLoadState = 0;
    }
    if (ok == false){
        ui->toolButton_Refresh->setIcon(*LoadFailed);
        UrlLoadState = 2;
    }
}

void UrlAddressBar::Slot_LoadStarted()
{
    ui->toolButton_Refresh->setIcon(*loading);
    UrlLoadState = 1;
}

void UrlAddressBar::Slot_CollectionState(bool checked)
{
    emit Sig_CollectionStateChange(checked);
}

void UrlAddressBar::Slot_PusbuttonClicked(bool checked)
{
    QToolButton * ToolBtn = (QToolButton *)sender();
    if (ToolBtn == ui->toolButton_Refresh){
        if (UrlLoadState == 0){
            emit Sig_Reload();
        }
        if (UrlLoadState == 1){
            emit Sig_StopLoad();
        }
        if (UrlLoadState == 2){
            emit Sig_Reload();
        }
    }
    if (ToolBtn == ui->toolButton_Left){
        emit Sig_ToLeft();
    }
    if (ToolBtn == ui->toolButton_Right){
        emit Sig_ToRight();
    }
}

bool UrlAddressBar::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == ui->lineEdit_Url){
        if (ev->type() == QEvent::KeyPress){
            QKeyEvent *KeyEvent = (QKeyEvent *)ev;
            int kl  = KeyEvent->key();
            if (KeyEvent->key() == Qt::Key_Enter || KeyEvent->key() == Qt::Key_Return){
                emit Sig_UrlAddressCommit(QUrl(ui->lineEdit_Url->text()));
            }
        }
    }
}
