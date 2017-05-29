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

	QCheckBox **stars;
	int record;
	enum {StarNumber = 5};
signals:
	void score(int);

public:
	StarCheck(QWidget *parent);

public slots:
	void Stared(int id, int state);
};

}

#endif //FACEMASH2_STARWINDOW_H
