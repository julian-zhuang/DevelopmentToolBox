#include "WorkUI.h"
#include "ui_WorkUI.h"
#include <QProcess>
#include <QAction>
#include <QDebug>

void WorkUI::Slot_ButtonClicked()
{
    QPushButton *t_pBtn = (QPushButton *)sender();
    if (t_pBtn == ui->pushButton_DayRight) {
        ui->dateTimeEdit->setDateTime(ui->dateTimeEdit->dateTime().addDays(1));
        QString TimeStr = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd");
        ui->textEdit->setHtml(DateStr_LogConnect[TimeStr]);
        return;
    }
    if (t_pBtn == ui->pushButton_DayLeft) {
        ui->dateTimeEdit->setDateTime(ui->dateTimeEdit->dateTime().addDays(-1));
        QString TimeStr = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd");
        ui->textEdit->setHtml(DateStr_LogConnect[TimeStr]);
        return;
    }
    if (Toolbtn_FilePath.find(t_pBtn) != Toolbtn_FilePath.end()) {
        QProcess *t_QProcess = new QProcess;
        t_QProcess->start(Toolbtn_FilePath[t_pBtn]);
    }
}

void WorkUI::Slot_TodayTimeUpdata()
{
    QDateTime NowTime = QDateTime::currentDateTime();
    ui->label_Time_HMS->setText(NowTime.toString("hh:mm:ss"));
    ui->label_Time_YMD->setText(NowTime.toString("yyyy-MM-dd"));
    if (StartWorkTime[ui->label_Time_YMD->text()] <  QDateTime::fromString(ui->label_Time_YMD->text(),"yyyy-MM-dd").toTime_t()){
        StartWorkTime[ui->label_Time_YMD->text()] = NowTime.toTime_t();
    }
    StopWorkTime[ui->label_Time_YMD->text()] = NowTime.toTime_t();
}

void WorkUI::Slot_MenuClick(QAction *action)
{
    if (action == ListWig_ModifyIcon){
        //选择文件
        QFileDialog t_FileDialog(this);
        t_FileDialog.setDirectory(QDir::homePath());
        t_FileDialog.setAcceptMode(QFileDialog::AcceptOpen);
        t_FileDialog.setFileMode(QFileDialog::ExistingFile);
        QStringList filters;
        filters << "Image files (*.png *.ico *.jpg)";
        t_FileDialog.setNameFilters(filters);
        if (t_FileDialog.exec() == QFileDialog::Accepted){
            QStringList fs = t_FileDialog.selectedFiles();
            Toolbtn_FileIcon[FocusToolBtn] = fs[0];
            FocusToolBtn->setIcon(QIcon(fs[0]));
        }
    }
    if (action == ListWig_Delete){

    }
}

void WorkUI::Slot_ShowMenu(const QPoint &pos)
{
    FocusToolBtn = (QToolButton *)sender();
    m_TaskListMenu->exec(cursor().pos());
}

void WorkUI::Slot_TextChange()
{
    QString TimeStr = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd");
    DateStr_LogConnect[TimeStr] = ui->textEdit->toHtml();
}

