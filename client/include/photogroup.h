//
// Created by 陈齐斌 on 20/05/2017.
//

#ifndef CLIENT_PHOTOGROUP_H
#define CLIENT_PHOTOGROUP_H

#include <QtWidgets>

namespace client
{

class PhotoGroup : public QGroupBox
{
Q_OBJECT
//  Constants
	const QSize PhotoLabelSize = QSize(100, 100);

	enum
	{
		/**
		 * We can set them as parameters later
		 */
		PhotosPerRow = 4
	};
public:
	PhotoGroup(const int fileNum, const QString fileList[], const QString &title, QWidget *parent = nullptr);


};

}

#endif //CLIENT_PHOTOGROUP_H
