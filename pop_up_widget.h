#ifndef POP_UP_WIDGET_H
#define POP_UP_WIDGET_H

#include <QWidget>

namespace Ui {
class pop_up_widget;
}

class pop_up_widget : public QWidget
{
    Q_OBJECT

public:
    explicit pop_up_widget(QWidget *parent = nullptr);
    ~pop_up_widget();

private:
    Ui::pop_up_widget *ui;
};

#endif // POP_UP_WIDGET_H
