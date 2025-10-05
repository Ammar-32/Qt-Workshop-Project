#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDate>

class Task
{
public:
    Task() = default;
    Task(const QString &name, const QDate &dueDate, bool done = false);

    QString get_name() const;

    void set_name(const QString &new_name);

    QDate get_date() const;

    void set_date(const QDate &new_date);

    bool get_is_done() const;

    void set_is_done(bool new_done_status);

private:
    QString name;

    QDate date;

    bool is_done = false;

};
#endif // TASK_H
