#include "Edit_task_widget.h"
#include "ui_Edit_task_widget.h"
#include "QPushButton"



Edit_task_widget::Edit_task_widget(const QString &taskName, const QDate &dueDate,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Edit_task_widget)
{
    ui->setupUi(this);
    ui->task_name->setText(taskName);
    ui->due_date->setDate(dueDate);
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(false);

    connect(ui->task_name, &QLineEdit::textChanged,
            this, [okButton](const QString &text) {

                // Logic: Enable the button if the trimmed text is NOT empty
                bool isNotEmpty = !text.trimmed().isEmpty();
                okButton->setEnabled(isNotEmpty);
            });
    connect(ui->due_date,&QDateEdit::dateChanged,this,[okButton]() {


        okButton->setEnabled(true);
    });
}

Edit_task_widget::~Edit_task_widget()
{
    delete ui;
}

void Edit_task_widget::on_buttonBox_accepted()
{

    text= ui->task_name->text();
    date= ui->due_date->date();

}

QString Edit_task_widget::getText() const
{
    return text;
}

QDate Edit_task_widget::getDate() const
{
    return date;
}

