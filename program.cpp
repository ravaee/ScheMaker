#include "program.h"
#include <QDebug>
#include <dbmanager.h>

Program::Program(QObject *parent) : QObject(parent)
{
   dbManager = new DbManager("programs.db");
}

bool Program::addActivity(Activity *activity)
{

    if(dbManager->addActivity(activity)){
        return true;

    }else{
        return false;
        qDebug()<<"The problem happened during add to database Find Mohamad Ravaei and say rouds to him :)";
    }

}

QList<Activity*> Program::initialProgram()
{
    return dbManager->getActivities();
}

bool Program::editActivity(Activity *activity)
{
    return dbManager->updateActivity(activity);
}

bool Program::removeActivity(int id)
{
    return dbManager->deleteActivity(id);
}


