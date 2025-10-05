#ifndef TASK_H
#define TASK_H

#include <QWidget>

namespace Ui {
class task;
}

class task : public QWidget
{
    Q_OBJECT

public:
    explicit task(QWidget *parent = nullptr);
    ~task();
    void setDescription(const QString& text);
    void setDueDate(const QDate& date);
    QString getDescription();
    QDate getDueDate();

private:
    Ui::task *ui;
};

#endif // TASK_H
