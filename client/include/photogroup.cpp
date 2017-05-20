//
// Created by 陈齐斌 on 20/05/2017.
//

#include "photogroup.h"
#include <iostream>

namespace client
{

PhotoGroup::PhotoGroup(const int fileNum, const QString fileList[], const QString &title, QWidget *parent) : QGroupBox(title, parent)
{
	QGridLayout *layout = new QGridLayout;
	for (int i = 0; i < fileNum; i++)
	{
		std::cout << fileList[i].toStdString() << std::endl;

		QLabel *photoLabel = new QLabel;
		photoLabel->resize(PhotoLabelSize);
		photoLabel->setPixmap(QPixmap(fileList[i]));
		photoLabel->setScaledContents(true);
		photoLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

		layout->addWidget(photoLabel, i / PhotosPerRow, i % PhotosPerRow, 1, 1);
	}
	this->setLayout(layout);
}

}