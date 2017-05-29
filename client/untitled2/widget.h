#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "libs/clientnetwork/include/myclient.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    MyClient *myclient;
};

#endif // WIDGET_H
