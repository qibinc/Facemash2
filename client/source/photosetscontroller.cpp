//
// Created by 陈齐斌 on 21/05/2017.
//

#include "photosetscontroller.h"
#include "photoset.h"
#include <iostream>

namespace client
{

PhotoSetsController::PhotoSetsController()
{
}

QGroupBox *PhotoSetsController::CreatePhotoSetsBox()
{
	photoSets = new PhotoSet *[NumPhotoSets];
	QGroupBox *photoSetsBox = new QGroupBox(tr("Photos"));

	QVBoxLayout *layout = new QVBoxLayout;

	for (int i = 0; i < NumPhotoSets; i++)
	{
		const QString photos[5] = {tr("image1.jpg"), tr("image2.jpg"), tr("image3.jpg"), tr("image4.jpg"),
		                           tr("image5.jpg")};

		photoSets[i] = new PhotoSet(i, 5, photos, tr("PhotoSet %1").arg(i + 1));
		layout->addWidget(photoSets[i], 0, Qt::AlignTop);
	}

	photoSetsBox->setLayout(layout);
	return photoSetsBox;
}
}
