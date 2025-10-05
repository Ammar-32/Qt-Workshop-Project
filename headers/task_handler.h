#ifndef TASK_HANDLER_H
#define TASK_HANDLER_H

#include <QDialog>
#include <QSettings>
#include <QTableWidget>

namespace Ui {
class TaskHandler;
}

class TaskHandler : public QDialog
{
    Q_OBJECT

public:
    explicit TaskHandler(QWidget *parent = nullptr);
    ~TaskHandler();
    void load_tasks(QTableWidget *table);

private:
    Ui::TaskHandler *ui;

    QSettings *settings;

public slots:
    void save_current_table(QTableWidget *table);

};

#endif // TASK_HANDLER_H
