#ifndef ADD_TASK_DIALOG_H
#define ADD_TASK_DIALOG_H

#include <QDialog>

namespace Ui {
class AddTaskDialog;
}

class AddTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskDialog(QWidget *parent = nullptr);
    ~AddTaskDialog();

    QString task_name() const;

    QDate due_date() const;

private:
    Ui::AddTaskDialog *ui;

private slots:
    void validate();
};

#endif // ADD_TASK_DIALOG_H
