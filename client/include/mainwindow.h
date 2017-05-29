//
// Created by 陈齐斌 on 20/05/2017.
//

#ifndef CLIENT_MAINWINDOW_H
#define CLIENT_MAINWINDOW_H

#include <QtWidgets>
#include "widgetsize.h"
#include "photosetscontroller.h"

namespace client
{

class MainWindow : public QMainWindow
{
Q_OBJECT

private:

//	Components
	QWidget *centralWidget;
	QHBoxLayout *mainLayout;

	enum
	{ NumAlbums = 3 };
	QScrollArea *albumArea;
	QGroupBox *albumGroupBox;
//	AlbumController
	QPushButton *albumButtons[NumAlbums];

	QScrollArea *photoArea;
	QGroupBox *photoSetsBox;
	PhotoSetsController *photoSetsController;

//	Initialize
	void InitMainScene();

//	Refresh
	void RefreshAlbums();
	void RefreshPhotos();

public:
	explicit MainWindow(QWidget *parent = nullptr);

	virtual ~MainWindow();

};
}
#endif //CLIENT_WIDGET_H
