#include "taskmanager.h"
#include "androidsound.h"
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

TaskManager::TaskManager(QObject *parent)
    : QObject(parent)
    , m_androidSound(nullptr)
{
    initializeFilePath();
    initializeAndroidSound();
    loadTasks();
}

void TaskManager::initializeFilePath()
{
#ifdef Q_OS_ANDROID
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#else
    QString dataPath = "C:/Users/ayankan";
#endif
    QDir dir;
    if (!dir.exists(dataPath)) {
        dir.mkpath(dataPath);
    }
    m_filePath = dataPath + "/tasks.ini";
}

void TaskManager::addTask(const Task& task)
{
    m_tasks.append(task);
    saveTasks();
    
    // Play sound when task is created (Android only)
    if (m_androidSound) {
        m_androidSound->playTaskCreatedSound();
    }
    
    emit tasksChanged();
}

void TaskManager::removeTask(int index)
{
    if (index >= 0 && index < m_tasks.size()) {
        m_tasks.removeAt(index);
        saveTasks();
        emit tasksChanged();
    }
}

void TaskManager::updateTask(int index, const Task& task)
{
    if (index >= 0 && index < m_tasks.size()) {
        m_tasks[index] = task;
        saveTasks();
        emit tasksChanged();
    }
}

void TaskManager::toggleTaskDone(int index)
{
    if (index >= 0 && index < m_tasks.size()) {
        m_tasks[index].isDone = !m_tasks[index].isDone;
        saveTasks();
        emit tasksChanged();
    }
}

bool TaskManager::loadTasks()
{
    QSettings settings(m_filePath, QSettings::IniFormat);
    
    int size = settings.beginReadArray("tasks");
    m_tasks.clear();
    
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        Task task;
        task.name = settings.value("name").toString();
        task.dueDate = settings.value("dueDate").toDate();
        task.isDone = settings.value("isDone").toBool();
        m_tasks.append(task);
    }
    
    settings.endArray();
    
    qDebug() << "Loaded" << m_tasks.size() << "tasks from" << m_filePath;
    return true;
}

bool TaskManager::saveTasks()
{
    QSettings settings(m_filePath, QSettings::IniFormat);
    
    settings.beginWriteArray("tasks");
    for (int i = 0; i < m_tasks.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("name", m_tasks[i].name);
        settings.setValue("dueDate", m_tasks[i].dueDate);
        settings.setValue("isDone", m_tasks[i].isDone);
    }
    settings.endArray();
    
    qDebug() << "Saved" << m_tasks.size() << "tasks to" << m_filePath;
    return true;
}

void TaskManager::initializeAndroidSound()
{
    // Only initialize Android sound on Android platform
    #ifdef Q_OS_ANDROID
    m_androidSound = new AndroidSound(this);
    qDebug() << "TaskManager: Android sound initialized";
    #else
    qDebug() << "TaskManager: Not on Android platform - sound disabled";
    #endif
}
