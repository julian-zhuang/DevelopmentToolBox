#ifndef COMMUNICATIONCENTER_H
#define COMMUNICATIONCENTER_H

#include <QObject>
#include <QWidget>

class CommunicationCenter : public QObject
{
    Q_OBJECT
public:
    explicit CommunicationCenter(QObject *parent = 0);

signals:

public slots:
};

#endif // COMMUNICATIONCENTER_H