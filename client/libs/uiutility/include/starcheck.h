//
// Created by Qibin Chen on 29/05/2017.
//

#ifndef FACEMASH2_STARWINDOW_H
#define FACEMASH2_STARWINDOW_H

#include <QtWidgets>

namespace uiutility
{

class StarCheck : public QWidget
{
Q_OBJECT
	enum {StarNumber = 5};

	QCheckBox **stars;
	int record, photoID;
signals:
	void score(int photoID, int record);

public:
	StarCheck(int score, int photoID, QWidget *parent = nullptr);

public slots:
	void Stared(int id, int state);
};

}

#endif //FACEMASH2_STARWINDOW_H
