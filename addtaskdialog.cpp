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

    // Set a controlled dialog size
    setFixedSize(360, 200); // looks clean on Android emulator and small devices

    // Create widgets
    m_taskNameEdit = new QLineEdit(this);
    m_dueDateEdit = new QDateEdit(this);
    m_okButton = new QPushButton("OK", this);
    m_cancelButton = new QPushButton("Cancel", this);

    // Configure fixed sizes
    m_taskNameEdit->setFixedWidth(200);
    m_dueDateEdit->setFixedWidth(200);

    m_taskNameEdit->setMinimumHeight(40);
    m_dueDateEdit->setMinimumHeight(40);

    // Optional: make font a bit larger for touch screens
    QFont font = m_taskNameEdit->font();
    font.setPointSize(12);
    m_taskNameEdit->setFont(font);
    m_dueDateEdit->setFont(font);
    m_okButton->setFont(font);
    m_cancelButton->setFont(font);

    m_dueDateEdit->setCalendarPopup(true);
    m_dueDateEdit->setMinimumDate(QDate::currentDate());

    // Create layouts
    QFormLayout *formLayout = new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignRight);
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

void AddTaskDialog::setTask(const Task &task)
{
    m_taskNameEdit->setText(task.name);
    m_dueDateEdit->setDate(task.dueDate);
    setWindowTitle("Edit Task");
}
