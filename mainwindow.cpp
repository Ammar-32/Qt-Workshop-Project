#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addtaskdialog.h"
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_taskManager(new TaskManager(this))
{
    ui->setupUi(this);
    setupUI();
    
    // Connect task manager signals
    connect(m_taskManager, &TaskManager::tasksChanged, this, &MainWindow::onTasksChanged);
    
    // Initial table update
    updateTaskTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    setWindowTitle("Task Manager Lite");
    resize(800, 600);
    
    // Create central widget and layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    // Create and setup table widget
    m_taskTable = new QTableWidget(this);
    setupTableWidget();
    mainLayout->addWidget(m_taskTable);
    
    // Create buttons layout
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    
    m_addButton = new QPushButton("Add Task", this);
    m_editButton = new QPushButton("Edit Task", this);
    m_deleteButton = new QPushButton("Delete Task", this);
    
    buttonLayout->addWidget(m_addButton);
    buttonLayout->addWidget(m_editButton);
    buttonLayout->addWidget(m_deleteButton);
    buttonLayout->addStretch();
    
    mainLayout->addLayout(buttonLayout);
    
    // Connect button signals
    connect(m_addButton, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(m_editButton, &QPushButton::clicked, this, &MainWindow::editTask);
    connect(m_deleteButton, &QPushButton::clicked, this, &MainWindow::deleteTask);
    
    // Connect table selection change
    connect(m_taskTable, &QTableWidget::itemSelectionChanged, [this]() {
        bool hasSelection = m_taskTable->currentRow() >= 0;
        m_editButton->setEnabled(hasSelection);
        m_deleteButton->setEnabled(hasSelection);
    });
    
    // Initial button states
    m_editButton->setEnabled(false);
    m_deleteButton->setEnabled(false);
}

void MainWindow::setupTableWidget()
{
    m_taskTable->setColumnCount(3);
    QStringList headers = {"Task", "Due Date", "Done"};
    m_taskTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths
    m_taskTable->horizontalHeader()->setStretchLastSection(false);
    m_taskTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_taskTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    m_taskTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    
    // Set selection behavior
    m_taskTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_taskTable->setSelectionMode(QAbstractItemView::SingleSelection);
    
    // Connect cell change signal
    connect(m_taskTable, &QTableWidget::cellChanged, this, &MainWindow::onCellChanged);
}

void MainWindow::addTask()
{
    AddTaskDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Task newTask = dialog.getTask();
        m_taskManager->addTask(newTask);
    }
}

void MainWindow::editTask()
{
    int currentRow = m_taskTable->currentRow();
    if (currentRow < 0) return;
    
    AddTaskDialog dialog(this);
    dialog.setTask(m_taskManager->getTask(currentRow));
    
    if (dialog.exec() == QDialog::Accepted) {
        Task updatedTask = dialog.getTask();
        m_taskManager->updateTask(currentRow, updatedTask);
    }
}

void MainWindow::deleteTask()
{
    int currentRow = m_taskTable->currentRow();
    if (currentRow < 0) return;
    
    const Task& task = m_taskManager->getTask(currentRow);
    
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Delete Task",
        QString("Are you sure you want to delete the task:\n\"%1\"?").arg(task.name),
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        m_taskManager->removeTask(currentRow);
    }
}

void MainWindow::onTasksChanged()
{
    updateTaskTable();
}

void MainWindow::updateTaskTable()
{
    const QList<Task>& tasks = m_taskManager->getTasks();
    
    // Temporarily disconnect to avoid triggering cellChanged during update
    disconnect(m_taskTable, &QTableWidget::cellChanged, this, &MainWindow::onCellChanged);
    
    m_taskTable->setRowCount(tasks.size());
    
    for (int i = 0; i < tasks.size(); ++i) {
        const Task& task = tasks[i];
        
        // Task name
        QTableWidgetItem *nameItem = new QTableWidgetItem(task.name);
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        m_taskTable->setItem(i, 0, nameItem);
        
        // Due date
        QTableWidgetItem *dateItem = new QTableWidgetItem(task.dueDateString());
        dateItem->setFlags(dateItem->flags() & ~Qt::ItemIsEditable);
        m_taskTable->setItem(i, 1, dateItem);
        
        // Done checkbox using QTableWidgetItem instead of QCheckBox widget
        QTableWidgetItem *doneItem = new QTableWidgetItem();
        doneItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        doneItem->setCheckState(task.isDone ? Qt::Checked : Qt::Unchecked);
        doneItem->setText(""); // No text, just checkbox
        m_taskTable->setItem(i, 2, doneItem);
    }
    
    // Reconnect the signal
    connect(m_taskTable, &QTableWidget::cellChanged, this, &MainWindow::onCellChanged);
}

void MainWindow::onCellChanged(int row, int column)
{
    // Handle checkbox changes in the "Done" column (column 2)
    if (column == 2 && row >= 0 && row < m_taskManager->taskCount()) {
        QTableWidgetItem *item = m_taskTable->item(row, column);
        if (item) {
            bool isChecked = (item->checkState() == Qt::Checked);
            
            // Get current task state
            const Task& currentTask = m_taskManager->getTask(row);
            
            // Only update if the state actually changed
            if (currentTask.isDone != isChecked) {
                // Temporarily disconnect to prevent recursion
                disconnect(m_taskManager, &TaskManager::tasksChanged, this, &MainWindow::onTasksChanged);
                
                // Update the task state
                m_taskManager->toggleTaskDone(row);
                
                // Reconnect the signal
                connect(m_taskManager, &TaskManager::tasksChanged, this, &MainWindow::onTasksChanged);
            }
        }
    }
}
