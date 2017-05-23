//
// Created by 陈齐斌 on 21/05/2017.
//

#include "photolabel.h"
#include "widgetsize.h"

namespace uiutility
{
PhotoLabel::PhotoLabel(int photoID, QWidget *parent, Qt::WindowFlags f)
		: photoID(photoID), ClickableLabel(parent, f)
{
	setStyleSheet(tr("border: %1px outset transparent").arg(SCREEN_UNIT * 1.5));
}

void PhotoLabel::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
		emit rightClicked(photoID);
	else
		emit clicked(photoID);
}

void PhotoLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
	emit doubleClicked(photoID);
}

}