WorkUI::WorkUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkUI)
{
    ui->setupUi(this);
    //更新时间设置
    m_TodayTimeUpdata.start(1000);
    connect(&m_TodayTimeUpdata,SIGNAL(timeout()),this,SLOT(Slot_TodayTimeUpdata()));
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    connect(ui->pushButton_DayRight, SIGNAL(clicked()), this, SLOT(Slot_ButtonClicked()));
    connect(ui->pushButton_DayLeft, SIGNAL(clicked()), this, SLOT(Slot_ButtonClicked()));
    connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(Slot_TextChange()));

    ui->widget_Tools->installEventFilter(this);

    //添加工具栏按钮
    t_Layout = new QHBoxLayout;
    t_Layout->setDirection(QBoxLayout::LeftToRight);
    ui->widget_Tools->setLayout(t_Layout);
    t_Layout->setContentsMargins(0, 0, 0, 0);

    m_TaskListMenu = new QMenu;
    connect(m_TaskListMenu, SIGNAL(triggered(QAction *)), this, SLOT(Slot_MenuClick(QAction *)));

    ListWig_ModifyIcon = new QAction;
    ListWig_ModifyIcon->setText(tr("Modify Icon"));
    m_TaskListMenu->addAction(ListWig_ModifyIcon);

    ListWig_Delete = new QAction;
    ListWig_Delete->setText(tr("Delete"));
    m_TaskListMenu->addAction(ListWig_Delete);

    QFile XmlFile(QApplication::applicationDirPath() + "/Work/Work.xml");
    if (!XmlFile.open(QFile::Text | QFile::ReadOnly)) {
        qDebug() << "Open " << QApplication::applicationDirPath() + "/Work/Work.xml" << " failed";
    }

    QDateTime NowDatetime = QDateTime::currentDateTime();
    QDomDocument XMLInfo;
    QString LogStr;
    if (XMLInfo.setContent(&XmlFile, &LogStr)) {
        QDomNode ProtocolNode = FindNode(XMLInfo, "Work");
        QDomNode ShortcutNode = FindNode(ProtocolNode,"Shortcut");
        if (!ShortcutNode.isNull()){
            QDomNode t_Node = ShortcutNode.firstChild();
            while(!t_Node.isNull()){
                QDomNamedNodeMap NodeMap = t_Node.attributes();
                auto t_ToolButton = new QToolButton(ui->widget_Tools);
                t_Layout->insertWidget(t_Layout->count() - 1,t_ToolButton);
                QString Path = NodeMap.namedItem("Path").nodeValue();
                QString Name = NodeMap.namedItem("Name").nodeValue();
                QString Icon = NodeMap.namedItem("Icon").nodeValue();
                Toolbtn_FilePath[t_ToolButton] = Path;
                Toolbtn_FileName[t_ToolButton] = Name;
                Toolbtn_FileIcon[t_ToolButton] = Icon;
                t_ToolButton->setIcon(QIcon(Icon));
                t_ToolButton->setIconSize(t_ToolButton->size());
                t_ToolButton->setMinimumSize(QSize(50, 50));
                t_ToolButton->setMaximumSize(QSize(50, 50));
                t_Layout->insertWidget(t_Layout->count() - 1,t_ToolButton);
                t_ToolButton->setContextMenuPolicy(Qt::CustomContextMenu);
                connect(t_ToolButton, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(Slot_ShowMenu(const QPoint &)));
                connect(t_ToolButton, SIGNAL(clicked()), this, SLOT(Slot_ButtonClicked()));
                t_Node = t_Node.nextSibling();
            }
        }
        QDomNode LodNode = FindNode(ProtocolNode,"Log");
        if (!LodNode.isNull()){
            QDomNode t_Node = LodNode.firstChild();
            while(!t_Node.isNull()){
                QDomNamedNodeMap NodeMap = t_Node.attributes();
                QString DateStr = NodeMap.namedItem("Date").nodeValue();
                QString Content = NodeMap.namedItem("Content").nodeValue();
                unsigned int StartTime_t = QDateTime::fromString(NodeMap.namedItem("Start").nodeValue(),"yyyy-MM-dd hh:mm:ss").toTime_t();
                unsigned int StopTime_t = QDateTime::fromString(NodeMap.namedItem("Stop").nodeValue(),"yyyy-MM-dd hh:mm:ss").toTime_t();
                DateStr_LogConnect[DateStr] = Content;
                StartWorkTime[DateStr] = StartTime_t;
                StopWorkTime[DateStr] = StopTime_t;
                t_Node = t_Node.nextSibling();
            }
            QString DateStr = ui->dateTimeEdit->text();
            ui->textEdit->setHtml(DateStr_LogConnect[DateStr]);
        }
    }
    t_Layout->addStretch();
    XmlFile.close();
}

