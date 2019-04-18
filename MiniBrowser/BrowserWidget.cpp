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
        QString UUid = QUuid::createUuid().toString();
        WebPageWidget *Page = new WebPageWidget;
        Page->setObjectName(UUid);
        QString kl = Page->objectName();
        connect(Page,SIGNAL(Sig_TitleChanged(QString)),this,SLOT(Slot_TitleChanged(QString)));
        connect(Page,SIGNAL(Sig_IconChanged(QIcon)),this,SLOT(Slot_IconChanged(QIcon)));
        int TabIndex = ui->TabBarWidget->addTab(tr("New Page"));
        //TabIndex_PageUUID[TabIndex] = UUid;
        //TabIndex_pPage[TabIndex]= Page;
        ui->TabBarWidget->setTabData(200, UUid);
        PageUUiD_pPage[UUid] = Page;
        PageUUiD_TabIndex[UUid] = TabIndex;
        ui->WebPages_stackedWidget->addWidget(Page);
        ui->WebPages_stackedWidget->setCurrentWidget(Page);
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
    ui->TabBarWidget->setTabIcon(PageUUiD_TabIndex[UUID],icon);
}

void BrowserWidget::Slot_CurrentChanged(int index)
{

}

void BrowserWidget::Slot_TabBarClicked(int index)
{
    QTabBar * TabBar = (QTabBar *)sender();
    QString UUID = TabBar->tabData(200).toString();
    if (PageUUiD_pPage[UUID] != nullptr){
        ui->WebPages_stackedWidget->setCurrentWidget(PageUUiD_pPage[UUID]);
    }
}

void BrowserWidget::Slot_TabBarDoubleClicked(int index)
{
    QTabBar * TabBar = (QTabBar *)sender();
    QString UUID = TabBar->tabData(200).toString();

}

void BrowserWidget::Slot_TabCloseRequested(int index)
{
    QTabBar * TabBar = (QTabBar *)sender();
    QString UUID = TabBar->tabData(200).toString();
    if (PageUUiD_pPage[UUID] != nullptr){
        ui->WebPages_stackedWidget->removeWidget(PageUUiD_pPage[UUID]);
    }
    delete PageUUiD_pPage[UUID];
    PageUUiD_pPage.remove(UUID);
    PageUUiD_TabIndex.remove(UUID);
}
