//
// Created by Qibin Chen on 29/05/2017.
//

#ifndef FACEMASH2_STARCHECKBOX_H
#define FACEMASH2_STARCHECKBOX_H

#include <QtWidgets>

namespace uiutility
{

class StarCheckBox : public QCheckBox
{
Q_OBJECT

private:
	int ID;

signals:
	void stateChanged(int id, int state);

private slots:
	void StateChanged();

protected:
	void leaveEvent(QEvent *event) override;

	void enterEvent(QEvent *event) override;

public:
	enum
	{
		CLICK = 0,
		HOVER = 1,
		LEAVE = 2,
	};

	StarCheckBox(int ID, QWidget *parent = nullptr);

};

}
#endif //FACEMASH2_STARCHECKBOX_H