WorkUI::~WorkUI()
{
    QDomDocument doc;
    QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
    doc.appendChild(instruction);

    QDomElement RootNode = doc.createElement("Work");//创建根节点
    doc.appendChild(RootNode);//添加根节点

    QDomElement ShortcutNode = doc.createElement("Shortcut");//创建元素节点
    RootNode.appendChild(ShortcutNode);
    for (auto i = Toolbtn_FileName.begin(); i != Toolbtn_FileName.end(); ++i){
        QDomElement Item = doc.createElement("Item");
        Item.setAttribute("Name",i.value());
        Item.setAttribute("Path",Toolbtn_FilePath[i.key()]);
        Item.setAttribute("Icon",Toolbtn_FileIcon[i.key()]);
        ShortcutNode.appendChild(Item);
    }

    QDomElement LogNode = doc.createElement("Log");//创建元素节点
    for(auto i = DateStr_LogConnect.begin(); i!= DateStr_LogConnect.end();++i){
        QDomElement Item = doc.createElement("Item");
        Item.setAttribute("Date",i.key());
        Item.setAttribute("Content",i.value());
        Item.setAttribute("Start",QDateTime::fromTime_t(StartWorkTime[i.key()]).toString("yyyy-MM-dd hh:mm:ss"));
        Item.setAttribute("Stop",QDateTime::fromTime_t(StopWorkTime[i.key()]).toString("yyyy-MM-dd hh:mm:ss"));
        LogNode.appendChild(Item);
    }
    RootNode.appendChild(LogNode);
    QFile file(QApplication::applicationDirPath() + "/Work/Work.xml");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&file);
        out.setCodec("utf-8");
        doc.save(out, 4, QDomNode::EncodingFromTextStream);
        file.close();
    }

    delete ui;
}

bool WorkUI::eventFilter(QObject *watched, QEvent *event)
{
    if (Toolbtn_FilePath.find((QWidget*)watched) != Toolbtn_FilePath.end()){
        if (event->type() == QEvent::MouseButtonPress && ((QMouseEvent *)event)->button() == Qt::RightButton){

        }
    }
    if (watched == ui->widget_Tools){
        if (event->type() == QEvent::MouseButtonDblClick){
            if (((QMouseEvent *)event)->button() == Qt::LeftButton) {
                //选择文件
                QFileDialog t_FileDialog(this);
                t_FileDialog.setDirectory(QDir::homePath());
                t_FileDialog.setAcceptMode(QFileDialog::AcceptOpen);
                t_FileDialog.setFileMode(QFileDialog::ExistingFile);
                if (t_FileDialog.exec() == QFileDialog::Accepted)
                {
                    auto t_ToolButton = new QToolButton(this);
                    QStringList fs = t_FileDialog.selectedFiles();
                    QFileInfo file_info(fs[0]);
                    QFileIconProvider icon_provider;
                    QIcon icon = icon_provider.icon(file_info);
                    t_ToolButton->setIcon(icon);
                    t_ToolButton->setIconSize(t_ToolButton->size());
                    t_ToolButton->setMinimumSize(QSize(50, 50));
                    t_ToolButton->setMaximumSize(QSize(50, 50));
                    t_Layout->insertWidget(t_Layout->count() - 1,t_ToolButton);
                    t_ToolButton->setContextMenuPolicy(Qt::CustomContextMenu);

                    connect(t_ToolButton, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(Slot_ShowMenu(const QPoint &)));
                    connect(t_ToolButton, SIGNAL(clicked()), this, SLOT(Slot_ButtonClicked()));
                    QString Path = fs[0];
                    QString Name = file_info.fileName();
                    QString Icon = QApplication::applicationDirPath() + "/Work/" + Name + ".png";

                    Toolbtn_FileName[t_ToolButton] = Name;
                    Toolbtn_FilePath[t_ToolButton] = Path;
                    Toolbtn_FileIcon[t_ToolButton] = Icon;
                    icon.pixmap(50,50).save(Icon);
                }
                return true;
            }
        }
    }
}

QDomNode WorkUI::FindNode(QDomNode &Node, QString NodeName)
{
    QDomNode t_Node = Node.firstChild();
    while (!t_Node.isNull()) {
        QString NodeNamea = t_Node.nodeName();
        QString NodeValuea = t_Node.nodeValue();
        if (t_Node.nodeName() == NodeName) {
            return t_Node;
        }
        t_Node = t_Node.nextSibling();
    }
    return QDomNode();
}
