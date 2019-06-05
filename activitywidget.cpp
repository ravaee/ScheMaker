#include "activitywidget.h"
#include "ui_activitywidget.h"
#include <QMessageBox>
#include "editactivity.h"
#include "qdebug.h"
#include "program.h"


ActivityWidget::ActivityWidget(QWidget *parent,Activity* activity,QMainWindow* mainWindow) :
    QFrame(parent),
    ui(new Ui::ActivityWidget)
{
    ui->setupUi(this);
    ui->name_lbl->setText(activity->name());
    ui->name_lbl->setStyleSheet(ui->name_lbl->styleSheet() + "\n" +activity->color());
    ui->time_lbl->setText(activity->time().toString("hh:mm"));
    this->_activity = activity;
    ui->widget->setVisible(false);
    connect(mainWindow,SIGNAL(setEditable(bool)),this,SLOT(setEditable(bool)));
}

ActivityWidget::~ActivityWidget()
{
    delete ui;
}

void ActivityWidget::setEditable(bool status)
{
    qDebug()<<"hello";
    ui->widget->setVisible(status);
}


void ActivityWidget::on_edit_btn_clicked()
{
    editActivity = new EditActivity(this,this->_activity);
    connect(editActivity,SIGNAL(activityEdit(Activity*)),this,SLOT(onActivityChanged(Activity*)));
    editActivity->show();
}

void ActivityWidget::onActivityChanged(Activity *activity)
{
    emit activityEditRequested(activity);
}

void ActivityWidget::on_pushButton_3_clicked()
{
    Program program;
    if(program.removeActivity(this->_activity->id())){
        emit activityDeleteRequested(this->_activity->id());
    }else{
        QMessageBox msg(this);
        msg.setText("There was a problem connecting to the database");
        msg.exec();
    }

}

void ActivityWidget::on_details_btn_clicked()
{
    QMessageBox msg(this);
    msg.setText(this->_activity->description());
    msg.exec();
}
