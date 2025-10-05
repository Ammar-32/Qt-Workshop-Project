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
    task_h_ptr = new TaskHandler();
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
    ui->table_tasks->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->add_button, &QPushButton::clicked, this, &MainWindow::adding_task);
    connect(ui->delete_button, &QPushButton::clicked, this, &MainWindow::deleteing_task);
    connect(ui->edit_button, &QPushButton::clicked, this, &MainWindow::edit_task);
    connect(ui->table_tasks,
            &QTableWidget::itemSelectionChanged,
            this,
            &MainWindow::on_task_selection_changed);
    connect(ui->table_tasks, &QTableWidget::itemChanged,this, &MainWindow::on_table_item_changed);
    populate_table_from_model();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete task_h_ptr;
}

void MainWindow::populate_table_from_model()
{
    ui->table_tasks->setRowCount(0); // clear table

    const QVector<Task> &tasks = task_h_ptr->get_tasks();
    for (int i = 0; i < tasks.size(); ++i) {
        const Task &t = tasks[i];
        int row = ui->table_tasks->rowCount();
        ui->table_tasks->insertRow(row);

        ui->table_tasks->setItem(row, 0, new QTableWidgetItem(t.get_name()));
        ui->table_tasks->setItem(row, 1, new QTableWidgetItem(t.get_date().toString("dd/MM/yyyy")));
        QTableWidgetItem *doneItem = new QTableWidgetItem();
        doneItem->setCheckState(t.get_is_done() ? Qt::Checked : Qt::Unchecked);
        ui->table_tasks->setItem(row, 2, doneItem);
    }
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

        Task newTask(ptr->task_name(), ptr->due_date(), false);
        task_h_ptr->add_task(newTask);
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
        task_h_ptr->delete_task(row);
    }
}

void MainWindow::edit_task()
{
    int row = ui->table_tasks->currentRow();
    if (row < 0) return;

    const Task &old_task = task_h_ptr->get_tasks().at(row);

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
        Task updated(dialog->task_name(), dialog->due_date(), old_task.get_is_done());
        task_h_ptr->edit_task(row, updated);
    }
}


void MainWindow::on_task_selection_changed()
{
    bool is_selected = !ui->table_tasks->selectedItems().isEmpty();

    ui->edit_button->setEnabled(is_selected);
    ui->delete_button->setEnabled(is_selected);
}

void MainWindow::on_table_item_changed(QTableWidgetItem *item)
{
    int row = item->row();
    if (row < 0 || row >= task_h_ptr->get_tasks().size()) {
        return;
    }
    if (item->column() == 2) {
        bool done = (item->checkState() == Qt::Checked);
        const Task &old_task = task_h_ptr->get_tasks().at(row);
        Task updated(old_task.get_name(), old_task.get_date(), done);
        task_h_ptr->edit_task(row, updated);
    }
}
