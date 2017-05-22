//
// Created by 陈齐斌 on 20/05/2017.
//

#ifndef CLIENT_PHOTOSET_H
#define CLIENT_PHOTOSET_H

#include <QtWidgets>

namespace client
{

class PhotoSet : public QGroupBox
{
Q_OBJECT
	enum
	{
		/**
		 * We can set them as parameters later
		 */
		PhotosPerRow = 3
	};

	int setID;

public:
	PhotoSet(int setID, const int fileNum, const QString fileList[], const QString &title, QWidget *parent = nullptr);

signals:
	void photoClicked(int setID, int photoID);
	void photoDoubleClicked(int setID, int photoID);
	void photoRightClicked(int setID, int photoID);
public slots:
	void PhotoClicked(int i);
	void PhotoRightClicked(int i);
	void PhotoDoubleClicked(int i);
};

}

#endif //CLIENT_PHOTOSET_H
