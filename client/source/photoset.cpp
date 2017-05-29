//
// Created by Qibin Chen on 20/05/2017.
//

#include "photoset.h"
#include "widgetsize.h"
#include "photolabel.h"
#include "starcheck.h"
#include "photowindow.h"
#include "filescanner.h"

namespace client
{

PhotoSet::PhotoSet(int setID, QList<QString> fileList, const QString &title, QWidget *parent)
		: QGroupBox(title, parent), setID(setID), fileList(fileList)

{
	QGridLayout *layout = new QGridLayout;
	CreatePhotos(layout);
	CreateStarCheckBoxes(layout);
	this->setLayout(layout);
}

void PhotoSet::CreatePhotos(QGridLayout *layout)
{
	photos = new QLabel*[fileList.size()];
	starCheckBoxes = new QWidget*[fileList.size()];

	int i;
	for (i = 0; i < fileList.size(); ++i)
	{
		photos[i] = new uiutility::PhotoLabel(i);

		QPixmap *pixmap = localfilemanager::OpenImage(fileList.value(i));
		*pixmap = pixmap->scaled(PHOTO_LABEL_SIZE, Qt::KeepAspectRatio);
		photos[i]->resize(pixmap->size());
		photos[i]->setPixmap(*pixmap);
		delete pixmap;
		layout->addWidget(photos[i], i / PhotosPerRow * 2, i % PhotosPerRow, 1, 1, Qt::AlignCenter);
		connect(photos[i], SIGNAL(clicked(int)), this, SLOT(PhotoClicked(int)));
		connect(photos[i], SIGNAL(rightClicked(int)), this, SLOT(PhotoRightClicked(int)));
		connect(photos[i], SIGNAL(doubleClicked(int)), this, SLOT(PhotoDoubleClicked(int)));
	}
//	Place holder
	while (i % PhotosPerRow != 0)
	{
		QLabel *blankLabel = new uiutility::PhotoLabel(i);
		layout->addWidget(blankLabel, i / PhotosPerRow * 2, i % PhotosPerRow, 1, 1, Qt::AlignCenter);
		i++;
	}
}

void PhotoSet::CreateStarCheckBoxes(QGridLayout *layout)
{
	int i;
	for (i = 0; i < fileList.size(); ++i)
	{
		starCheckBoxes[i] = new uiutility::StarCheck(photos[i]);

		layout->addWidget(starCheckBoxes[i], i / PhotosPerRow * 2 + 1, i % PhotosPerRow, 1, 1, Qt::AlignCenter);
//		connect(starCheckBoxes[i], SIGNAL(clicked(int)), this, SLOT(PhotoClicked(int)));
	}
}

void PhotoSet::PhotoClicked(int i)
{
	emit photoClicked(setID, i);
}

void PhotoSet::PhotoRightClicked(int i)
{
	emit photoRightClicked(setID, i);
}

void PhotoSet::PhotoDoubleClicked(int i)
{
	emit photoDoubleClicked(setID, i);
}

QLabel *PhotoSet::GetPhoto(int photoID) const
{
	return photos[photoID];
}


}