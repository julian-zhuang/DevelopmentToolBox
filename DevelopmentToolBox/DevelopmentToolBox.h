#ifndef DEVELOPMENTTOOLBOX_H
#define DEVELOPMENTTOOLBOX_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class DevelopmentToolBox; }
QT_END_NAMESPACE

class DevelopmentToolBox : public QWidget
{
    Q_OBJECT

public:
    DevelopmentToolBox(QWidget *parent = nullptr);
    ~DevelopmentToolBox();

private:
    Ui::DevelopmentToolBox *ui;
};
#endif // DEVELOPMENTTOOLBOX_H
