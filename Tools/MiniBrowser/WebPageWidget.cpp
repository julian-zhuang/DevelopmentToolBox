#include "WebPageWidget.h"
#include "ui_WebPageWidget.h"

void WebPageWidget::Slot_IconChanged(const QIcon &icon)
{
    emit Sig_IconChanged(icon);
}

void WebPageWidget::Slot_IconUrlChanged(const QUrl &url)
{

}

void WebPageWidget::Slot_LoadFinished(bool ok)
{
    ui->Url_widget->Slot_LoadFinished(ok);
    ui->Loading_progressBar->setVisible(true);
}

void WebPageWidget::Slot_LoadProgress(int progress)
{
    ui->Loading_progressBar->setValue(progress);
    if(progress >= 100){
        ui->Loading_progressBar->setVisible(false);
    }
}

void WebPageWidget::Slot_LoadStarted()
{
    ui->Url_widget->Slot_LoadStarted();
    ui->Loading_progressBar->setVisible(true);
}

void WebPageWidget::Slot_SelectionChanged()
{

}

void WebPageWidget::Slot_TitleChanged(const QString &title)
{
    emit Sig_TitleChanged(title);
}

void WebPageWidget::Slot_UrlChanged(const QUrl &url)
{
    ui->Url_widget->Slot_UrlChanged(url);
}

void WebPageWidget::Slot_CollectionStateChange(bool checked)
{

}

void WebPageWidget::Slot_UrlAddressCommit(const QUrl &Url)
{
    ui->Web_widget->load(Url);
}

void WebPageWidget::Slot_StopLoad()
{
    ui->Web_widget->stop();
}

void WebPageWidget::Slot_Reload()
{
    ui->Web_widget->reload();
}

void WebPageWidget::Slot_ToLeft()
{
    ui->Web_widget->back();
}

void WebPageWidget::Slot_ToRight()
{
    ui->Web_widget->forward();
}

WebPageWidget::WebPageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebPageWidget)
{
    ui->setupUi(this);
    ui->Loading_progressBar->setVisible(false);
    connect(ui->Web_widget,SIGNAL(iconChanged(QIcon)),this,SLOT(Slot_IconChanged(QIcon)));
    connect(ui->Web_widget,SIGNAL(iconUrlChanged(QUrl)),this,SLOT(Slot_IconUrlChanged(QUrl)));
    connect(ui->Web_widget,SIGNAL(loadFinished(bool)),this,SLOT(Slot_LoadFinished(bool)));
    connect(ui->Web_widget,SIGNAL(loadProgress(int)),this,SLOT(Slot_LoadProgress(int)));
    connect(ui->Web_widget,SIGNAL(loadStarted()),this,SLOT(Slot_LoadStarted()));
    connect(ui->Web_widget,SIGNAL(selectionChanged()),this,SLOT(Slot_SelectionChanged()));
    connect(ui->Web_widget,SIGNAL(titleChanged(QString)),this,SLOT(Slot_TitleChanged(QString)));
    connect(ui->Web_widget,SIGNAL(urlChanged(QUrl)),this,SLOT(Slot_UrlChanged(QUrl)));

    connect(ui->Url_widget,SIGNAL(Sig_CollectionStateChange(bool)),this,SLOT(Slot_CollectionStateChange(bool)));
    connect(ui->Url_widget,SIGNAL(Sig_UrlAddressCommit(QUrl)),this,SLOT(Slot_UrlAddressCommit(QUrl)));
    connect(ui->Url_widget,SIGNAL(Sig_Reload()),this,SLOT(Slot_Reload()));
    connect(ui->Url_widget,SIGNAL(Sig_StopLoad()),this,SLOT(Slot_StopLoad()));
    connect(ui->Url_widget,SIGNAL(Sig_ToLeft()),this,SLOT(Slot_ToLeft()));
    connect(ui->Url_widget,SIGNAL(Sig_ToRight()),this,SLOT(Slot_ToRight()));
}

WebPageWidget::~WebPageWidget()
{
    delete ui;
}
