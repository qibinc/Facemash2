//
// Created by Qibin Chen on 23/05/2017.
//

#include "photoeditmenu.h"

namespace uiutility
{

PhotoEditMenu::PhotoEditMenu(QWidget *parent) : QMenu(parent)
{
	createActions();
	addAction(copyAct);
	addAction(delAct);
}

void PhotoEditMenu::createActions()
{
	copyAct = new QAction(QObject::tr("&Copy"), this);
	copyAct->setShortcuts(QKeySequence::Copy);
	copyAct->setStatusTip(QObject::tr("Copy this photo"));
	connect(copyAct, SIGNAL(triggered()), parent(), SLOT(CopyPhotoFile()));

	delAct = new QAction(QObject::tr("&Delete"), this);
	delAct->setShortcuts(QKeySequence::Delete);
	delAct->setStatusTip(QObject::tr("Delete this photo"));
	connect(delAct, SIGNAL(triggered()), parent(), SLOT(DeletePhotoFile()));
}

}
