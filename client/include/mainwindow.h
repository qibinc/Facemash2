//
// Created by 陈齐斌 on 20/05/2017.
//

#ifndef CLIENT_MAINWINDOW_H
#define CLIENT_MAINWINDOW_H

#include <QtWidgets>
#include "ScreenUnit.h"
#include "photogroup.h"

namespace client
{

class MainWindow : public QMainWindow
{
Q_OBJECT

private:
//	Constants
	const QRect WindowGeometry = QRect(60 * SCREEN_UNIT, 40 * SCREEN_UNIT, 360 * SCREEN_UNIT, 240 * SCREEN_UNIT);
	enum
	{
		/**
 		* We will set them as variables later
 		*/
		NumAlbums = 3,
		NumPhotoGroups = 1
	};

//	Components
	QWidget *centralWidget;

	QGroupBox *albumGroupBox;
	QPushButton *albumButtons[NumAlbums];

	QGroupBox *photoGroupBox;
	PhotoGroup **photoGroups;
//	Create
	void CreateAlbumGroupBox();
	void CreatePhotoGroupBox();

public:
	explicit MainWindow(QWidget *parent = nullptr);

	virtual ~MainWindow();

};
}
#endif //CLIENT_WIDGET_H
