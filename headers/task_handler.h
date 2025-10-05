#ifndef TASK_HANDLER_H
#define TASK_HANDLER_H

#include <QDialog>
#include <QSettings>
#include <QTableWidget>
#include "task.h"
#include <QVector>

namespace Ui {
class TaskHandler;
}

class TaskHandler : public QDialog
{
    Q_OBJECT

public:
    explicit TaskHandler(QWidget *parent = nullptr);

    ~TaskHandler();

    void add_task(Task task);

    void delete_task(int index);

    void edit_task(int index, const Task &task);

    const QVector<Task> &get_tasks() const;

private:
    Ui::TaskHandler *ui;

    QSettings *settings;

    QVector<Task> tasks_list;

    void load_tasks();

    void save_tasks();

};

#endif // TASK_HANDLER_H
