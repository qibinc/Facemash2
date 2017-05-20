//
// Created by 陈齐斌 on 20/05/2017.
//

#ifndef CLIENT_WIDGET_H
#define CLIENT_WIDGET_H

#include <QtWidgets>

namespace Ui
{
class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT
public:
	explicit Widget(QWidget* parent = nullptr);

	virtual ~Widget();

private slots:
	void SlotPushButton();

private:
	Ui::Widget *ui;
	int m_icount;
};


#endif //CLIENT_WIDGET_H
