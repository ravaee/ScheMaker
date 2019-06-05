#include "mainpage.h"
#include "ui_mainpage.h"
#include <QDialog>
#include <QDebug>
#include <activitywidget.h>
#include <QMessageBox>

MainPage::MainPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    connect(this, SIGNAL(activitiesChanged(QList<Activity*>)),this, SLOT(onActivitiesChanged()));
    setActivities(program()->initialProgram());

    QAction *editAction = ui->menuNew_Feature->actions().at(1);
    QAction *addAction = ui->menuNew_Feature->actions().at(0);
    QAction *helpAction = ui->menuHelp->actions().at(0);
    QAction *aboutAction = ui->menuHelp->actions().at(1);
    connect(editAction, SIGNAL(triggered()), this, SLOT(on_actionEdit_triggred()));
    connect(addAction, SIGNAL(triggered()), this, SLOT(on_actionAddNew_Feature_triggered()));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(on_helpAction_triggred()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(on_aboutAction_triggered()));
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::dialogIsFinished(int result)
{
    if(result == QDialog::Accepted){

        setActivities(program()->initialProgram());

    }
}

void MainPage::on_actionAddNew_Feature_triggered()
{
    this->addActivity = new AddActivity(this);
    QObject::connect(addActivity, SIGNAL(finished (int)), this, SLOT(dialogIsFinished(int)));
    this->addActivity->exec();
}

void MainPage::on_actionEdit_triggred()
{

    if(ui->menuNew_Feature->actions().at(1)->isChecked()){
        foreach (ActivityWidget* activityWidget, this->activityWidgets) {
            activityWidget->setEditable(true);
        }
    }else{
        foreach (ActivityWidget* activityWidget, this->activityWidgets) {
            activityWidget->setEditable(false);
        }
    }
}

void MainPage::onActivitiesChanged()
{

    foreach (ActivityWidget* activityWidget, this->activityWidgets) {
        if(activityWidget->_activity->id() != this->shouldNotCleanWidgetId){
            delete activityWidget;
        }else{
            activityWidget->setVisible(false);
        }
    }

    this->activityWidgets.clear();

    foreach (Activity* activity, this->activities()) {

        ActivityWidget *activityw = new ActivityWidget(nullptr,activity);

        connect(activityw,SIGNAL(activityEditRequested(Activity*)),this,SLOT(onActivityEdited(Activity*)));
        connect(activityw,SIGNAL(activityDeleteRequested(int)),this,SLOT(onActivityDeleted(int)));

        if(activity->days() == Saturday){
            ui->widget0->layout()->addWidget(activityw);
        }else if(activity->days() == Sunday){
            ui->widget1->layout()->addWidget(activityw);
        }else if(activity->days() == Monday){
            ui->widget2->layout()->addWidget(activityw);
        }else if(activity->days() == Tuesday){
            ui->widget3->layout()->addWidget(activityw);
        }else if(activity->days() == Wednesday){
            ui->widget4->layout()->addWidget(activityw);
        }else if(activity->days() == Thursday){
            ui->widget5->layout()->addWidget(activityw);
        }else if(activity->days() == Friday){
            ui->widget6->layout()->addWidget(activityw);
        }

        activityWidgets.push_back(activityw);
    }

    if(ui->menuNew_Feature->actions().at(1)->isChecked()){
        foreach (ActivityWidget* activityWidget, this->activityWidgets) {
            activityWidget->setEditable(true);
        }
    }else{
        foreach (ActivityWidget* activityWidget, this->activityWidgets) {
            activityWidget->setEditable(false);
        }
    }
}

void MainPage::onActivityEdited(Activity *activity)
{
    this->shouldNotCleanWidgetId = activity->id();
    this->setActivities(program()->initialProgram());
}

void MainPage::onActivityDeleted(int id)
{

    foreach (ActivityWidget* aw, this->activityWidgets) {
        if(aw->_activity->id() == id){
            aw->setVisible(false);
            this->activityWidgets.removeOne(aw);
        }
    }

}

void MainPage::on_helpAction_triggred()
{
    QMessageBox messagebox;
    messagebox.setText("ScaMaker is so easier than you think just click on add button from File tab on menuBar and start programming your schedule also you can edit it just from Edit action.");
    messagebox.exec();
}

void MainPage::on_aboutAction_triggered()
{
    QMessageBox messagebox;
    messagebox.setText("ScaMaker has designed and develop by Mohamad ravaei.\nIt is free to use under MIT license so you can access to the source code just in my github account:  www.github.com/ravaee. \n\n Also you can be in touch with me at:\n\n ravaeimohamad@gmail.com \n www.linkedin.com/in/mohamad-ravaei-4abb45106 \n www.instagram.com/mohamad_ravaei");
    messagebox.exec();
}

