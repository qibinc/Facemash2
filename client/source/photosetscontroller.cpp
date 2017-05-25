//
// Created by Qibin Chen on 21/05/2017.
//

#include "photosetscontroller.h"
#include "photoset.h"
#include "photowindow.h"
#include "photoeditmenu.h"
#include "widgetsize.h"
#include "filescanner.h"
#include <iostream>

namespace client
{

PhotoSetsController::PhotoSetsController(QWidget *parent) : QWidget(parent)
{

	menu = new uiutility::PhotoEditMenu(this);
}

QGroupBox *PhotoSetsController::CreatePhotoSetsBox()
{
	QList<QString> dirs = localfilemanager::GetDirs(".");
	numberOfPhotoSet = dirs.size();
	photoSetFiles = new QString*[numberOfPhotoSet];

	numberOfPhotoEverySet = new int[numberOfPhotoSet];

	for (int i = 0; i < numberOfPhotoSet; ++i)
	{
		QList<QString> files = localfilemanager::GetFiles(dirs.value(i));
		numberOfPhotoEverySet[i] = files.size();
		photoSetFiles[i] = new QString[numberOfPhotoEverySet[i]];

		for (int j = 0; j < numberOfPhotoEverySet[i]; ++j)
			photoSetFiles[i][j] = files.value(j);
	}

	selectedSetID = selectedPhotoID = -1;

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
	uiutility::PhotoWindow *photo = new uiutility::PhotoWindow(localfilemanager::OpenImage(photoSetFiles[setID][photoID]), this);
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
