//
// Created by Qibin Chen on 20/05/2017.
//

#include "mainwindow.h"
#include "photosetscontroller.h"

#include "widgetsize.h"
#include "wechatstream.h"
#include "streamdisplay.h"

#include <iostream>

namespace client
{

MainWindow::MainWindow(QWidget *parent)
		: QMainWindow(parent), centralWidget(new QWidget()),
          mainLayout(nullptr)
{
	setWindowTitle(tr("Facemash2"));
	setGeometry(WINDOW_GEOMETRY);
	setCentralWidget(centralWidget);
//	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	InitMainScene();
	RefreshUsers();
	RefreshPhotos();

}

MainWindow::~MainWindow()
{
	delete centralWidget;
}

void MainWindow::InitMainScene()
{
	mainLayout = new QHBoxLayout;

	photoArea = new QScrollArea;
	photoArea->setWidgetResizable(true);

	userArea = new QScrollArea;
	userArea->setWidgetResizable(true);

//	albumController = new AlbumController(this);
	photoSetsController = new PhotoSetsController(this);

	QShortcut *copyShortCut = new QShortcut(QKeySequence::Copy, this);
	connect(copyShortCut, SIGNAL(activated()), photoSetsController, SLOT(CopyPhotoFile()));

	QShortcut *delShortCut = new QShortcut(QKeySequence::Delete, this);
	connect(delShortCut, SIGNAL(activated()), photoSetsController, SLOT(DeletePhotoFile()));

	photoSetsBox = nullptr;

	mainLayout->addWidget(userArea);
	mainLayout->addWidget(photoArea);

	mainLayout->setStretch(0, 1);
	mainLayout->setStretch(1, 8);

	centralWidget->setLayout(mainLayout);

	streamdisplay = new photostream::StreamDisplay(QDate::currentDate().toString("yyyy.MM.dd") + "/", "wechat_photo_stream_temp/", this);

	streamtimer = new QTimer;
	streamtimer->setInterval(100);
	connect(streamtimer, SIGNAL(timeout()), streamdisplay, SLOT(Refresh()));
	photostream = new photostream::WechatStream(this);

}

void MainWindow::RefreshUsers()
{
	QGroupBox *box = new QGroupBox(tr("Temp Area"));

	QVBoxLayout *layout = new QVBoxLayout;

	QPushButton *enablePhotoStreamButton = new QPushButton("Stream", this);
	connect(enablePhotoStreamButton, SIGNAL(clicked()), this, SLOT(SwitchPhotoStream()));
	layout->addWidget(enablePhotoStreamButton, 0, Qt::AlignTop);

	QPushButton *manualRefreshButton = new QPushButton("Refresh", this);
	connect(manualRefreshButton, SIGNAL(clicked()), this, SLOT(RefreshPhotos()));
	layout->addWidget(manualRefreshButton, 0, Qt::AlignTop);

	box->setLayout(layout);

	userArea->setWidget(box);

}

void MainWindow::RefreshPhotos()
{
	if (photoSetsBox != nullptr)
		delete photoSetsBox;

	photoSetsBox = photoSetsController->CreatePhotoSetsBox();

	photoArea->setWidget(photoSetsBox);
	photoArea->verticalScrollBar()->setValue(photoArea->verticalScrollBar()->maximum());

}

void MainWindow::SwitchPhotoStream()
{
	if (!streamOn)
	{
		std::cout << "Wechat Photo Stream ON" << std::endl;
		streamOn = true;
		streamtimer->start();
		photostream->start();
	}
	else
	{
		std::cout << "Wechat Photo Stream OFF" << std::endl;
		streamOn = false;
		streamtimer->stop();
		photostream->terminate();
	}

}

}
