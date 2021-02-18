#include "BrowserWidget.h"
#include "ui_BrowserWidget.h"
#include <QPushButton>
#include <QUuid>
#include <QVBoxLayout>

BrowserWidget::BrowserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrowserWidget)
{
    ui->setupUi(this);
    ui->TabBarWidget->setTabsClosable(true);
    connect(ui->TabBarWidget,SIGNAL(currentChanged(int)),this,SLOT(Slot_CurrentChanged(int)));
    connect(ui->TabBarWidget,SIGNAL(tabBarClicked(int)),this,SLOT(Slot_TabBarClicked(int)));
    connect(ui->TabBarWidget,SIGNAL(tabBarDoubleClicked(int)),this,SLOT(Slot_TabBarDoubleClicked(int)));
    connect(ui->TabBarWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(Slot_TabCloseRequested(int)));
    foreach(QToolButton* var, this->findChildren<QToolButton *>()) {
        connect(var,SIGNAL(clicked(bool)),this,SLOT(Slot_PusbuttonClicked(bool)));
    }
}

BrowserWidget::~BrowserWidget()
{
    delete ui;
}

void BrowserWidget::Slot_PusbuttonClicked(bool checked)
{
    QToolButton *ToolBtn = (QToolButton *)sender();
    if (ToolBtn == ui->toolButton_NewPage){
        QString UUid = QUuid::createUuid().toString().toUtf8().toHex();
        WebPageWidget *Page = new WebPageWidget;
        Page->setObjectName(UUid);
        connect(Page,SIGNAL(Sig_TitleChanged(QString)),this,SLOT(Slot_TitleChanged(QString)));
        connect(Page,SIGNAL(Sig_IconChanged(QIcon)),this,SLOT(Slot_IconChanged(QIcon)));
        int TabIndex = ui->TabBarWidget->addTab(tr("New Page"));
        int PageIndex = ui->WebPages_stackedWidget->addWidget(Page);
        TabIndex_PageIndex[TabIndex] = PageIndex;
        PageUUiD_TabIndex[UUid] = TabIndex;
        ui->WebPages_stackedWidget->setCurrentIndex(PageIndex);
        ui->TabBarWidget->setCurrentIndex(TabIndex);
    }
}

void BrowserWidget::Slot_TitleChanged(const QString &title)
{
    WebPageWidget* Page = (WebPageWidget*)sender();
    QString UUID = Page->objectName();
    ui->TabBarWidget->setTabText(PageUUiD_TabIndex[UUID],title);
}

void BrowserWidget::Slot_IconChanged(const QIcon &icon)
{
    WebPageWidget* Page = (WebPageWidget*)sender();
    QString UUID = Page->objectName();
    ui->TabBarWidget->setTabIcon(PageUUiD_TabIndex[UUID], icon);
}

void BrowserWidget::Slot_CurrentChanged(int index)
{

}

void BrowserWidget::Slot_TabBarClicked(int index)
{
    if (TabIndex_PageIndex.contains(index) == true){
        ui->WebPages_stackedWidget->setCurrentIndex(TabIndex_PageIndex[index]);
    }
}

void BrowserWidget::Slot_TabBarDoubleClicked(int index)
{

}

void BrowserWidget::Slot_TabCloseRequested(int index)
{
    if (TabIndex_PageIndex.contains(index) == true){
        WebPageWidget* Page = (WebPageWidget*)ui->WebPages_stackedWidget->widget(TabIndex_PageIndex[index]);
        TabIndex_PageIndex.remove(index);
        ui->TabBarWidget->removeTab(index);
        delete Page;
    }
}

void BrowserWidget::Slot_TabMoved(int from, int to)
{
}
