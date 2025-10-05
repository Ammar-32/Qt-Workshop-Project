#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include<QDateEdit>
#include<QCheckBox>
#include <task.h>
#include <addtask.h>
#include <Edit_task_widget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateButtonsState()
{
    // Check if the list contains one or more items
    bool isNotEmpty = (ui->listWidget->count() > 0);

    // Get the buttons using their object names for a cleaner implementation
    QPushButton *deleteButton = ui->deleteButton;
    QPushButton *editButton = ui->editButton;

    // Apply the state
    if (deleteButton) {
        deleteButton->setEnabled(isNotEmpty);
    }
    if (editButton) {
        editButton->setEnabled(isNotEmpty);
    }
}
void MainWindow::addTaskItem(QString &taskname ,QDate &DueDate )
{
    // 1. Create a NEW instance of your TaskWidget for this specific row.
    // This is the key step to avoid overwriting the previous one.
    task *newTaskWidget = new task(this);
    newTaskWidget->setDescription(taskname);
    newTaskWidget->setDueDate(DueDate);

    QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);

    listItem->setSizeHint(newTaskWidget->sizeHint());

    // 4. Embed the TaskWidget instance into the list item container
    ui->listWidget->setItemWidget(listItem, newTaskWidget);
}

void MainWindow::on_addButton_clicked()
{
    AddTask *addtask= new AddTask(this);

    auto ret = addtask->exec();
    if (ret == QDialog::Accepted)
    {
        auto TaskName= addtask->getText();
        auto DueDate = addtask->getDate();
        addTaskItem(TaskName,DueDate);
    }
    updateButtonsState();
}


void MainWindow::on_deleteButton_clicked()
{
    ui->listWidget->takeItem(ui->listWidget->currentRow());
    updateButtonsState();
}


void MainWindow::on_editButton_clicked()
{
    // 2. Get the QListWidgetItem at the specified row
    QListWidgetItem *listItem = ui->listWidget->item(ui->listWidget->currentRow());

    // 3. Get the embedded custom widget (task*)
    // QListWidget::itemWidget() returns a QWidget*, so we must safely cast it back to our 'task' type.
    task *taskWidget = qobject_cast<task*>(ui->listWidget->itemWidget(listItem));
    auto text = taskWidget->getDescription();
    auto date = taskWidget->getDueDate();
    Edit_task_widget *Edit_task= new Edit_task_widget(text,date,this);

    auto ret = Edit_task->exec();
    if (ret == QDialog::Accepted)
    {


        auto text= Edit_task->getText();
        auto Date = Edit_task->getDate();
        taskWidget->setDescription(text);
        taskWidget->setDueDate(Date);
    }



}
