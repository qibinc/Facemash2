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

	for (int i = 0; i < dirs.size(); ++i)
	{
		QList<QString> files = localfilemanager::GetFiles(dirs.value(i));

		photoSetFiles.append(files);
	}

	selectedSetID = selectedPhotoID = -1;

	photoSets = new PhotoSet *[photoSetFiles.size()];
	QGroupBox *photoSetsBox = new QGroupBox(tr("Photos"));
	QVBoxLayout *layout = new QVBoxLayout;

	for (int i = 0; i < photoSetFiles.size(); ++i)
	{
		photoSets[i] = new PhotoSet(i, photoSetFiles.value(i), QDir(dirs.value(i)).dirName());
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
	if (0 <= selectedSetID && selectedSetID < photoSetFiles.size()
	    && 0 <= selectedPhotoID && selectedPhotoID < photoSetFiles.value(selectedSetID).size())
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
	uiutility::PhotoWindow *photo = new uiutility::PhotoWindow(photoSetFiles[setID][photoID], 0, this);
	photo->show();
}

void PhotoSetsController::CopyPhotoFile()
{
	if (0 <= selectedSetID && selectedSetID < photoSetFiles.size()
			&& 0 <= selectedPhotoID && selectedPhotoID < photoSetFiles.value(selectedSetID).size())
		QApplication::clipboard()->setPixmap(QPixmap(photoSetFiles[selectedSetID][selectedPhotoID]));
}

void PhotoSetsController::DeletePhotoFile()
{
	std::cout << photoSetFiles[selectedSetID][selectedPhotoID].toStdString() << " pretended to be deleted" << std::endl;

}


}
