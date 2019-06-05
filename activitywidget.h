#ifndef ACTIVITYWIDGET_H
#define ACTIVITYWIDGET_H

#include <QFrame>
#include "Activity.h"
#include "editactivity.h"
#include <QMainWindow>

namespace Ui {
class ActivityWidget;
}

class ActivityWidget : public QFrame
{
    Q_OBJECT

public:
    explicit ActivityWidget(QWidget *parent = nullptr,Activity* activity=nullptr,QMainWindow* mainWindow = nullptr);
    Activity* _activity;
    ~ActivityWidget();


public slots:
    void setEditable(bool status);

private slots:
    void on_edit_btn_clicked();
    void onActivityChanged(Activity* activity);
    void on_pushButton_3_clicked();

    void on_details_btn_clicked();

signals:
    void activityEditRequested(Activity* activity);
    void activityDeleteRequested(int id);

private:
    Ui::ActivityWidget *ui;

    EditActivity *editActivity;
};

#endif // ACTIVITYWIDGET_H
