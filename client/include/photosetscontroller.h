//
// Created by 陈齐斌 on 21/05/2017.
//

#ifndef FACEMASH2_PHOTOGROUPCONTROLLER_H
#define FACEMASH2_PHOTOGROUPCONTROLLER_H

#include <QtWidgets>

namespace client
{

class PhotoSet;

class PhotoSetsController : public QWidget
{
Q_OBJECT
	int selectedSetID, selectedPhotoID;
	int numberOfPhotoSet, *numberOfPhotoEverySet;
	QString **photoSetFiles;
	PhotoSet **photoSets;
	QMenu *menu;
public:
	PhotoSetsController(QWidget *parent = nullptr);

	QGroupBox *CreatePhotoSetsBox();

private slots:
	void CopyPhotoFile();
	void DeletePhotoFile();

public slots:
	void PhotoClicked(int setID, int photoID);
	void PhotoRightClicked(int setID, int photoID);
	void PhotoDoubleClicked(int setID, int photoID);

};

}
#endif //FACEMASH2_PHOTOGROUPCONTROLLER_H
