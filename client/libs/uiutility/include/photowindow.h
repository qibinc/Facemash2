//
// Created by 陈齐斌 on 22/05/2017.
//

#ifndef UIUTILITY_PHOTOWINDOW_H
#define UIUTILITY_PHOTOWINDOW_H

#include <QtWidgets>

namespace uiutility
{
class PhotoWindow : public QMainWindow
{
Q_OBJECT

private:
	QPixmap photoPixmap;
	QLabel *centralLabel;
	QPoint mouseStartLocation, windowStartLocation;
protected:
	void keyReleaseEvent(QKeyEvent *event) override;

	void mousePressEvent(QMouseEvent *event) override;

	void mouseMoveEvent(QMouseEvent *event) override;

	void mouseDoubleClickEvent(QMouseEvent *event) override;

	void wheelEvent(QWheelEvent *event) override;

	void keyPressEvent(QKeyEvent *event) override;

public:
	PhotoWindow(const QString &fileName, QWidget *parent = nullptr);

	virtual ~PhotoWindow();

};
}

#endif //UIUTILITY_PHOTOWINDOW_H
