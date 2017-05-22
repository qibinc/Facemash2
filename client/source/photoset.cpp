//
// Created by 陈齐斌 on 20/05/2017.
//

#include "photoset.h"
#include "widgetsize.h"
#include "photolabel.h"
#include <iostream>

namespace client
{

PhotoSet::PhotoSet(int setID, const int fileNum, const QString fileList[], const QString &title, QWidget *parent) : QGroupBox(title, parent), setID(setID)
{
	QGridLayout *layout = new QGridLayout;

	for (int i = 0; i < fileNum; i++)
	{
		QLabel *photoLabel = new uiutility::PhotoLabel(i);

		QPixmap pixmap(fileList[i]);
		pixmap = pixmap.scaled(PHOTO_LABEL_SIZE, Qt::KeepAspectRatio);

		photoLabel->resize(pixmap.size());
		photoLabel->setPixmap(pixmap);

		layout->addWidget(photoLabel, i / PhotosPerRow, i % PhotosPerRow, 1, 1, Qt::AlignCenter);
		connect(photoLabel, SIGNAL(clicked(int)), this, SLOT(PhotoClicked(int)));
		connect(photoLabel, SIGNAL(rightClicked(int)), this, SLOT(PhotoRightClicked(int)));
		connect(photoLabel, SIGNAL(doubleClicked(int)), this, SLOT(PhotoDoubleClicked(int)));

	}

	this->setLayout(layout);
}

void PhotoSet::PhotoClicked(int i)
{
	std::cout << "Photo Set " << setID <<" Photo " << i << " clicked"<< std::endl;
	emit photoClicked(setID, i);
}

void PhotoSet::PhotoRightClicked(int i)
{
	std::cout << "Photo Set " << setID <<" Photo " << i << " right clicked"<< std::endl;
	emit photoRightClicked(setID, i);
}

void PhotoSet::PhotoDoubleClicked(int i)
{
	std::cout << "Photo Set " << setID <<" Photo " << i << " DOUBLE clicked"<< std::endl;
	emit photoDoubleClicked(setID, i);
}




}