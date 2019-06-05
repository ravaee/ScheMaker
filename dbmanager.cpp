#include "dbmanager.h"
#include "QDebug"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }

    QSqlQuery qry;

    qry.prepare( "CREATE TABLE IF NOT EXISTS programs (id INTEGER UNIQUE PRIMARY KEY, name VARCHAR(30) NOT NULL, description VARCHAR(30) NOT NULL, day INTEGER NOT NULL, time VARCHAR(30) NOT NULL, color VARCHAR(60)) NOT NULL" );

    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug() << "Table created!";
}

bool DbManager::addActivity(const Activity *activity)
{
    bool success = false;

    QSqlQuery query;

    query.prepare("INSERT INTO programs (name , description , day , time, color) VALUES (:name , :description , :day , :time, :color)");

    query.bindValue(":name", activity->name());
    query.bindValue(":description", activity->description());
    query.bindValue(":day", static_cast<std::underlying_type<Days>::type>(activity->days()) + 1);
    query.bindValue(":time", activity->time());
    query.bindValue(":color", activity->color());

    if(query.exec())
    {
        success = true;

    }else{

        qDebug() << "addPerson error:  "
                 << query.lastError();
    }

    return success;
}

QList<Activity*> DbManager::getActivities()
{
    QList<Activity*> activities;

    int id = 0;
    QString name = NULL;
    QString time = NULL;
    QString description = NULL;
    int day = 0;
    QString color = NULL;

    QSqlQuery query;

    query.prepare( "SELECT * FROM programs" );

    if( !query.exec() )

      qDebug() << query.lastError();

    else
    {
      QSqlRecord rec = query.record();

      int cols = rec.count();

      for( int r=0; query.next(); r++ ){

        for( int c=0; c<cols; c++ ){
            id = (rec.fieldName(c) == "id") ? query.value(c).toInt() : id;
            name = (rec.fieldName(c) == "name") ? query.value(c).toString() : name;
            time = (rec.fieldName(c) == "time") ? query.value(c).toString() : time;
            description = (rec.fieldName(c) == "description") ? query.value(c).toString() : description;
            day = (rec.fieldName(c) == "day") ? query.value(c).toInt() : day;
            color = (rec.fieldName(c) == "color") ? query.value(c).toString() : color;
        }

        QStringList times = time.split(':');
        QString hour = times[0];
        QString minute = times[1];
        QStringList secondAndMili = times[2].split('.');
        QString second = secondAndMili[0];

        activities.push_back(new Activity(name,QTime(hour.toInt(),minute.toInt(),second.toInt()),static_cast<Days>(day),description,id,color));
      }

    }

    return activities;

}

bool DbManager::updateActivity(const Activity *activity)
{
    QSqlQuery query;

    query.prepare("UPDATE programs set name=?, description=? , time=?, day=?, color=? WHERE id=?");

    query.addBindValue(activity->name());
    query.addBindValue(activity->description());
    query.addBindValue(activity->time().toString());
    query.addBindValue(static_cast<std::underlying_type<Days>::type>(activity->days()) + 1);
    query.addBindValue(activity->color());
    query.addBindValue(activity->id());


    if(query.exec())
    {
        return true;

    }else{
        qDebug()<<query.lastError();
    }

    return false;
}

bool DbManager::deleteActivity(int id)
{
    QSqlQuery query;

    query.prepare("DELETE from programs WHERE id=?");

    query.addBindValue(id);

    if(query.exec())
    {
        return true;

    }else{
        qDebug()<<query.lastError();
    }

    return false;
}
