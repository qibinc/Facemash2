//
// Created by Qibin Chen on 25/05/2017.
//

#include "filescanner.h"

namespace localfilemanager
{

QList<QString> GetFiles(QString dir)
{
	QDirIterator iter(dir, QStringList() << "*.jpg" << "*.png" << "*.gif", QDir::Files, QDirIterator::Subdirectories);
	QList<QString> files;
	while (iter.hasNext())
	{
		QString &&filename = iter.next();
		if (!OpenImage(filename)->isNull())
			files.append(filename);
		else
		{
			qDebug() << "localfilemanager:: Warning, Can't Open image" + filename + ", deleted";
//			QFile::remove(filename);
		}
	}
	return files;
}

QList<QString> GetDirs(QString dir)
{
	QDirIterator iter(dir, QDir::Dirs);
	QList<QString> dirs;
	while (iter.hasNext())
	{
		QString &&dirname = iter.next();
		if (dirname != "./." && dirname != "./..")
		{
			dirs.append(dirname);
		}
	}
	return dirs;
};

QPixmap *OpenImage(QString filename)
{
	QPixmap *pixmap = new QPixmap(filename);
	if (pixmap->isNull())
	{
		pixmap->load(filename, "JPG");
	}
	if (pixmap->isNull())
	{
		pixmap->load(filename, "PNG");
	}
	return pixmap;
}

QMovie *OpenMovie(QString filename)
{
	QMovie *gif = new QMovie(filename);
	gif->start();
	return gif;
}

}