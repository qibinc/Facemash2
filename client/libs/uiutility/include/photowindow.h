//
// Created by Qibin Chen on 22/05/2017.
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
	bool isStream;
	QSize originalSize;
	QLabel *centralLabel;
	QPoint mouseStartLocation, windowStartLocation;

	void SetPhoto(QString photoFileName);

	void SetAnimation();

private slots:
	void Vanish();

protected:
	void keyReleaseEvent(QKeyEvent *event) override;

	void mousePressEvent(QMouseEvent *event) override;

	void mouseMoveEvent(QMouseEvent *event) override;

	void mouseDoubleClickEvent(QMouseEvent *event) override;

	void wheelEvent(QWheelEvent *event) override;

	void keyPressEvent(QKeyEvent *event) override;

public:
	PhotoWindow(QString photoFileName, bool isStream = false, QWidget *parent = nullptr);

	virtual ~PhotoWindow();

};
}

#endif //UIUTILITY_PHOTOWINDOW_H
