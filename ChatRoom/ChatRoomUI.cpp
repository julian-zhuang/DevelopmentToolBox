#include "ChatRoomUI.h"
#include "ui_ChatRoomUI.h"

ChatRoomUI::ChatRoomUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatRoomUI)
{
    ui->setupUi(this);
    ui->treeWidget_GroupList->setVisible(false);
    ui->treeWidget_MemberList->setVisible(true);
    ui->treeWidget_PublicChatMemberList->setVisible(false);
    connect(ui->pushButton_Member,SIGNAL(clicked()),this,SLOT(Slot_ToolBtnClicked()));
    connect(ui->pushButton_Group,SIGNAL(clicked()),this,SLOT(Slot_ToolBtnClicked()));
    connect(ui->pushButton_PublicChat,SIGNAL(clicked()),this,SLOT(Slot_ToolBtnClicked()));
}

ChatRoomUI::~ChatRoomUI()
{
    delete ui;
}

void ChatRoomUI::Slot_ToolBtnClicked()
{
    if (sender() == ui->pushButton_PublicChat){
        ui->treeWidget_PublicChatMemberList->setVisible(true);
        ui->treeWidget_GroupList->setVisible(false);
        ui->treeWidget_MemberList->setVisible(false);
    }
    if (sender() == ui->pushButton_Member){
        ui->treeWidget_MemberList->setVisible(true);
        ui->treeWidget_GroupList->setVisible(false);
        ui->treeWidget_PublicChatMemberList->setVisible(false);
    }
    if (sender() == ui->pushButton_Group){
        ui->treeWidget_GroupList->setVisible(true);
        ui->treeWidget_MemberList->setVisible(false);
        ui->treeWidget_PublicChatMemberList->setVisible(false);
    }
}
