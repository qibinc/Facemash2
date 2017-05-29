#include <iostream>
#include "filescanner.h"

int main()
{
	QList<QString> dirs = localfilemanager::GetDirs(".");
	for (auto dirname : dirs)
	{
		std::cout << dirname.toStdString() << std::endl;
		QList<QString> files = localfilemanager::GetFiles(dirname);
		for (auto filename : files)
		{
			std::cout << "\t" << filename.toStdString() << std::endl;
		}
		std::cout << std::endl;
	}

	return 0;
}
