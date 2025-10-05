#include "pop_up_widget.h"
#include "ui_pop_up_widget.h"

pop_up_widget::pop_up_widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pop_up_widget)
{
    ui->setupUi(this);
}

pop_up_widget::~pop_up_widget()
{
    delete ui;
}
