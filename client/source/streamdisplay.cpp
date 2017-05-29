//
// Created by Qibin Chen on 25/05/2017.
//

#include "streamdisplay.h"
#include "filescanner.h"
#include "photowindow.h"
#include "myclient.h"

namespace photostream
{

StreamDisplay::StreamDisplay(clientnetwork::MyClient *clientNetwork, QString from_dir, QObject *parent)
		: QObject(parent), clientNetwork(clientNetwork), from_dir(from_dir)
{
	if (!QDir(from_dir + "cache/").exists())
		QDir().mkdir(from_dir + "cache/");
}

void StreamDisplay::Refresh()
{
	QList<QString> photoFileNames = localfilemanager::GetFiles(from_dir);
	for (auto photoFileName : photoFileNames)
	{
		qDebug() << "photostream:: Refresh " << photoFileName;
		QFile::copy(photoFileName, from_dir + "cache/" + QFileInfo(photoFileName).fileName());
		if (QFileInfo(photoFileName).suffix() != "gif")
			clientNetwork->UploadSinglePhoto(from_dir + "cache/" + QFileInfo(photoFileName).fileName());
		QFile::remove(photoFileName);
		uiutility::PhotoWindow *photo = new uiutility::PhotoWindow(from_dir + "cache/" + QFileInfo(photoFileName).fileName(), true);
		photo->show();
	}
}

}