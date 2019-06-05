#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QObject>
#include <QTime>

enum Days
{
    Saturday=1,
    Sunday=2,
    Monday=3,
    Tuesday=4,
    Wednesday=5,
    Thursday=6,
    Friday=7
};

class Activity : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(float sort READ sort WRITE setSort NOTIFY sortChanged)
    Q_PROPERTY(QTime time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(Days days READ days WRITE setDays NOTIFY daysChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)

public:
    Activity();
    Activity(QString name,QTime time,Days day,QString description,QString color);
    Activity(QString name,QTime time,Days day,QString description,int id,QString color);

    QString name() const
    {
        return m_name;
    }
    float sort() const
    {
        return m_sort;
    }

    QTime time() const
    {
        return m_time;
    }

    Days days() const
    {
        return m_days;
    }

    QString description() const
    {
        return m_description;
    }

    int id() const
    {
        return m_id;
    }

    QString color() const
    {
        return m_color;
    }

public slots:
    void setName(QString name)
    {
        if (m_name == name)
            return;

        m_name = name;
        emit nameChanged(m_name);
    }

    void setSort(float sort)
    {
        if (qFuzzyCompare(m_sort, sort))
            return;

        m_sort = sort;
        emit sortChanged(m_sort);
    }

    void setTime(QTime time)
    {
        if (m_time == time)
            return;

        m_time = time;
        emit timeChanged(m_time);
    }

    void setDays(Days days)
    {
        if (m_days == days)
            return;

        m_days = days;
        emit daysChanged(m_days);
    }

    void setDescription(QString description)
    {
        if (m_description == description)
            return;

        m_description = description;
        emit descriptionChanged(m_description);
    }

    void setId(int id)
    {
        if (m_id == id)
            return;

        m_id = id;
        emit idChanged(m_id);
    }

    void setColor(QString color)
    {
        if (m_color == color)
            return;

        m_color = color;
        emit colorChanged(m_color);
    }

signals:
    void nameChanged(QString name);
    void sortChanged(float sort);
    void timeChanged(QTime time);
    void daysChanged(Days days);
    void descriptionChanged(QString description);

    void idChanged(int id);

    void colorChanged(QString color);

private:
    QString m_name;
    float m_sort;
    QTime m_time;
    Days m_days;
    QString m_description;
    int m_id;
    QString m_color;
};



#endif // ACTIVITY_H
