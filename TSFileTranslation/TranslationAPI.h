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

public:
    Ui::TranslationAPI *ui;
};

#endif // TRANSLATIONAPI_H
