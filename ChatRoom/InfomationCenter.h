#ifndef INFOMATIONCENTER_H
#define INFOMATIONCENTER_H

#include <QObject>

class InfomationCenter : public QObject
{
    Q_OBJECT
public:
    explicit InfomationCenter(QObject *parent = 0);

signals:

public slots:
};

#endif // INFOMATIONCENTER_H