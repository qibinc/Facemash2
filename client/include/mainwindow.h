//
// Created by 陈齐斌 on 20/05/2017.
//

#ifndef FACEMASH2_MAINWINDOW_H
#define FACEMASH2_MAINWINDOW_H

#include <QtWidgets>

namespace client
{

class PhotoSetsController;

class MainWindow : public QMainWindow
{
Q_OBJECT

private:

//	Components
	QWidget *centralWidget;
	QHBoxLayout *mainLayout;
	QMenu *menu;
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
#endif //FACEMASH2_WIDGET_H
