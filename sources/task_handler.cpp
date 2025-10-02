#include "task_handler.h"
#include "ui_task_handler.h"

TaskHandler::TaskHandler(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TaskHandler)
{
    ui->setupUi(this);
}

TaskHandler::~TaskHandler()
{
    delete ui;
}
