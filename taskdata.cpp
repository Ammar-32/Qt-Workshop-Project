#include "taskdata.h"

// Implement the constructor
TaskData::TaskData(const QString &name, const QDate &date, bool complete)
    : m_name(name), m_dueDate(date), m_isComplete(complete)
{
    // Optional: Validation can happen here
}

// Implement the setters
void TaskData::setName(const QString &name) {
    // Optional: Validation (e.g., check for empty name)
    m_name = name;
}

void TaskData::setDueDate(const QDate &date) {
    // Ensure the date is valid before setting
    if (date.isValid()) {
        m_dueDate = date;
    }
}

void TaskData::setComplete(bool complete) {
    m_isComplete = complete;
}

