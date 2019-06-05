#include "addactivity.h"
#include "ui_addactivity.h"
#include "Activity.h"
#include <QTime>
#include "program.h"
#include <qdebug.h>
#include <QMessageBox>
#include <QLabel>
#include <QColorDialog>

int dayIndex = 0;
QString color = NULL;

AddActivity::AddActivity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddActivity)
{
    ui->setupUi(this);
}

AddActivity::~AddActivity()
{
    this->close();
    this->destroy(false,false);
    delete ui;
}

void AddActivity::on_pushButton_clicked()
{
    this->destroy(false,false);
}


void AddActivity::on_addActivity_btn_clicked()
{
    QString description = ui->ActivityDescriptionText->toPlainText();
    QString name = ui->activityNameText->text();
    Days day = static_cast<Days>(dayIndex);
    QTime time = ui->activityTimeText->time();

    Program program;

    if(program.addActivity(new Activity(name,time,day,description,color)) == true){

        qDebug()<<"accepted";
        finished(Accepted);
        this->close();

    }else{
        qDebug()<<"rejected";
        QMessageBox messageBox(this);
        messageBox.setText("You missed to Enter some data");
        messageBox.exec();
    }

}

void AddActivity::on_activityDayText_currentIndexChanged(int index)
{
    dayIndex = index;
}

void AddActivity::on_set_color_btn_clicked()
{
    color = "background-color: rgb(170, 255, 127);";

    ui->set_color_btn->setText("*");
    ui->set_color_btn_2->setText("");
    ui->set_color_btn_3->setText("");
    ui->set_color_btn_4->setText("");
}

void AddActivity::on_set_color_btn_2_clicked()
{
    color = "background-color: rgb(170, 255, 255);";

    ui->set_color_btn->setText("");
    ui->set_color_btn_2->setText("*");
    ui->set_color_btn_3->setText("");
    ui->set_color_btn_4->setText("");
}

void AddActivity::on_set_color_btn_3_clicked()
{
    color = "background-color: rgb(255, 170, 0);";

    ui->set_color_btn->setText("");
    ui->set_color_btn_2->setText("");
    ui->set_color_btn_3->setText("*");
    ui->set_color_btn_4->setText("");
}

void AddActivity::on_set_color_btn_4_clicked()
{
    color = "background-color: rgb(255, 104, 93);";

    ui->set_color_btn->setText("");
    ui->set_color_btn_2->setText("");
    ui->set_color_btn_3->setText("");
    ui->set_color_btn_4->setText("*");
}
