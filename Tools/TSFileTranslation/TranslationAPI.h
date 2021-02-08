#ifndef TRANSLATIONAPI_H
#define TRANSLATIONAPI_H

#include <QDialog>

namespace Ui {
class TranslationAPI;
}

class TranslationAPI : public QDialog
{
    Q_OBJECT

public:
    explicit TranslationAPI(QWidget *parent = 0);
    ~TranslationAPI();

private slots:
    void Slot_accepted();
    void Slot_rejected();
public:
    void Init();
    bool EnableAPI;
    QString Url;
    QString APIID;
    QString APIKey;
    QString FromLan;
    QString ToLan;
    bool IsAccepted;
private:
    Ui::TranslationAPI *ui;

};

#endif // TRANSLATIONAPI_H
