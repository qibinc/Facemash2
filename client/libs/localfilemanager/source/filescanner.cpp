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
		if (!OpenImage(filename).isNull())
			files.append(filename);
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

QPixmap OpenImage(QString filename)
{
	QPixmap pixmap(filename);
	if (pixmap.isNull())
	{
		pixmap.load(filename, "JPG");
	}
	return pixmap;
}


}