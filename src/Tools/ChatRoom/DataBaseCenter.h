#ifndef DATABASECENTER_H
#define DATABASECENTER_H

#include <QObject>

class DataBaseCenter : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseCenter(QObject *parent = 0);

signals:

public slots:
};

#endif // DATABASECENTER_H