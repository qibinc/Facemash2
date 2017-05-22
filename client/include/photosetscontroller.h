//
// Created by 陈齐斌 on 21/05/2017.
//

#ifndef CLIENT_PHOTOGROUPCONTROLLER_H
#define CLIENT_PHOTOGROUPCONTROLLER_H

#include <QtWidgets>

namespace client
{

class PhotoSet;

class PhotoSetsController : public QObject
{
Q_OBJECT

	enum
	{
		NumPhotoSets = 3
	};

	PhotoSet **photoSets;
public:
	PhotoSetsController();

	QGroupBox *CreatePhotoSetsBox();

};

}
#endif //CLIENT_PHOTOGROUPCONTROLLER_H
