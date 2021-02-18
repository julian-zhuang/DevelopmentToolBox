#include "DevelopmentToolBox.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DevelopmentToolBox w;
    w.show();
    return a.exec();
}
