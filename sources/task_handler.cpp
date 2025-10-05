#include "task_handler.h"
#include "ui_task_handler.h"
#include <QDebug>

TaskHandler::TaskHandler(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TaskHandler)
{
    ui->setupUi(this);
    settings = new QSettings(QSettings::IniFormat,QSettings::UserScope,"MyOrg","TaskOrganizer");
    load_tasks();

}

TaskHandler::~TaskHandler()
{
    save_tasks();
    delete ui;
    delete settings;
}

void TaskHandler::add_task(Task task)
{
    tasks_list.append(task);
}

void TaskHandler::delete_task(int index)
{
    if (index >= 0 && index < tasks_list.size())
    {
        tasks_list.removeAt(index);
    }
}

void TaskHandler::edit_task(int index, const Task &task)
{
    if (index >= 0 && index < tasks_list.size())
    {
        tasks_list[index] = task;
    }
}

void TaskHandler::load_tasks()
{
    int size = settings->beginReadArray("Tasks");
    tasks_list.clear();

    for (int i = 0; i < size; ++i) {
        settings->setArrayIndex(i);
        QString name = settings->value("Name").toString();
        QDate dueDate = QDate::fromString(settings->value("DueDate").toString(), Qt::ISODate);
        bool done = settings->value("Done").toBool();

        tasks_list.push_back(Task(name, dueDate, done));
    }

    settings->endArray();

}

void TaskHandler::save_tasks()
{
    settings->beginWriteArray("Tasks");
    for (int i = 0; i < tasks_list.size(); ++i) {
        settings->setArrayIndex(i);
        const Task &task = tasks_list[i];
        settings->setValue("Name", task.get_name());
        settings->setValue("DueDate", task.get_date().toString(Qt::ISODate));
        settings->setValue("Done", task.get_is_done());
    }
    settings->endArray();
    settings->sync();

}

const QVector<Task> &TaskHandler::get_tasks() const
{
    return tasks_list;
}
