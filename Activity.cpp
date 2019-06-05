#include "activity.h"

Activity::Activity(QString name, QTime time, Days day, QString description, QString color)
{
    this->setName(name);
    this->setDays(day);
    this->setDescription(description);
    this->setTime(time);
    this->setColor(color);
}

Activity::Activity(QString name, QTime time, Days day, QString description, int id, QString color)
{
    this->setName(name);
    this->setDays(day);
    this->setDescription(description);
    this->setTime(time);
    this->setId(id);
    this->setColor(color);
}
