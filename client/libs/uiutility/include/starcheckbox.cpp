//
// Created by Qibin Chen on 29/05/2017.
//

#include "starcheckbox.h"

namespace uiutility
{
StarCheckBox::StarCheckBox(int ID, QWidget *parent) : QCheckBox(parent), ID(ID)
{
	connect(this, SIGNAL(clicked()), this, SLOT(StateChanged()));
}

void StarCheckBox::StateChanged()
{
	emit stateChanged(ID, CLICK);
}

void StarCheckBox::enterEvent(QEvent *event)
{
	emit stateChanged(ID, HOVER);
}

void StarCheckBox::leaveEvent(QEvent *event)
{
	emit stateChanged(ID, LEAVE);
}

}