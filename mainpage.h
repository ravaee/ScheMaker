#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>
#include <program.h>
#include "addactivity.h"
#include "Activity.h"
#include <QList>
#include <algorithm>
#include <QLayout>
#include <QFrame>
#include <activitywidget.h>

namespace Ui {
class MainPage;
}

class MainPage : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QList<Activity*> activities READ activities WRITE setActivities NOTIFY activitiesChanged)


public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();

    Program* program(){
        this->_program = (this->_program != NULL) ? this->_program : new Program();
        return this->_program;
    }

    QList<Activity*> activities()
    {
        return bubbleSort(m_activities);
    }

    void swap(Activity *xp, Activity *yp)
    {
        Activity *temp = xp;
        xp = yp;
        yp = temp;
    }

    void clearWidgets(QLayout * layout) {
       if (! layout)
          return;
       while (auto item = layout->takeAt(0)) {
          delete item->widget();
          clearWidgets(item->layout());
       }
    }

    QList<Activity*> bubbleSort(QList<Activity*> arr)
    {
       int i, j;
       int n = arr.length();
       for (i = 0; i < n-1; i++)
           for (j = 0; j < n-i-1; j++){

               QString t1 = arr[j]->time().toString("hh:mm").split(':')[0] + arr[j]->time().toString("hh:mm").split(':')[1];
               QString t2 = arr[j+1]->time().toString("hh:mm").split(':')[0] + arr[j+1]->time().toString("hh:mm").split(':')[1];

               int time1 = t1.toInt();
               int time2 = t2.toInt();

               if (time1 > time2){
                  swap(arr[j], arr[j+1]);
                  Activity *temp = arr[j];
                  arr[j] = arr[j+1];
                  arr[j+1] = temp;
               }
           }

       return arr;
    }

public slots:

    void dialogIsFinished(int result);

    void setActivities(QList<Activity*> activities)
    {
        if (m_activities == activities)
            return;

        m_activities = activities;
        emit activitiesChanged(m_activities);
    }

signals:
    void activitiesChanged(QList<Activity*> activities);
    void setEditable(bool);
private slots:
   void on_actionAddNew_Feature_triggered();
   void on_actionEdit_triggred();
   void onActivitiesChanged();
   void onActivityEdited(Activity* activity);
   void onActivityDeleted(int id);
   void on_helpAction_triggred();
   void on_aboutAction_triggered();

private:
    Program *_program = NULL;
    Ui::MainPage *ui;
    AddActivity *addActivity;
    QList<ActivityWidget*> activityWidgets;
    QList<Activity*> m_activities;
    int shouldNotCleanWidgetId = -1;
};

#endif // MAINPAGE_H
