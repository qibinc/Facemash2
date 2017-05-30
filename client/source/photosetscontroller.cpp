//
// Created by Qibin Chen on 21/05/2017.
//

#include "photoset.h"
#include "photowindow.h"
#include "photoeditmenu.h"
#include "widgetsize.h"

#include "photosetscontroller.h"
#include "filescanner.h"
#include "myclient.h"

#include <iostream>

namespace client
{

PhotoSetsController::PhotoSetsController(clientnetwork::MyClient *clientNetwork, QWidget *parent) : QWidget(parent), clientNetwork(clientNetwork)
{
	menu = new uiutility::PhotoEditMenu(this);
}

QGroupBox *PhotoSetsController::CreatePhotoSetsBox()
{
	dirs = localfilemanager::GetDirs(".");
	photoSetFiles.clear();
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
		photoSets[i] = new PhotoSet(clientNetwork, i, photoSetFiles.value(i), QDir(dirs.value(i)).dirName());
		layout->addWidget(photoSets[i], 0, Qt::AlignTop);
		connect(photoSets[i], SIGNAL(photoClicked(int, int)), this, SLOT(PhotoClicked(int, int)));
		connect(photoSets[i], SIGNAL(photoRightClicked(int, int)), this, SLOT(PhotoRightClicked(int, int)));
		connect(photoSets[i], SIGNAL(photoDoubleClicked(int, int)), this, SLOT(PhotoDoubleClicked(int, int)));
	}

	photoSetsBox->setLayout(layout);
	return photoSetsBox;
}

void PhotoSetsController::NewPhoto()
{
	QStringList photofiles = QFileDialog::getOpenFileNames(this, "Choose a photo", "./", "Images (*.png *.jpg)");

	for (auto photofile : photofiles)
		clientNetwork->UploadSinglePhoto(photofile);
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
	qDebug() << "PhotoSetsController: Showing Photo Window";
	QSize originalSize = clientNetwork->AskforOneSize(QDir(dirs.value(setID)).dirName(), QFileInfo(photoSetFiles.value(setID).value(photoID)).fileName());
	uiutility::PhotoWindow *photo = new uiutility::PhotoWindow(photoSetFiles[setID][photoID], false, originalSize, this);

	if (localfilemanager::OpenImage(photoSetFiles[setID][photoID])->size() != originalSize)
	{
		qDebug() << "PhotoSetsController: Original Photo Request";
		clientNetwork->AskforBigPhoto(QDir(dirs.value(setID)).dirName(),
		                              QFileInfo(photoSetFiles.value(setID).value(photoID)).fileName());
		connect(clientNetwork, SIGNAL(PhotosSaved(QStringList)), photo, SLOT(RefreshOriginalPhoto(QStringList)));
	}
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

void PhotoSetsController::StartRefresh()
{
	emit RefreshComplete(CreatePhotoSetsBox());
}

}
