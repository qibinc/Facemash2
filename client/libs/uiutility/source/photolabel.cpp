//
// Created by 陈齐斌 on 21/05/2017.
//

#include "photolabel.h"

uiutility::PhotoLabel::PhotoLabel(int photoID, QWidget* parent, Qt::WindowFlags f) : photoID(photoID), ClickableLabel(parent, f)
{

}

void uiutility::PhotoLabel::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
		emit rightClicked(photoID);
	else
		emit clicked(photoID);
}

void uiutility::PhotoLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
	emit doubleClicked(photoID);
}
