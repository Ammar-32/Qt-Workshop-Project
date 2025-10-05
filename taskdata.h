#ifndef TASKDATA_H
#define TASKDATA_H

#include <QString>
#include <QDate>

class TaskData
{
public:
    // Constructor to initialize the object
    TaskData(const QString &name, const QDate &date, bool complete = false);

    // --- Public Getters (Read-only access) ---
    QString getName() const { return m_name; }
    QDate getDueDate() const { return m_dueDate; }
    bool isComplete() const { return m_isComplete; }

    // --- Public Setters (Controlled modification) ---
    void setName(const QString &name);
    void setDueDate(const QDate &date);
    void setComplete(bool complete);
    QString m_name;
    QDate m_dueDate;
    bool m_isComplete;
private:
    // Private data members (Encapsulation)

};

#endif // TASKDATA_H
