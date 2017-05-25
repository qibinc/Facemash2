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
{}

void StreamDisplay::Refresh()
{
	qDebug() << "StreamDisplay::Refresh";
	QList<QString> photoFileNames = localfilemanager::GetFiles(from_dir);
	for (auto photoFileName : photoFileNames)
	{
		qDebug() << photoFileName;
		uiutility::PhotoWindow *photo = new uiutility::PhotoWindow(localfilemanager::OpenImage(photoFileName));
		photo->show();
		QFile::remove(photoFileName);
	}

}

}