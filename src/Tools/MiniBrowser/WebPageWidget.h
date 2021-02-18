#ifndef WEBPAGEWIDGET_H
#define WEBPAGEWIDGET_H

#include <QWidget>

namespace Ui {
class WebPageWidget;
}

class WebPageWidget : public QWidget
{
    Q_OBJECT

signals:
    void Sig_TitleChanged(const QString &title);
    void Sig_IconChanged(const QIcon &icon);
    void Sig_LoadProgress(int progress);

private slots:
    void Slot_IconChanged(const QIcon &icon);
    void Slot_IconUrlChanged(const QUrl &url);
    void Slot_LoadFinished(bool ok);
    void Slot_LoadProgress(int progress);
    void Slot_LoadStarted();
    void Slot_SelectionChanged();
    void Slot_TitleChanged(const QString &title);
    void Slot_UrlChanged(const QUrl &url);

    void Slot_CollectionStateChange(bool checked);
    void Slot_UrlAddressCommit(const QUrl &Url);
    void Slot_StopLoad();
    void Slot_Reload();
    void Slot_ToLeft();
    void Slot_ToRight();
public:
    explicit WebPageWidget(QWidget *parent = 0);
    ~WebPageWidget();

private:
    Ui::WebPageWidget *ui;
};

#endif // WEBPAGEWIDGET_H
