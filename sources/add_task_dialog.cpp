#include "add_task_dialog.h"
#include "ui_add_task_dialog.h"
#include "QMessageBox"

AddTaskDialog::AddTaskDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddTaskDialog)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &AddTaskDialog::validate);

    connect(ui->buttonBox, &QDialogButtonBox::rejected,
            this, &AddTaskDialog::reject);
}

AddTaskDialog::~AddTaskDialog()
{
    delete ui;
}

QString AddTaskDialog::task_name() const
{
    return ui->task_name->toPlainText();
}

QDate AddTaskDialog::due_date() const
{
    return ui->dateEdit->date();
}

void AddTaskDialog::set_task_name(const QString &name)
{
    ui->task_name->setPlainText(name);
}

void AddTaskDialog::set_due_date(const QDate &date)
{
    ui->dateEdit->setDate(date);
}

void AddTaskDialog::validate()
{
    QString name = ui->task_name->toPlainText();
    QDate date = ui->dateEdit->date();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Task name cannot be empty.");
        return; // don’t close
    }

    if (date < QDate::currentDate()) {
        QMessageBox::warning(this, "Invalid Date", "Due date cannot be in the past.");
        return; // don’t close
    }

    // If valid, close the dialog and return Accepted
    this->accept();
}
