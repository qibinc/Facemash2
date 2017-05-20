//
// Created by 陈齐斌 on 20/05/2017.
//

#include "mainwindow.h"

namespace client
{

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), centralWidget(new QWidget())
{
	setWindowTitle(tr("Facemash2"));
	setGeometry(WindowGeometry);
	setCentralWidget(centralWidget);
//	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	CreateAlbumGroupBox();
	CreatePhotoGroupBox();

	QHBoxLayout *mainLayout = new QHBoxLayout;

	mainLayout->addWidget(albumGroupBox);
	mainLayout->addWidget(photoGroupBox);
	mainLayout->setStretch(0, 1);
	mainLayout->setStretch(1, 8);

	centralWidget->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
	delete centralWidget;
}

void MainWindow::CreateAlbumGroupBox()
{
	albumGroupBox = new QGroupBox(tr("Albums"));
	QVBoxLayout *layout = new QVBoxLayout;
	for (int i = 0; i < NumAlbums; ++i)
	{
		albumButtons[i] = new QPushButton(tr("Album %1").arg(i + 1));
		layout->addWidget(albumButtons[i]);
	}
	albumGroupBox->setLayout(layout);
}

void MainWindow::CreatePhotoGroupBox()
{
	photoGroupBox = new QGroupBox(tr("Photos"));
	QVBoxLayout *layout = new QVBoxLayout;

	photoGroups = new PhotoGroup*[NumPhotoGroups];
	for (int i = 0; i < NumPhotoGroups; i++)
	{
		const QString photos[5] = {tr("image1.jpg"), tr("image2.jpg"), tr("image3.jpg"), tr("image4.jpg"), tr("image5.jpg")};

		photoGroups[i] = new PhotoGroup(5, photos, tr("PhotoGroup %1").arg(i + 1));
		layout->addWidget(photoGroups[i]);
	}

	photoGroupBox->setLayout(layout);
}

}
