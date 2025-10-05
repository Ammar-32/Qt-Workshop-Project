#ifndef EDIT_TASK_WIDGET_H
#define EDIT_TASK_WIDGET_H

#include <QDialog>
#include <Qdate>


namespace Ui {
class Edit_task_widget;
}

class Edit_task_widget : public QDialog
{
    Q_OBJECT

public:
    explicit Edit_task_widget(const QString &taskName, const QDate &dueDate,QWidget *parent = nullptr);
    ~Edit_task_widget();
    QString Text;
    QDate Date;
    QString getText() const;
    QDate getDate() const;

private slots:
    void on_buttonBox_accepted();





private:
    Ui::Edit_task_widget *ui;
    QString text;
    QDate date;
};

#endif // EDIT_TASK_WIDGET_H
