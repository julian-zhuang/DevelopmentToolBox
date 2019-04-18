#include "QWebEngineViewEx.h"

QWebEngineView *QWebEngineViewEx::createWindow(QWebEnginePage::WebWindowType type)
{
    if (type == QWebEnginePage::WebBrowserWindow){
        return new QWebEngineView;
    }else if(type == QWebEnginePage::WebBrowserTab){
        return this;
    }else if(type == QWebEnginePage::WebDialog){
        return this;
    }else if(type == QWebEnginePage::WebBrowserBackgroundTab){
        return this;
    }
    return QWebEngineView::createWindow(type);
}

QWebEngineViewEx::QWebEngineViewEx(QWidget *parent) : QWebEngineView(parent)
{
}
