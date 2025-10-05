#include "addtaskdialog.h"
#include <QDate>

AddTaskDialog::AddTaskDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    
    // Set default due date to today
    m_dueDateEdit->setDate(QDate::currentDate());
    
    // Connect signals
    connect(m_taskNameEdit, &QLineEdit::textChanged, this, &AddTaskDialog::validateInput);
    connect(m_okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    
    // Initial validation
    validateInput();
}

void AddTaskDialog::setupUI()
{
    setWindowTitle("Add Task");
    setModal(true);
    resize(300, 150);
    
    // Create widgets
    m_taskNameEdit = new QLineEdit(this);
    m_dueDateEdit = new QDateEdit(this);
    m_okButton = new QPushButton("OK", this);
    m_cancelButton = new QPushButton("Cancel", this);
    
    // Configure date edit
    m_dueDateEdit->setCalendarPopup(true);
    m_dueDateEdit->setMinimumDate(QDate::currentDate());
    
    // Create layouts
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Task Name:", m_taskNameEdit);
    formLayout->addRow("Due Date:", m_dueDateEdit);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
}

void AddTaskDialog::validateInput()
{
    bool isValid = !m_taskNameEdit->text().trimmed().isEmpty();
    m_okButton->setEnabled(isValid);
}

Task AddTaskDialog::getTask() const
{
    return Task(m_taskNameEdit->text().trimmed(), m_dueDateEdit->date());
}

void AddTaskDialog::setTask(const Task& task)
{
    m_taskNameEdit->setText(task.name);
    m_dueDateEdit->setDate(task.dueDate);
    setWindowTitle("Edit Task");
}
