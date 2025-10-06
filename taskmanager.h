#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include <QList>
#include <QString>
#include <QSettings>
#include "task.h"

// Forward declaration for Android sound functionality
class AndroidSound;

class TaskManager : public QObject
{
    Q_OBJECT

public:
    explicit TaskManager(QObject *parent = nullptr);
    
    // Task operations
    void addTask(const Task& task);
    void removeTask(int index);
    void updateTask(int index, const Task& task);
    void toggleTaskDone(int index);
    
    // Data access
    const QList<Task>& getTasks() const { return m_tasks; }
    int taskCount() const { return m_tasks.size(); }
    const Task& getTask(int index) const { return m_tasks.at(index); }
    
    // File operations
    bool loadTasks();
    bool saveTasks();

signals:
    void tasksChanged();

private:
    QList<Task> m_tasks;
    QString m_filePath;
    AndroidSound *m_androidSound;  // For playing sounds on Android
    
    void initializeFilePath();
    void initializeAndroidSound();
};

#endif // TASKMANAGER_H
