#ifndef BROWSERWIDGET_H
#define BROWSERWIDGET_H

#include <QWidget>
#include <QMap>
#include <QWebEngineView>
#include "UrlAddressBar.h"
#include "WebPageWidget.h"

namespace Ui {
class BrowserWidget;
}

class BrowserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BrowserWidget(QWidget *parent = 0);
    ~BrowserWidget();
public slots:
    void Slot_PusbuttonClicked(bool checked);

    void Slot_CurrentChanged(int index);
    void Slot_TabBarClicked(int index);
    void Slot_TabBarDoubleClicked(int index);
    void Slot_TabCloseRequested(int index);
    void Slot_TabMoved(int from, int to);

    void Slot_TitleChanged(const QString &title);
    void Slot_IconChanged(const QIcon &icon);
private:
    int UrlLoadState;
    QMap<int, int> TabIndex_PageIndex;
    QMap<QString, int> PageUUiD_TabIndex;
    Ui::BrowserWidget *ui;
};

#endif // BROWSERWIDGET_H
