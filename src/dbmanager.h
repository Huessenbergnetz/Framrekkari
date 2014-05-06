#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>

class DbManager : public QObject
{
    Q_OBJECT
public:
    explicit DbManager(QObject *parent = 0);

    bool openDB();
    bool createTables();
    bool closeDB();

signals:

public slots:

private:
    QSqlDatabase db;

};

#endif // DBMANAGER_H
