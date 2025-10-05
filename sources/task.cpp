#include "task.h"

Task::Task(const QString &name, const QDate &dueDate, bool done)
    : name(name)
    , date(dueDate)
    , is_done(done){};


QString Task::get_name() const
{
    return name;
}

void Task::set_name(const QString &new_name)
{
    name = new_name;
}

QDate Task::get_date() const
{
    return date;
}

void Task::set_date(const QDate &new_date)
{
    date = new_date;
}

bool Task::get_is_done() const
{
    return is_done;
}

void Task::set_is_done(bool new_done_status)
{
    is_done = new_done_status;
}
