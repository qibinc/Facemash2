#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myclient = new MyClient(this);
}

Widget::~Widget()
{
    delete ui;
}
