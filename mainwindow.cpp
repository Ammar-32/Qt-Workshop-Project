#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_task_dialog.h"
#include "QDateTime"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Task Manager");
    ui->edit_button->setEnabled(false);
    ui->delete_button->setEnabled(false);
    QStringList headers = {"Task", "Due Date", "Done"};
    ui->table_tasks->setHorizontalHeaderLabels(headers);
    ui->table_tasks->horizontalHeader()->setStretchLastSection(false);
    ui->table_tasks->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch); // Task Name
    ui->table_tasks->horizontalHeader()
        ->setSectionResizeMode(1, QHeaderView::ResizeToContents); // Due Date
    ui->table_tasks->horizontalHeader()
        ->setSectionResizeMode(2, QHeaderView::ResizeToContents); // Done checkbox
    connect(ui->add_button, &QPushButton::clicked, this, &MainWindow::adding_task);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::adding_task()
{
    std::unique_ptr<AddTaskDialog> ptr = std::make_unique<AddTaskDialog>();

    if (ptr->exec() == QDialog::Accepted) {
        auto current_row_count = ui->table_tasks->rowCount();
        ui->table_tasks->insertRow(current_row_count);

        // Task name
        ui->table_tasks->setItem(current_row_count, 0, new QTableWidgetItem(ptr->task_name()));

        // Due date
        ui->table_tasks->setItem(current_row_count, 1, new QTableWidgetItem(ptr->due_date().toString("dd/MM/yyyy")));

        // Done checkbox
        QTableWidgetItem *doneItem = new QTableWidgetItem();
        doneItem->setCheckState(Qt::Unchecked);
        ui->table_tasks->setItem(current_row_count, 2, doneItem);
    }
}
