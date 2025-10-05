#include "task_handler.h"
#include "ui_task_handler.h"

TaskHandler::TaskHandler(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TaskHandler)
{
    ui->setupUi(this);
    settings = new QSettings(QSettings::IniFormat,QSettings::UserScope,"MyOrg","TaskOrganizer");

}

TaskHandler::~TaskHandler()
{
    delete ui;
    delete settings;
}

void TaskHandler::load_tasks(QTableWidget *table)
{
    settings->beginGroup("Tasks");
    int rows = settings->value("rowCount", 0).toInt();

    table->setRowCount(0);
    for (int i = 0; i < rows; ++i) {
        table->insertRow(i);

        QString name = settings->value(QString("task%1/name").arg(i)).toString();
        QString date = settings->value(QString("task%1/date").arg(i)).toString();
        bool done = settings->value(QString("task%1/done").arg(i)).toBool();

        table->setItem(i, 0, new QTableWidgetItem(name));
        table->setItem(i, 1, new QTableWidgetItem(date));

        QTableWidgetItem *doneItem = new QTableWidgetItem();
        doneItem->setCheckState(done ? Qt::Checked : Qt::Unchecked);
        table->setItem(i, 2, doneItem);
    }
    settings->endGroup();

}

void TaskHandler::save_current_table(QTableWidget *table)
{
    if (!table) {
        return;
    }

    settings->beginGroup("Tasks");
    settings->remove("");  // clear old data

    settings->setValue("rowCount", table->rowCount());
    for (int i = 0; i < table->rowCount(); ++i) {
        settings->setValue(QString("task%1/name").arg(i), table->item(i, 0)->text());
        settings->setValue(QString("task%1/date").arg(i), table->item(i, 1)->text());
        settings->setValue(QString("task%1/done").arg(i),
                           table->item(i, 2)->checkState() == Qt::Checked);
    }
    settings->endGroup();

    settings->sync();
}
