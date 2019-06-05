#ifndef PROGRAM_H
#define PROGRAM_H

#include <QObject>
#include <QList>
#include <Activity.h>
#include <dbmanager.h>

class Program : public QObject
{
    Q_OBJECT

    QList<Activity*> m_activityList;

public:
    explicit Program(QObject *parent = nullptr);

    bool addActivity(Activity* activity);
    QList<Activity *> initialProgram();
    bool editActivity(Activity* activity);
    bool removeActivity(int id);

signals:

private slots:


private:
    DbManager *dbManager;
};

#endif // PROGRAM_H
