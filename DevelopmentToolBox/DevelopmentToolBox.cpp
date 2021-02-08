#include "DevelopmentToolBox.h"
#include "ui_DevelopmentToolBox.h"
#include "PluginManager.h"

#include <QDir>
#include <QPushButton>
#include <QApplication>

DevelopmentToolBox::DevelopmentToolBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DevelopmentToolBox)
{
    ui->setupUi(this);
    auto PluginMgr = PluginManager::Instance();
    PluginMgr->LoadPluginDir((QDir::currentPath() + "/plugin").toStdString());
    std::list<std::string> PluginList;
    PluginMgr->PluginList(PluginList);
    std::string Type;
    PluginMgr->PluginType(*(PluginList.begin()), Type);
    //if (Type == "GUI") {
    //    QWidget* ptr = nullptr;
    //    QWidget* parent = this;
    //    PluginMgr->APIRequest(*(PluginList.begin()), "GetWidget", { &ptr , &parent });
    //    ptr->show();
    //    for (int i = 0; i < 50; i++) {
    //        ui->gridLayout_2->addWidget(new QPushButton, i, 0, 1, 1);
    //    }
    //}
}

DevelopmentToolBox::~DevelopmentToolBox()
{
    delete ui;
}

