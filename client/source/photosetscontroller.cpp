//
// Created by 陈齐斌 on 21/05/2017.
//

#include "photosetscontroller.h"
#include "photoset.h"
#include "photowindow.h"
#include "photoeditmenu.h"
#include "widgetsize.h"
#include <iostream>

namespace client
{

PhotoSetsController::PhotoSetsController(QWidget *parent) : QWidget(parent)
{
	numberOfPhotoSet = 3;
	numberOfPhotoEverySet = new int[3]{4, 2, 3};
	photoSetFiles = new QString*[numberOfPhotoSet];

	for (int i = 0; i < numberOfPhotoSet; ++i)
	{
		photoSetFiles[i] = new QString[numberOfPhotoEverySet[i]];
		for (int j = 0; j < numberOfPhotoEverySet[i]; ++j)
			photoSetFiles[i][j] = QString(tr("image%1.jpg").arg(1+j));
	}

	selectedSetID = selectedPhotoID = -1;

	menu = new uiutility::PhotoEditMenu(this);
}

QGroupBox *PhotoSetsController::CreatePhotoSetsBox()
{
	photoSets = new PhotoSet *[numberOfPhotoSet];
	QGroupBox *photoSetsBox = new QGroupBox(tr("Photos"));

	QVBoxLayout *layout = new QVBoxLayout;

	for (int i = 0; i < numberOfPhotoSet; i++)
	{
		photoSets[i] = new PhotoSet(i, numberOfPhotoEverySet[i], photoSetFiles[i], tr("PhotoSet %1").arg(i + 1));
		layout->addWidget(photoSets[i], 0, Qt::AlignTop);
		connect(photoSets[i], SIGNAL(photoClicked(int, int)), this, SLOT(PhotoClicked(int, int)));
		connect(photoSets[i], SIGNAL(photoRightClicked(int, int)), this, SLOT(PhotoRightClicked(int, int)));
		connect(photoSets[i], SIGNAL(photoDoubleClicked(int, int)), this, SLOT(PhotoDoubleClicked(int, int)));
	}

	photoSetsBox->setLayout(layout);
	return photoSetsBox;
}

void PhotoSetsController::PhotoClicked(int setID, int photoID)
{
	if (0 <= selectedSetID && selectedSetID < numberOfPhotoSet
	    && 0 <= selectedPhotoID && selectedPhotoID < numberOfPhotoEverySet[selectedSetID])
		photoSets[selectedSetID]->GetPhoto(selectedPhotoID)->setStyleSheet(tr("border: %1px outset transparent").arg(SCREEN_UNIT * 1.5));

	selectedSetID = setID;
	selectedPhotoID = photoID;
	photoSets[selectedSetID]->GetPhoto(selectedPhotoID)->setStyleSheet(tr("border: %1px outset #015CDC").arg(SCREEN_UNIT * 1.5));

}

void PhotoSetsController::PhotoRightClicked(int setID, int photoID)
{
	PhotoClicked(setID, photoID);
	menu->show();
	menu->move(QCursor::pos());
}

void PhotoSetsController::PhotoDoubleClicked(int setID, int photoID)
{
	uiutility::PhotoWindow *photo = new uiutility::PhotoWindow(photoSetFiles[setID][photoID], this);
	photo->show();
}

void PhotoSetsController::CopyPhotoFile()
{
	if (0 <= selectedSetID && selectedSetID < numberOfPhotoSet
			&& 0 <= selectedPhotoID && selectedPhotoID < numberOfPhotoEverySet[selectedSetID])
		QApplication::clipboard()->setPixmap(QPixmap(photoSetFiles[selectedSetID][selectedPhotoID]));
}

void PhotoSetsController::DeletePhotoFile()
{
	std::cout << photoSetFiles[selectedSetID][selectedPhotoID].toStdString() << " pretended to be deleted" << std::endl;

}


}
