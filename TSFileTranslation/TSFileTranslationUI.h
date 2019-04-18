#ifndef TSFILETRANSLATIONUI_H
#define TSFILETRANSLATIONUI_H

#include <QWidget>

namespace Ui {
class TSFileTranslationUI;
}

class TSFileTranslationUI : public QWidget
{
    Q_OBJECT

public:
    explicit TSFileTranslationUI(QWidget *parent = 0);
    ~TSFileTranslationUI();

private:
    Ui::TSFileTranslationUI *ui;
};

#endif // TSFILETRANSLATIONUI_H
