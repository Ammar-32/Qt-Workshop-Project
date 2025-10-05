#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void addTaskItem(QString &taskname ,QDate &DueDate );

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_editButton_clicked();

private:
    void updateButtonsState();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
