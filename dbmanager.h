#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include "Activity.h"
#include <QList>

class DbManager
{
public:
    DbManager(const QString& path);
    bool addActivity(const Activity *activity);
    QList<Activity *> getActivities();
    bool updateActivity(const Activity *activity);
    bool deleteActivity(int id);
private:
    QSqlDatabase m_db;

};


#endif // DBMANAGER_H
