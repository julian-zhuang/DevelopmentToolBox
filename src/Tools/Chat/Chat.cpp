#include "Chat.h"
#include "ui_Chat.h"

#include <QUuid>
#include <QJsonObject>
#include <QJsonDocument>

#pragma execution_character_set("utf-8")
Chat::Chat(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Chat)
{
    ui->setupUi(this);

    connect(ui->toolButton_List, &QAbstractButton::clicked, [this] {
        ui->stackedWidget->setCurrentWidget(ui->Widget_List);
        });
    connect(ui->toolButton_Setting, &QAbstractButton::clicked, [this] {
        ui->stackedWidget->setCurrentWidget(ui->Setting_page);
        });

    //ui->treeWidget_UerList->setContextMenuPolicy(Qt::CustomContextMenu);
    //ui->treeWidget_UerList->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->treeWidget_UerList->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->treeWidget_UerList, &QTreeWidget::itemDoubleClicked, [this](QTreeWidgetItem* item, int column) {
            auto NodeType = item->data(0, 256 + 10).toInt();
            if (NodeType != 210) {
                return;
            }
            auto Addr = item->data(0, 256 + 20).toString();
            auto ID = item->data(0, 256 + 21).toString();
            auto Port = item->data(0, 256 + 22).toInt();
            ChatWindow*& Widget = IP_ChartWidget[ID];
            if (Widget == nullptr) {
                Widget = new ChatWindow(ID);
                ui->stackedWidget_Conversation->addWidget(Widget);
            }
            ui->stackedWidget_Conversation->setCurrentWidget(Widget);
        });


    Friend = new QTreeWidgetItem;
    Friend->setData(0, 256 + 1, 100);
    Friend->setText(0, tr("我的好友"));
    LocalAreaNetwork = new QTreeWidgetItem;
    LocalAreaNetwork->setData(0, 256 + 1, 200);
    LocalAreaNetwork->setText(0, tr("局域网"));

    ui->treeWidget_UerList->addTopLevelItem(LocalAreaNetwork);
    ui->treeWidget_UerList->addTopLevelItem(Friend);
    ui->treeWidget_UerList->expandAll();

    m_Conf_Ptr = Config::Instance();
    PS_Ptr = PostService::Instance();
    m_DS_Ptr = DiscoveryService::Instance();

    m_Conf_Ptr->Read("config/config.ini");

    m_Conf_Ptr->GetValue("NET", "BindIP", m_BindAddr);
    m_Conf_Ptr->GetValue("NET", "BindPort", m_BindPort);
    m_Conf_Ptr->GetValue("NET", "BroadcastPort", m_BroadcastPort);
    m_Conf_Ptr->GetValue("CHAT", "ID", m_LocalID);

    m_DS_Ptr->BindRecvPort(m_BroadcastPort);
    QJsonObject BroadcastJson;
    BroadcastJson.insert("NodeType", "Chat");
    BroadcastJson.insert("ID", m_LocalID);
    BroadcastJson.insert("Addr", m_BindAddr);
    BroadcastJson.insert("Port", m_BindPort);
    m_DS_Ptr->AddBroadCastContent(m_BroadcastPort, QJsonDocument(BroadcastJson).toJson());

    PS_Ptr->SetLocalAddr(m_LocalID, QHostAddress(m_BindAddr), m_BindPort);
    connect(m_DS_Ptr, &DiscoveryService::Signal_RecvBroadCastContent, [this](quint16 recv_port, QHostAddress client_addr, QByteArray Datagram) {
        QJsonObject JsonObj = QJsonDocument::fromJson(Datagram).object();
        if (JsonObj.isEmpty() == true) {
            if (QString(Datagram) == "GoodbyeEveryone") {
                auto Item = IP_Item[client_addr.toString()];
                PS_Ptr->DelRemoteAddr(Item->data(0, 256 + 21).toString());
                delete Item;
            }
            return;
        }
        auto NodeType = JsonObj.value("NodeType").toString();
        auto Addr = JsonObj.value("Addr").toString();
        auto ID = JsonObj.value("ID").toString();
        auto Port = JsonObj.value("Port").toInt();
        if (IP_Item.contains(client_addr.toString()) == false && ID != m_LocalID) {
            QTreeWidgetItem* Item = new QTreeWidgetItem;
            Item->setData(0, 256 + 10, 210);
            Item->setData(0, 256 + 20, Addr);
            Item->setData(0, 256 + 21, ID);
            Item->setData(0, 256 + 22, Port);
            Item->setText(0, Addr);
            LocalAreaNetwork->addChild(Item);
            IP_Item[client_addr.toString()] = Item;
            PS_Ptr->AddRemoteAddr(ID, QHostAddress(Addr), Port);
        }
    });

    bool m_ReadReceipt;
    bool m_AutoRecvFile;
    bool m_AutoRecvImage;
    bool m_AutoRecvAudio;
    bool m_AutoRecvVideo;
    m_Conf_Ptr->GetValue("MSG", "ReadReceipt", m_ReadReceipt, true);
    m_Conf_Ptr->GetValue("MSG", "AutoRecvFile", m_AutoRecvFile, true);
    m_Conf_Ptr->GetValue("MSG", "AutoRecvImage", m_AutoRecvImage, true);
    m_Conf_Ptr->GetValue("MSG", "AutoRecvAudio", m_AutoRecvAudio, true);
    m_Conf_Ptr->GetValue("MSG", "AutoRecvVideo", m_AutoRecvVideo, true);
}

Chat::~Chat()
{
    DiscoveryService::DestoryInstance();
    PostService::DestoryInstance();
    Config::DestoryInstance();
    delete ui;
}

