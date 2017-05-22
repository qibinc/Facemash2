//
// Created by 陈齐斌 on 21/05/2017.
//

#include "clickablelabel.h"

namespace uiutility
{

ClickableLabel::ClickableLabel(QWidget *parent, Qt::WindowFlags f)
		: QLabel(parent)
{

}

ClickableLabel::~ClickableLabel()
{}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
	emit clicked();
}

void ClickableLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
	emit doubleClicked();
}

}