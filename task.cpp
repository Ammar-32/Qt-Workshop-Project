#include "task.h"
#include "ui_task.h"
#include<QDate>

task::task(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::task)
{
    ui->setupUi(this);
}

task::~task()
{
    delete ui;
}

void task::setDescription(const QString &text)
{
    ui->task_name->setText(text);
}

void task::setDueDate(const QDate &date)
{

    ui->task_date->setText(date.toString("yyyy-MM-dd"));
}

QString task::getDescription()
{
    return ui->task_name->text();
}

QDate task::getDueDate()
{
    QDate date = QDate::fromString(ui->task_date->text(), "yyyy-MM-dd");

    return date;
}
