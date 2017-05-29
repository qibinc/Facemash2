//
// Created by Qibin Chen on 25/05/2017.
//

#include "streamdisplay.h"
#include "filescanner.h"
#include "photowindow.h"

namespace photostream
{

StreamDisplay::StreamDisplay(QString to_dir, QString from_dir, QObject *parent)
		: QObject(parent), to_dir(to_dir), from_dir(from_dir)
{
	if (!QDir(to_dir).exists())
		QDir().mkdir(to_dir);
}

void StreamDisplay::Refresh()
{
	QList<QString> photoFileNames = localfilemanager::GetFiles(from_dir);
	for (auto photoFileName : photoFileNames)
	{
		qDebug() << "photostream:: Refresh " << photoFileName;
		QFile::copy(photoFileName, to_dir + QFileInfo(photoFileName).fileName());
		QFile::remove(photoFileName);
		uiutility::PhotoWindow *photo = new uiutility::PhotoWindow(to_dir + QFileInfo(photoFileName).fileName(), 1);
		photo->show();
	}
}

}