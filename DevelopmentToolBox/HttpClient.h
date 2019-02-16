#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QWidget>

namespace Ui {
class HttpClient;
}

class HttpClient : public QWidget
{
    Q_OBJECT

public:
    explicit HttpClient(QWidget *parent = nullptr);
    ~HttpClient();

private:
    Ui::HttpClient *ui;
};

#endif // HTTPCLIENT_H
