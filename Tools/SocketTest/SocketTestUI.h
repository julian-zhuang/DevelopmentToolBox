#ifndef SOCKETTESTUI_H
#define SOCKETTESTUI_H

#include <QWidget>
#include <QSignalMapper>
#include <QMenu>
#include <QAction>
#include <QTreeWidget>
#include <QDomComment>
#include <QDomNode>
#include <QList>
#include <QTreeWidgetItem>
#include <QTextEdit>
#include <QByteArray>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QObjectUserData>
#include <QNetworkInterface>
#include <QStringList>

QT_BEGIN_NAMESPACE
class DataTransmit;
QT_END_NAMESPACE

namespace Ui {
class SocketTestUI;
}

class SocketTestUI : public QWidget
{
    Q_OBJECT

public:
    explicit SocketTestUI(QWidget *parent = 0);
    ~SocketTestUI();

public slots:
    void Slot_PusBtnClicked();
    void Slot_ClickBoxClicked(int state);
    void Slot_CustomContextMenuRequested(const QPoint &pos);
    void Slot_triggered(QAction *action);    
    void Slot_activated(const QString &text);
    void Slot_activated(int index);
    void Slot_CurrentChanged(int index);
    void Slot_ItemChanged(QTreeWidgetItem * item, int column);

    void Slot_Connected();
    void Slot_Disconnected();
    void Slot_Error(QAbstractSocket::SocketError socketError);
    void Slot_ReadyRead();
    void Slot_NewConnection();

private:
    struct FieldInformation{
        QString Name;
        QString Type;
        unsigned int Length;
        QString Value;
        QString Note;
    };
    int GetByteOrder(QTreeWidget* TreeWidget, QString ByteOrderName, QByteArray &Des, bool BigEndian);
    int ByteOrderAnalyze(QByteArray &Src, QString ByteOrderName, QList<FieldInformation> &Des, bool BigEndian);

private:
    struct SocketUserData : public QObjectUserData{
        unsigned int Mode;   //1:Client  2:Server
        unsigned int From;   //1:SocketCLient 2:SocketServer  3:RepeaterSrcServer 4:RepeaterDesClient
        unsigned int Type;   //1:TCP  2:UDP
    };

private:
    Ui::SocketTestUI *ui;
    QTreeWidget * m_FocuseTreeWidget;
    QMenu *m_ByteOrder;
        QMenu *m_Export;
        QAction *m_ToXML;
        QAction *m_ToCStruct;
        QAction *m_NewField;
        QAction *m_DelField;

    QMenu *m_Log;
        QAction *m_Clear;
        QAction *m_Analysis;

private:
    QTextEdit* TextEdit;

    // Client
    bool TCP_Client_IsConnect;
    QTcpSocket TCP_Client;

    bool UDP_Client_IsBindPort;
    QUdpSocket UDP_Client;
    
    // Server
    QTcpServer TCP_Server;
    bool UDP_Server_IsBindPort;
    QUdpSocket UDP_Server;
    QMap<QString,QAbstractSocket *> Server_Clitents;

    // Repeater
    QTcpServer Repeater_Src_TCP_Server;
    bool Repeater_UDP_Server_IsBindPort;
    QUdpSocket Repeater_Src_UDP_Server;
    QMap<QString,QAbstractSocket *> Repeater_Clitents;

    bool Repeater_Des_TCP_Client_Isconnect;
    QTcpSocket Repeater_Des_TCP_Client;

    bool Repeater_Des_UDP_Client_IsBindPort;
    QUdpSocket Repeater_Des_UDP_Client;

    QDomNode FindNode(QDomNode &Node,QString NodeName);
    QMap<QString, QList<FieldInformation>> ByteOrders;
};

#endif // SOCKETTESTUI_H
