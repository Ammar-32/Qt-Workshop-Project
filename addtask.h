#ifndef ADDTASK_H
#define ADDTASK_H

#include <QDialog>
#include <Qdate>


namespace Ui {
class AddTask;
}

class AddTask : public QDialog
{
    Q_OBJECT

public:
    explicit AddTask(QWidget *parent = nullptr);
    ~AddTask();

    QString getText() const;
    QDate getDate() const;

private slots:
    void on_buttonBox_accepted();





private:
    Ui::AddTask *ui;
    QString text;
    QDate date;
};

#endif // ADDTASK_H
