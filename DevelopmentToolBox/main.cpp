#include "MainWindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <SqliteService.h>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	
	QTranslator m_Translator;
    QLocale locale;
    switch (locale.language())
	{
	case QLocale::Chinese:
        m_Translator.load("Language_zh.qm");
		break;
	}
	a.installTranslator(&m_Translator);

	if (SqliteService::GetInstance()->OpenDataBase() < 0) {
		QMessageBox::information(NULL, QObject::tr("Error"), QObject::tr("Unable to open database"), QMessageBox::Yes, QMessageBox::Yes);
		return -1;
	}

    MainWindow w;
    w.show();

    return a.exec();
}
