//
// Created by Qibin Chen on 20/05/2017.
//

#include "photoset.h"
#include "widgetsize.h"
#include "photolabel.h"
#include "starcheck.h"
#include "photowindow.h"
#include "filescanner.h"
#include "myclient.h"

namespace client
{

PhotoSet::PhotoSet(clientnetwork::MyClient *clientNetwork, int setID, QList<QString> fileList, const QString &title, QWidget *parent)
		: clientNetwork(clientNetwork), QGroupBox(title, parent), setID(setID), fileList(fileList), dirname(title)

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
		starCheckBoxes[i] = new uiutility::StarCheck(clientNetwork->AskforOnePoints(dirname, QFileInfo(fileList[i]).fileName()), i, photos[i]);
		connect(starCheckBoxes[i], SIGNAL(score(int, int)), this, SLOT(Score(int, int)));
		layout->addWidget(starCheckBoxes[i], i / PhotosPerRow * 2 + 1, i % PhotosPerRow, 1, 1, Qt::AlignCenter);
//		connect(starCheckBoxes[i], SIGNAL(clicked(int)), this, SLOT(PhotoClicked(int)));
	}
}

void PhotoSet::PhotoClicked(int photoID)
{
	emit photoClicked(setID, photoID);
}

void PhotoSet::PhotoRightClicked(int photoID)
{
	emit photoRightClicked(setID, photoID);
}

void PhotoSet::PhotoDoubleClicked(int photoID)
{
	emit photoDoubleClicked(setID, photoID);
}

QLabel *PhotoSet::GetPhoto(int photoID) const
{
	return photos[photoID];
}

void PhotoSet::Score(int photoID, int score)
{
	clientNetwork->ScorePhoto(dirname, QFileInfo(fileList.value(photoID)).fileName(), score);
}


}