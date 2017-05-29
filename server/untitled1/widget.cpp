#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myserver = new MyServer(this);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), myserver, SLOT(SendMessage()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), myserver, SLOT(SendPoints()));
}

Widget::~Widget()
{
    delete ui;
}




