#ifndef URLADDRESSBAR_H
#define URLADDRESSBAR_H

#include <QWidget>
#include <QUrl>

namespace Ui {
class UrlAddressBar;
}

class UrlAddressBar : public QWidget
{
    Q_OBJECT

public:
    explicit UrlAddressBar(QWidget *parent = 0);
    ~UrlAddressBar();

signals:
    void Sig_CollectionStateChange(bool checked);
    void Sig_UrlAddressCommit(const QUrl &Url);
    void Sig_StopLoad();
    void Sig_Reload();
    void Sig_ToLeft();
    void Sig_ToRight();

public slots:
    void Slot_LoadProgress(int progress);
    void Slot_UrlChanged(const QUrl &url);
    void Slot_LoadFinished(bool ok);
    void Slot_LoadStarted();
    void Slot_CollectionState(bool checked);

private slots:
    void Slot_PusbuttonClicked(bool checked);

protected:
    bool eventFilter(QObject *obj, QEvent *ev);

private:
    Ui::UrlAddressBar *ui;

    unsigned int UrlLoadState;

    QIcon *LoadFailed;
    QIcon *Loadedsuccessfully;
    QIcon *loading;
    QIcon *Collected;
    QIcon *NotCollected;

};

#endif // URLADDRESSBAR_H
