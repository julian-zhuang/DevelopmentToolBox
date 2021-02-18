#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include "Config.h"
#include "PostService.h"
#include "DiscoveryService.h"
#include <QTreeWidgetItem>
#include "ChatWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Chat; }
QT_END_NAMESPACE

class Chat : public QWidget
{
    Q_OBJECT

public:
    Chat(QWidget *parent = nullptr);
    ~Chat();

private:
    Ui::Chat *ui;
    Config *m_Conf_Ptr;
    PostService *PS_Ptr;
    DiscoveryService *m_DS_Ptr;
    QString m_BindAddr;
    int m_BindPort;
    int m_BroadcastPort;
    QString m_LocalID;

    QTreeWidgetItem *Friend;
    QTreeWidgetItem *LocalAreaNetwork;
    QMap<QString, QTreeWidgetItem*> IP_Item;
    QMap<QString, ChatWindow*> IP_ChartWidget;
};
#endif // CHAT_H
