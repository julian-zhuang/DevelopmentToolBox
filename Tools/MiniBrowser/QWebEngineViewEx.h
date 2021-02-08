#ifndef QWEBENGINEVIEWEX_H
#define QWEBENGINEVIEWEX_H

#include <QObject>
#include <QWebEngineView>

class QWebEngineViewEx : public QWebEngineView
{
protected:
    QWebEngineView *createWindow(QWebEnginePage::WebWindowType type);
public:
    QWebEngineViewEx(QWidget *parent = 0);
    ~QWebEngineViewEx() = default;
};

#endif // QWEBENGINEVIEWEX_H
