//
// Created by 陈齐斌 on 20/05/2017.
//

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
	ui->setupUi(this);
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(SlotPushButton()));
	m_icount = 0;
}

Widget::~Widget()
{

}

void Widget::SlotPushButton()
{
	++m_icount;
	ui->lineEdit->setText(QString::number(m_icount));
}
