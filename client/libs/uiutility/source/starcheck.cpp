//
// Created by Qibin Chen on 29/05/2017.
//

#include "starcheck.h"
#include "starcheckbox.h"

namespace uiutility
{

StarCheck::StarCheck(int photoID, QWidget *parent) : QWidget(parent), photoID(photoID)
{
	QHBoxLayout *layout = new QHBoxLayout(this);
	stars = new QCheckBox*[StarNumber];
	for (int i = 0; i < StarNumber; i++)
	{
		stars[i] = new StarCheckBox(i, this);
		layout->addWidget(stars[i]);
		connect(stars[i], SIGNAL(stateChanged(int, int)), this, SLOT(Stared(int, int)));
	}
	setLayout(layout);

	record = 0;
}

void StarCheck::Stared(int id, int state)
{
	if (state == StarCheckBox::LEAVE)
	{
		for (int i = 0; i < record; ++i)
		{
			stars[i]->setChecked(true);
		}
		for (int i = record; i < StarNumber; ++i)
		{
			stars[i]->setChecked(false);
		}
	}
	else
	{
		for (int i = 0; i <= id; ++i)
		{
			stars[i]->setChecked(true);
		}
		for (int i = id + 1; i < StarNumber; ++i)
		{
			stars[i]->setChecked(false);
		}

		if (state == StarCheckBox::CLICK)
		{
			record = id + 1;
			emit score(photoID, record);
		}
	}
}

}
