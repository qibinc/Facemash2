//
// Created by Qibin Chen on 21/05/2017.
//

#ifndef UIUTILITY_PHOTOLABEL_H
#define UIUTILITY_PHOTOLABEL_H

#include "clickablelabel.h"

namespace uiutility
{
class PhotoLabel : public ClickableLabel
{
Q_OBJECT

public:
	PhotoLabel(int photoID, QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

	void Select();

	void DeSelect();
private:
	int photoID;

protected:
	virtual void mousePressEvent(QMouseEvent* event) override;

	virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
	void clicked(int id);
	void rightClicked(int id);
	void doubleClicked(int id);
};

}
#endif //UIUTILITY_PHOTOLABEL_H
