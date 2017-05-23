//
// Created by 陈齐斌 on 22/05/2017.
//

#include "photowindow.h"
#include <iostream>

namespace uiutility
{

PhotoWindow::PhotoWindow(const QString &fileName, QWidget *parent)
		: QMainWindow(parent, Qt::Window | Qt::FramelessWindowHint), photoPixmap(QPixmap(fileName))
{
	setWindowTitle(fileName);
	centralLabel = new QLabel;
	centralLabel->setScaledContents(true);
	centralLabel->setPixmap(photoPixmap);
	centralLabel->resize(photoPixmap.size());
	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	setCentralWidget(centralLabel);
	setFixedSize(centralLabel->size());
	move(QCursor::pos().x() - size().width() / 2, QCursor::pos().y() - size().height() / 2);

	QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity", this);
	animation->setDuration(500);
	animation->setStartValue(0);
	animation->setEndValue(1);
	animation->start();
}

PhotoWindow::~PhotoWindow()
{
	delete centralLabel;
}

void PhotoWindow::mousePressEvent(QMouseEvent *event)
{
	mouseStartLocation = event->globalPos();
	windowStartLocation = this->pos();
}

void PhotoWindow::mouseMoveEvent(QMouseEvent *event)
{
	this->move(event->globalPos() - mouseStartLocation + windowStartLocation);
}

void PhotoWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
	QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity", this);
	animation->setDuration(500);
	animation->setStartValue(windowOpacity());
	animation->setEndValue(0);
	animation->start();
	connect(animation, SIGNAL(finished()), this, SLOT(close()));
}

void PhotoWindow::wheelEvent(QWheelEvent *event)
{
	if (event->orientation() == Qt::Vertical)
	{
		centralLabel->resize((1 + (event->delta() / 5000.0)) * centralLabel->size());
		setFixedSize(centralLabel->size());
	}
}

void PhotoWindow::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
		case Qt::Key_Equal:
			centralLabel->resize(1.1 * centralLabel->size());
			setFixedSize(centralLabel->size());
			break;
		case Qt::Key_Minus:
			centralLabel->resize(0.9 * centralLabel->size());
			setFixedSize(centralLabel->size());
			break;
		case Qt::Key_0:
			centralLabel->resize(photoPixmap.size());
			setFixedSize(centralLabel->size());
			break;
		default:
			break;
	}

}

void PhotoWindow::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Space)
	{
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity", this);
		animation->setDuration(500);
		animation->setStartValue(windowOpacity());
		animation->setEndValue(0);
		animation->start();
		connect(animation, SIGNAL(finished()), this, SLOT(close()));
	}
}


}