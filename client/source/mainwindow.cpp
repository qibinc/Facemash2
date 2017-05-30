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
	clientNetwork->deleteLater();
	photostream->terminate();
	delete centralWidget;
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
//	QThread *networkThread = new QThread(this);networkThread->start();
//	clientNetwork->moveToThread(networkThread);
	connect(this, SIGNAL(windowLoaded()), clientNetwork, SLOT(SetupConnection()));
	connect(clientNetwork, SIGNAL(connected()), this, SLOT(EnableLogIn()));
	connect(clientNetwork, SIGNAL(PhotosSaved(QStringList)), this, SLOT(RefreshPhotos()));

	photoSetsController = new PhotoSetsController(clientNetwork, this);
//	QThread *photoControllerThread = new QThread(this);photoControllerThread->start();
//	photoSetsController->moveToThread(photoControllerThread);
	connect(this, SIGNAL(refreshRequest()), photoSetsController, SLOT(StartRefresh()));
	connect(photoSetsController, SIGNAL(RefreshComplete(QGroupBox*)), this, SLOT(RefreshComplete(QGroupBox*)));

	photostream = new photostream::WechatStream(this);
	streamdisplay = new photostream::StreamDisplay(clientNetwork, "wechat_photo_stream_temp/", this);
	streamtimer = new QTimer;
	streamtimer->setInterval(100);
	connect(streamtimer, SIGNAL(timeout()), streamdisplay, SLOT(Refresh()));

	InitButtons();
	InitShortCuts();

	char hostip[100];
	std::cin >> hostip;
	if (strlen(hostip) > 4)
		clientNetwork->SetIP(hostip);
	emit windowLoaded();
}

void MainWindow::InitButtons()
{
	QGroupBox *box = new QGroupBox(tr("Control Area"));
	QVBoxLayout *layout = new QVBoxLayout;

	loginPhotoButton = new QPushButton("Log in", this);
	connect(loginPhotoButton, SIGNAL(clicked()), this, SLOT(LogIn()));
	layout->addWidget(loginPhotoButton, 0, Qt::AlignTop);
	loginPhotoButton->setDisabled(true);

	streamButton = new QPushButton("Wechat", this);
	connect(streamButton, SIGNAL(clicked()), this, SLOT(TurnOnPhotoStream()));
	layout->addWidget(streamButton, 0, Qt::AlignTop);
	streamButton->setDisabled(true);

	addPhotoButton = new QPushButton("Add Photo", this);
	connect(addPhotoButton, SIGNAL(clicked()), photoSetsController, SLOT(NewPhoto()));
	layout->addWidget(addPhotoButton, 0, Qt::AlignTop);
	addPhotoButton->setDisabled(true);

	manualRefreshButton = new QPushButton("Refresh", this);
	connect(manualRefreshButton, SIGNAL(clicked()), this, SLOT(RefreshPhotos()));
	layout->addWidget(manualRefreshButton, 0, Qt::AlignTop);
	manualRefreshButton->setDisabled(true);

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
	emit refreshRequest();
}

void MainWindow::TurnOnPhotoStream()
{
	std::cout << "Wechat Photo Stream ON" << std::endl;
	streamButton->setDisabled(true);
	streamtimer->start();
	photostream->start();
}

void MainWindow::LogIn()
{
	clientNetwork->LogIn("facemash2_test");
	loginPhotoButton->setDisabled(true);
	streamButton->setDisabled(false);
	addPhotoButton->setDisabled(false);
	manualRefreshButton->setDisabled(false);
}

void MainWindow::RefreshComplete(QGroupBox *newPhotoSetsBox)
{
	if (photoSetsBox != nullptr)
		delete photoSetsBox;

	photoSetsBox = newPhotoSetsBox;

	photoArea->setWidget(photoSetsBox);
	photoArea->verticalScrollBar()->setValue(photoArea->verticalScrollBar()->maximum());
}

void MainWindow::EnableLogIn()
{
	loginPhotoButton->setDisabled(false);
}

}
