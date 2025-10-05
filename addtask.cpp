#include "addtask.h"
#include "ui_addtask.h"
#include "QPushButton"



AddTask::AddTask(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddTask)
{
    ui->setupUi(this);
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(false);

    connect(ui->task_name, &QLineEdit::textChanged,
            this, [okButton](const QString &text) {

                // Logic: Enable the button if the trimmed text is NOT empty
                bool isNotEmpty = !text.trimmed().isEmpty();
                okButton->setEnabled(isNotEmpty);
            });
}

AddTask::~AddTask()
{
    delete ui;
}

void AddTask::on_buttonBox_accepted()
{

    text= ui->task_name->text();
    date= ui->due_date->date();

}

QString AddTask::getText() const
{
    return text;
}

QDate AddTask::getDate() const
{
    return date;
}

