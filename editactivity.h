#ifndef EDITACTIVITY_H
#define EDITACTIVITY_H

#include <QDialog>
#include "Activity.h"

namespace Ui {
class EditActivity;
}

class EditActivity : public QDialog
{
    Q_OBJECT

public:
    explicit EditActivity(QWidget *parent = nullptr, Activity *activity=0);
    ~EditActivity();

signals:
    void activityEdit(Activity *activity);

private slots:
    void on_editActivity_btn_clicked();

    void on_activityDayText_currentIndexChanged(int index);

    void on_set_color_btn_clicked();

    void on_set_color_btn_2_clicked();

    void on_set_color_btn_3_clicked();

    void on_set_color_btn_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::EditActivity *ui;
    Activity *_activity;
};

#endif // EDITACTIVITY_H
