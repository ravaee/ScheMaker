#ifndef ADDACTIVITY_H
#define ADDACTIVITY_H

#include <QDialog>
#include <Activity.h>

namespace Ui {
class AddActivity;
}

class AddActivity : public QDialog
{
    Q_OBJECT

public:
    explicit AddActivity(QWidget *parent = nullptr);
    ~AddActivity();

private slots:
    void on_pushButton_clicked();
    void on_addActivity_btn_clicked();
    void on_activityDayText_currentIndexChanged(int index);
    void on_set_color_btn_clicked();

    void on_set_color_btn_2_clicked();

    void on_set_color_btn_3_clicked();

    void on_set_color_btn_4_clicked();

private:
    Ui::AddActivity *ui;

};

#endif // ADDACTIVITY_H
