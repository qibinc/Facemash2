//
// Created by Qibin Chen on 23/05/2017.
//

#ifndef FACEMASH2_PHOTOMENU_H
#define FACEMASH2_PHOTOMENU_H

#include <QtWidgets>

namespace uiutility
{

class PhotoEditMenu : public QMenu
{
	QAction *copyAct, *delAct;

	void createActions();

public:
	PhotoEditMenu(QWidget *parent = nullptr);

};

}

#endif //FACEMASH2_PHOTOMENU_H
