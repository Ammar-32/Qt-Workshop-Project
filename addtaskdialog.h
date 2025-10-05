#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include "task.h"

class AddTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskDialog(QWidget *parent = nullptr);
    
    Task getTask() const;
    void setTask(const Task& task);

private slots:
    void validateInput();

private:
    QLineEdit *m_taskNameEdit;
    QDateEdit *m_dueDateEdit;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
    
    void setupUI();
};

#endif // ADDTASKDIALOG_H
