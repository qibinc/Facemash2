//
// Created by Qibin Chen on 20/05/2017.
//

#ifndef FACEMASH2_PHOTOSET_H
#define FACEMASH2_PHOTOSET_H

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

	int setID, numberOfPhoto;

	QLabel **photos;
public:
	PhotoSet(int setID, const int fileNum, QString *fileList, const QString &title, QWidget *parent = nullptr);

	QLabel *GetPhoto(int photoID) const;

public slots:
	void PhotoClicked(int i);
	void PhotoRightClicked(int i);
	void PhotoDoubleClicked(int i);

signals:
	void photoClicked(int setID, int photoID);
	void photoDoubleClicked(int setID, int photoID);
	void photoRightClicked(int setID, int photoID);

};

}

#endif //FACEMASH2_PHOTOSET_H
