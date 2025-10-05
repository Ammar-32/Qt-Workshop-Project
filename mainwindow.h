#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include "taskmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addTask();
    void deleteTask();
    void editTask();
    void onTasksChanged();
    void onCellChanged(int row, int column);

private:
    Ui::MainWindow *ui;
    TaskManager *m_taskManager;
    QTableWidget *m_taskTable;
    QPushButton *m_addButton;
    QPushButton *m_deleteButton;
    QPushButton *m_editButton;
    
    void setupUI();
    void updateTaskTable();
    void setupTableWidget();
};
#endif // MAINWINDOW_H
