//
// Created by Qibin Chen on 20/05/2017.
//

#include "mainwindow.h"
#include "widgetsize.h"

#include "photosetscontroller.h"
#include "wechatstream.h"
#include "streamdisplay.h"
#include "myclient.h"

#include <iostream>

namespace client
{

MainWindow::MainWindow(QWidget *parent)
		: QMainWindow(parent), centralWidget(new QWidget()), mainLayout(nullptr)
{
	setWindowTitle(tr("Facemash2"));
	setGeometry(WINDOW_GEOMETRY);
	setCentralWidget(centralWidget);
//	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	InitMainScene();
	InitMainControl();

	RefreshPhotos();
}

MainWindow::~MainWindow()
{
	clientNetwork->LogOut();
	delete centralWidget;
	delete clientNetwork;
}

void MainWindow::InitMainScene()
{
	mainLayout = new QHBoxLayout;

	photoArea = new QScrollArea;
	photoArea->setWidgetResizable(true);

	controlArea = new QScrollArea;
	controlArea->setWidgetResizable(true);

	photoSetsBox = nullptr;

	mainLayout->addWidget(controlArea);
	mainLayout->addWidget(photoArea);

	mainLayout->setStretch(0, 1);
	mainLayout->setStretch(1, 8);

	centralWidget->setLayout(mainLayout);

}

void MainWindow::InitMainControl()
{
	clientNetwork = new clientnetwork::MyClient;
	clientNetwork->moveToThread(new QThread(this));
	connect(clientNetwork, SIGNAL(PhotosSaved(QList<QString>*)), this, SLOT(RefreshPhotos()));
	photoSetsController = new PhotoSetsController(clientNetwork, this);
	connect(this, SIGNAL(RefreshRequired()), photoSetsController, SLOT(StartRefresh()));
	connect(photoSetsController, SIGNAL(RefreshComplete(QGroupBox*)), this, SLOT(RefreshComplete(QGroupBox*)));
	photostream = new photostream::WechatStream(this);
	streamdisplay = new photostream::StreamDisplay(clientNetwork, "wechat_photo_stream_temp/", this);
	streamtimer = new QTimer;
	streamtimer->setInterval(100);
	connect(streamtimer, SIGNAL(timeout()), streamdisplay, SLOT(Refresh()));

	InitButtons();
	InitShortCuts();
}

void MainWindow::InitButtons()
{
	QGroupBox *box = new QGroupBox(tr("Control Area"));
	QVBoxLayout *layout = new QVBoxLayout;

	QPushButton *loginPhotoButton = new QPushButton("Log in", this);
	connect(loginPhotoButton, SIGNAL(clicked()), this, SLOT(LogIn()));
	layout->addWidget(loginPhotoButton, 0, Qt::AlignTop);

	addPhotoButton = new QPushButton("Add Photo", this);
	connect(addPhotoButton, SIGNAL(clicked()), photoSetsController, SLOT(NewPhoto()));
	layout->addWidget(addPhotoButton, 0, Qt::AlignTop);
	addPhotoButton->setDisabled(true);

	manualRefreshButton = new QPushButton("Refresh", this);
	connect(manualRefreshButton, SIGNAL(clicked()), this, SLOT(RefreshPhotos()));
	layout->addWidget(manualRefreshButton, 0, Qt::AlignTop);
	manualRefreshButton->setDisabled(true);

	enablePhotoStreamButton = new QPushButton("Stream", this);
	connect(enablePhotoStreamButton, SIGNAL(clicked()), this, SLOT(SwitchPhotoStream()));
	layout->addWidget(enablePhotoStreamButton, 0, Qt::AlignTop);
	enablePhotoStreamButton->setDisabled(true);

	box->setLayout(layout);
	controlArea->setWidget(box);
}

void MainWindow::InitShortCuts()
{
	QShortcut *copyShortCut = new QShortcut(QKeySequence::Copy, this);
	connect(copyShortCut, SIGNAL(activated()), photoSetsController, SLOT(CopyPhotoFile()));

	QShortcut *delShortCut = new QShortcut(QKeySequence::Delete, this);
	connect(delShortCut, SIGNAL(activated()), photoSetsController, SLOT(DeletePhotoFile()));
}

void MainWindow::RefreshPhotos()
{
	emit RefreshRequired();
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

void MainWindow::LogIn()
{
	clientNetwork->LogIn("facemash2_test");
	addPhotoButton->setDisabled(false);
	manualRefreshButton->setDisabled(false);
	enablePhotoStreamButton->setDisabled(false);
}

void MainWindow::RefreshComplete(QGroupBox *newPhotoSetsBox)
{
	if (photoSetsBox != nullptr)
		delete photoSetsBox;

	photoSetsBox = newPhotoSetsBox;

	photoArea->setWidget(photoSetsBox);
	photoArea->verticalScrollBar()->setValue(photoArea->verticalScrollBar()->maximum());
}

}
