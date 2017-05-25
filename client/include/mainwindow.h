//
// Created by Qibin Chen on 20/05/2017.
//

#ifndef FACEMASH2_MAINWINDOW_H
#define FACEMASH2_MAINWINDOW_H

#include <QtWidgets>
#include <libs/photostream/include/wechatstream.h>

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

	QScrollArea *userArea;

	QScrollArea *photoArea;
	QGroupBox *photoSetsBox;
	PhotoSetsController *photoSetsController;

	QThread *photostream;
	QObject *streamdisplay;
	QTimer *streamtimer;
	bool streamOn;
//	Initialize
	void InitMainScene();

//	Refresh
	void RefreshUsers();

public slots:
	void RefreshPhotos();
	void SwitchPhotoStream();

public:
	explicit MainWindow(QWidget *parent = nullptr);

	virtual ~MainWindow();

};
}
#endif //FACEMASH2_WIDGET_H
