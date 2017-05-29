//
// Created by 陈齐斌 on 20/05/2017.
//

#include "mainwindow.h"
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
	RefreshAlbums();
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

	albumArea = new QScrollArea;
	albumArea->setWidgetResizable(true);

//	albumController = new AlbumController;
	photoSetsController = new PhotoSetsController;
	albumGroupBox = nullptr;
	photoSetsBox = nullptr;

	mainLayout->addWidget(albumArea);
	mainLayout->addWidget(photoArea);

	mainLayout->setStretch(0, 1);
	mainLayout->setStretch(1, 8);

	centralWidget->setLayout(mainLayout);
}

void MainWindow::RefreshAlbums()
{
	if (albumGroupBox != nullptr)
		delete albumGroupBox;

//	albumGroupBox = albumController->CreateAlbum

	albumGroupBox = new QGroupBox(tr("Albums"));
	QVBoxLayout *layout = new QVBoxLayout;
	for (int i = 0; i < NumAlbums; ++i)
	{
		albumButtons[i] = new QPushButton(tr("Album %1").arg(i + 1));
		layout->addWidget(albumButtons[i], 0, Qt::AlignTop);
	}
	albumGroupBox->setLayout(layout);

	albumArea->setWidget(albumGroupBox);

}

void MainWindow::RefreshPhotos()
{
	if (photoSetsBox != nullptr)
		delete photoSetsBox;

	photoSetsBox = photoSetsController->CreatePhotoSetsBox();

	photoArea->setWidget(photoSetsBox);
}


}
