#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "task_handler.h"

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

private:
    Ui::MainWindow *ui;

    TaskHandler *task_h_ptr;

private slots:
    void adding_task();

    void deleteing_task();

    void edit_task();

    void on_task_selection_changed();

signals:
    void table_updated(QTableWidget *table);
};
#endif // MAINWINDOW_H
