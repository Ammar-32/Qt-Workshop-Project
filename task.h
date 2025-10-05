#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDate>

struct Task {
    QString name;
    QDate dueDate;
    bool isDone;
    
    Task() : isDone(false) {}
    Task(const QString& taskName, const QDate& date, bool done = false)
        : name(taskName), dueDate(date), isDone(done) {}
    
    // Helper methods for display
    QString dueDateString() const {
        return dueDate.toString("yyyy-MM-dd");
    }
    
    QString statusString() const {
        return isDone ? "Yes" : "No";
    }
};

#endif // TASK_H
