#include "editactivity.h"
#include "ui_editactivity.h"
#include "program.h"
#include <QDebug>
#include <QMessageBox>

int _dayIndex = 0;
QString _color = NULL;

EditActivity::EditActivity(QWidget *parent,Activity *activity) :
    QDialog(parent),
    ui(new Ui::EditActivity)
{
    ui->setupUi(this);
    this->_activity = activity;

    this->ui->activityNameText->setText(activity->name());
    this->ui->ActivityDescriptionText->setPlainText(activity->description());
    this->ui->activityTimeText->setTime(activity->time());
    this->ui->activityDayText->setCurrentIndex(static_cast<std::underlying_type<Days>::type>(activity->days()) - 1);
}

EditActivity::~EditActivity()
{
    delete ui;
}

void EditActivity::on_editActivity_btn_clicked()
{
    QString description = ui->ActivityDescriptionText->toPlainText();
    QString name = ui->activityNameText->text();
    Days day = static_cast<Days>(_dayIndex);
    QTime time = ui->activityTimeText->time();

    Activity* activity = new Activity(name,time,day,description,_color);
    activity->setId(this->_activity->id());

    Program program;
    QMessageBox messageBox(this);

    if(program.editActivity(activity)){

        this->destroy();
        emit activityEdit(activity);


    }else{

        messageBox.setText("You missed to Enter some data or maybe some problems in database call Mohamad Ravaei :D");
        messageBox.exec();
    }
}

void EditActivity::on_activityDayText_currentIndexChanged(int index)
{
    _dayIndex = index;
}

void EditActivity::on_set_color_btn_clicked()
{
    _color = "background-color: rgb(170, 255, 127);";
    ui->set_color_btn->setText("*");
    ui->set_color_btn_2->setText("");
    ui->set_color_btn_3->setText("");
    ui->set_color_btn_4->setText("");
}

void EditActivity::on_set_color_btn_2_clicked()
{
    _color = "background-color: rgb(170, 255, 255);";
    ui->set_color_btn->setText("");
    ui->set_color_btn_2->setText("*");
    ui->set_color_btn_3->setText("");
    ui->set_color_btn_4->setText("");
}

void EditActivity::on_set_color_btn_3_clicked()
{
    _color = "background-color: rgb(255, 170, 0);";
    ui->set_color_btn->setText("");
    ui->set_color_btn_2->setText("");
    ui->set_color_btn_3->setText("*");
    ui->set_color_btn_4->setText("");
}

void EditActivity::on_set_color_btn_4_clicked()
{
    _color = "background-color: rgb(255, 104, 93);";
    ui->set_color_btn->setText("");
    ui->set_color_btn_2->setText("");
    ui->set_color_btn_3->setText("");
    ui->set_color_btn_4->setText("*");
}

void EditActivity::on_pushButton_clicked()
{
    this->destroy();
}
