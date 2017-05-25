//
// Created by Qibin Chen on 20/05/2017.
//

#include "photoset.h"
#include "widgetsize.h"
#include "photolabel.h"
#include "photowindow.h"
namespace client
{

PhotoSet::PhotoSet(int setID, const int fileNum, QString *fileList, const QString &title, QWidget *parent)
		: QGroupBox(title, parent), setID(setID), numberOfPhoto(fileNum)

{
	QGridLayout *layout = new QGridLayout;
	photos = new QLabel*[numberOfPhoto];
	int i;
	for (i = 0; i < numberOfPhoto; ++i)
	{
		photos[i] = new uiutility::PhotoLabel(i);
//qDebug() << fileList[i];
		QPixmap pixmap(fileList[i]);
		if (pixmap.isNull())
		{
			pixmap.load(fileList[i], "JPG");
		}
		pixmap = pixmap.scaled(PHOTO_LABEL_SIZE, Qt::KeepAspectRatio);

		photos[i]->resize(pixmap.size());
		photos[i]->setPixmap(pixmap);

		layout->addWidget(photos[i], i / PhotosPerRow, i % PhotosPerRow, 1, 1, Qt::AlignCenter);
		connect(photos[i], SIGNAL(clicked(int)), this, SLOT(PhotoClicked(int)));
		connect(photos[i], SIGNAL(rightClicked(int)), this, SLOT(PhotoRightClicked(int)));
		connect(photos[i], SIGNAL(doubleClicked(int)), this, SLOT(PhotoDoubleClicked(int)));

	}
	while (i % PhotosPerRow != 0)
	{
		QLabel *blankLabel = new uiutility::PhotoLabel(i);
		layout->addWidget(blankLabel, i / PhotosPerRow, i % PhotosPerRow, 1, 1, Qt::AlignCenter);
		i++;
	}
	this->setLayout(layout);
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