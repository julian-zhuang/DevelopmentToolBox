#include "DevelopmentToolBox.h"
#include "ui_DevelopmentToolBox.h"
#include "PluginManager.h"

#include <QDir>
#include <QPushButton>
#include <QApplication>
#include <QVBoxLayout>

DevelopmentToolBox::DevelopmentToolBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DevelopmentToolBox)
{
    ui->setupUi(this);
    auto PluginMgr = PluginManager::Instance();
    PluginMgr->LoadPluginDir((QDir::currentPath() + "/plugin").toStdString());
    std::list<std::string> PluginList;
    PluginMgr->PluginList(PluginList);

    QList<QPushButton*> Buts;
    for (auto i = PluginList.begin(); i != PluginList.end(); i++) {
        std::string PublicID = *i;
        std::string Type;
        PluginMgr->PluginType(PublicID, Type);
        if (Type != "GUI") {
            return;
        }

        QWidget* Widget_Ptr = nullptr;
        QWidget* parent = this;
        PluginMgr->APIRequest(*(i), "GetWidget", { &Widget_Ptr , &parent });
        ui->stackedWidget->addWidget(Widget_Ptr);

        QPushButton* Btn = new QPushButton;
        Btn->setText(PublicID.c_str());
        Buts.append(Btn);
        connect(Btn, &QPushButton::clicked, [this, Btn, Widget_Ptr] {
                ui->stackedWidget->setCurrentWidget(Widget_Ptr);
            });
    }
    int Row = 0;
    auto layout = new QVBoxLayout;
    ui->scrollAreaWidgetContents->setLayout(layout);
    foreach (auto var, Buts)
    {
        layout->addWidget(var, Row++);
    }
    layout->addStretch(1);
}

DevelopmentToolBox::~DevelopmentToolBox()
{
    delete ui;
}

