#ifndef TASK_HANDLER_H
#define TASK_HANDLER_H

#include <QDialog>

namespace Ui {
class TaskHandler;
}

class TaskHandler : public QDialog
{
    Q_OBJECT

public:
    explicit TaskHandler(QWidget *parent = nullptr);
    ~TaskHandler();

private:
    Ui::TaskHandler *ui;

signals:
    void task_added();
};

#endif // TASK_HANDLER_H
