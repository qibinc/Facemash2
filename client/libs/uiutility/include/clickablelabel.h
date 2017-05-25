//
// Created by Qibin Chen on 21/05/2017.
//

#ifndef UIUTILITY_CLICKABLELABEL_H
#define UIUTILITY_CLICKABLELABEL_H

#include <QtWidgets>

namespace uiutility
{

class ClickableLabel : public QLabel
{
	Q_OBJECT
public:
	explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
	~ClickableLabel();

protected:
	virtual void mousePressEvent(QMouseEvent* event) override;

	virtual void mouseDoubleClickEvent(QMouseEvent *event) override;


signals:
	void clicked();
	void doubleClicked();
};

}
#endif //UIUTILITY_CLICKABLELABEL_H
