//
// Created by Qibin Chen on 21/05/2017.
//

#ifndef FACEMASH2_PHOTOGROUPCONTROLLER_H
#define FACEMASH2_PHOTOGROUPCONTROLLER_H

#include <QtWidgets>

namespace clientnetwork
{
class MyClient;
}

namespace client
{

class PhotoSet;

class PhotoSetsController : public QWidget
{
Q_OBJECT
	int selectedSetID, selectedPhotoID;
	QStringList dirs;
	QList<QList<QString>> photoSetFiles;
	PhotoSet **photoSets;
	QMenu *menu;
	clientnetwork::MyClient *clientNetwork;

public:
	PhotoSetsController(clientnetwork::MyClient *clientNetwork, QWidget *parent = nullptr);

	QGroupBox *CreatePhotoSetsBox();

signals:
	void RefreshComplete(QGroupBox *newPhotoSetsBox);

private slots:
	void CopyPhotoFile();
	void DeletePhotoFile();

public slots:
	void StartRefresh();
	void NewPhoto();
	void PhotoClicked(int setID, int photoID);
	void PhotoRightClicked(int setID, int photoID);
	void PhotoDoubleClicked(int setID, int photoID);
	void PhotoScored(int setID, int photoID, int score);
};

}
#endif //FACEMASH2_PHOTOGROUPCONTROLLER_H
