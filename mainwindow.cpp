#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_task_dialog.h"
#include "QDateTime"
#include "QMessageBox"

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
    connect(ui->delete_button, &QPushButton::clicked, this, &MainWindow::deleteing_task);
    connect(ui->edit_button, &QPushButton::clicked, this, &MainWindow::edit_task);
    connect(ui->table_tasks,
            &QTableWidget::itemSelectionChanged,
            this,
            &MainWindow::on_task_selection_changed);
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

void MainWindow::deleteing_task()
{
    int row = ui->table_tasks->currentRow();
    if (row < 0) return; // nothing selected

    QString task_name = ui->table_tasks->item(row, 0)->text();

    auto reply = QMessageBox::question(
        this,
        "Delete Task",
        QString("Are you sure you want to delete the task \"%1\"?").arg(task_name),
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        ui->table_tasks->removeRow(row);
    }
}

void MainWindow::edit_task()
{
    int row = ui->table_tasks->currentRow();
    if (row < 0) return;

    // Get current values from the table
    QString currentName = ui->table_tasks->item(row, 0)->text();
    QString currentDateStr = ui->table_tasks->item(row, 1)->text();
    QDate currentDate = QDate::fromString(currentDateStr, "dd/MM/yyyy");

    // Open dialog pre-filled
    auto dialog = std::make_unique<AddTaskDialog>(this);
    dialog->set_task_name(currentName);
    dialog->set_due_date(currentDate);

    if (dialog->exec() == QDialog::Accepted) {
        // Update the row with new values
        ui->table_tasks->item(row, 0)->setText(dialog->task_name());
        ui->table_tasks->item(row, 1)->setText(dialog->due_date().toString("dd/MM/yyyy"));
    }
}


void MainWindow::on_task_selection_changed()
{
    bool is_selected = !ui->table_tasks->selectedItems().isEmpty();

    ui->edit_button->setEnabled(is_selected);
    ui->delete_button->setEnabled(is_selected);
}
