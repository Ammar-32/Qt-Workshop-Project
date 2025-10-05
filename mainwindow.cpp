#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include<QDateEdit>
#include<QCheckBox>
#include <task.h>
#include <addtask.h>
#include <Edit_task_widget.h>
#include <taskdata.h>
#include <QSettings>




QList<TaskData> tasklist;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings=new QSettings("tasklist.ini",QSettings::IniFormat);
    loadTasks();







}

MainWindow::~MainWindow()
{
    saveTasks();
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
    tasklist.append(TaskData(taskname,DueDate,false));
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
    tasklist.removeAt(ui->listWidget->currentRow());
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
        tasklist[ui->listWidget->currentRow()].m_name =Edit_task->getText();
        tasklist[ui->listWidget->currentRow()].m_dueDate =Edit_task->getDate();
        taskWidget->setDescription(text);
        taskWidget->setDueDate(Date);
    }



}

void MainWindow::saveTasks()
{
    // 1. Instantiate QSettings
    // Use QSettings::IniFormat for simple, readable files, or NativeFormat for OS-specific storage.
    // The arguments are: Company Name, Application Name


    // 2. Store the total count of tasks
    settings->setValue("taskCount", tasklist.size());

    // 3. Loop through each task and save its properties within a unique group
    for (int i = 0; i < tasklist.size(); ++i) {
        // Create a unique group name for the task based on its index
        QString groupName = QString("Task/%1").arg(i);

        settings->beginGroup(groupName);

        // Save the properties
        settings->setValue("name", tasklist[i].m_name);
        settings->setValue("dueDate", tasklist[i].m_dueDate); // QDate is stored directly
        settings->setValue("isComplete", tasklist[i].m_isComplete);

        settings->endGroup();
    }

    // Optional: Write immediately to disk
    settings->sync();


}

void MainWindow::loadTasks()
{
    // MUST be the first two actions:
    tasklist.clear();          // Clears the QVector<TaskData> data model
    ui->listWidget->clear();
    // 2. Instantiate QSettings


    // 3. Get the total number of tasks saved (default to 0 if not found)
    int count = settings->value("taskCount", 0).toInt();

    // 4. Loop to load each task
    for (int i = 0; i < count; ++i) {
        QString groupName = QString("Task/%1").arg(i);

        settings->beginGroup(groupName);

        // Retrieve the saved values
        QString name = settings->value("name").toString();
        // Retrieve the QDate. Use QDate() as default for safety.
        QDate dueDate = settings->value("dueDate").toDate();
        bool isComplete = settings->value("isComplete").toBool();

        settings->endGroup();


        // A. Add to the data model (TaskRecord)
        TaskData loadedTask(name, dueDate, isComplete);


        // B. Rebuild the UI item (call your existing function or integrate logic here)
        // Note: This call should accept 'isComplete' if you want the checkbox state to load.
        addTaskItem(name, dueDate);

        // NOTE: If your addTaskItem doesn't handle the isComplete state,
        // you must manually set the checkbox state on the resulting task widget here.

    }

    // 6. Update control buttons state
    updateButtonsState();


}
