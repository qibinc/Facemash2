//
// Created by Qibin Chen on 22/05/2017.
//

#include "widgetsize.h"
#include "photowindow.h"
#include "filescanner.h"

namespace uiutility
{

PhotoWindow::PhotoWindow(QString photoFileName, bool isStream, QSize size, QWidget *parent)
		: QMainWindow(parent, Qt::Window | Qt::FramelessWindowHint ), photoFileName(photoFileName), isStream(isStream), originalSize(size)
{
	setAttribute(Qt::WA_NoSystemBackground, true);
	setAttribute(Qt::WA_TranslucentBackground, true);

	SetPhoto(photoFileName);

	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	setFixedSize(centralLabel->size());

	SetAnimation();
}

PhotoWindow::~PhotoWindow()
{
	delete centralLabel;
}

void PhotoWindow::mousePressEvent(QMouseEvent *event)
{
	mouseStartLocation = event->globalPos();
	windowStartLocation = this->pos();
}

void PhotoWindow::mouseMoveEvent(QMouseEvent *event)
{
	this->move(event->globalPos() - mouseStartLocation + windowStartLocation);
}

void PhotoWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
	Vanish();
}

void PhotoWindow::wheelEvent(QWheelEvent *event)
{
	if (event->orientation() == Qt::Vertical)
	{
		centralLabel->resize((1 + (event->delta() / 5000.0)) * centralLabel->size());
		setFixedSize(centralLabel->size());
	}
}

void PhotoWindow::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
		case Qt::Key_Equal:
			centralLabel->resize(1.1 * centralLabel->size());
			setFixedSize(centralLabel->size());
			break;
		case Qt::Key_Minus:
			centralLabel->resize(0.9 * centralLabel->size());
			setFixedSize(centralLabel->size());
			break;
		case Qt::Key_0:
			centralLabel->resize(originalSize);
			setFixedSize(centralLabel->size());
			break;
		default:
			break;
	}

}

void PhotoWindow::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Space)
	{
		Vanish();
	}
}

void PhotoWindow::SetPhoto(QString photoFileName)
{
	centralLabel = new QLabel;
	centralLabel->setAttribute(Qt::WA_TranslucentBackground, true);
	centralLabel->setScaledContents(true);

	if (QFileInfo(photoFileName).suffix() == "gif")
	{
		QMovie *gif = localfilemanager::OpenMovie(photoFileName);
		if (gif->isValid())
		{
//			gif->setScaledSize(gif->currentPixmap().size().scaled(PHOTO_LABEL_SIZE, Qt::KeepAspectRatio));
			centralLabel->resize(gif->currentPixmap().size());
			centralLabel->setMovie(gif);
			originalSize = centralLabel->size();
			setCentralWidget(centralLabel);
			return;
		}
	}
	QPixmap *photoPixmap = localfilemanager::OpenImage(photoFileName);
	QSize size;
	if (isStream)
		size = photoPixmap->size();
	else
		size = originalSize;
	if (size.width() > PHOTO_LABEL_SIZE.width() * 2 || size.height() > PHOTO_LABEL_SIZE.height() * 2)
	{
		size = size.scaled(PHOTO_LABEL_SIZE * 2, Qt::KeepAspectRatio);
	}

	*photoPixmap = photoPixmap->scaled(size, Qt::KeepAspectRatio, Qt::FastTransformation);
	centralLabel->resize(photoPixmap->size());
	centralLabel->setPixmap(*photoPixmap);
	delete photoPixmap;
	originalSize = centralLabel->size();
	setCentralWidget(centralLabel);

}

void PhotoWindow::SetAnimation()
{
	QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
	centralLabel->setGraphicsEffect(eff);
	QPropertyAnimation *animation = new QPropertyAnimation(eff, "opacity", this);
	animation->setDuration(500);
	animation->setStartValue(0);
	animation->setEndValue(1);
	animation->start(QPropertyAnimation::DeleteWhenStopped);
	if (isStream)
	{
		int &&y = rand() % (SCREEN_UNIT * 200);
		QPropertyAnimation *streamAnimation = new QPropertyAnimation(this, "pos", this);
		streamAnimation->setDuration(5000);
		streamAnimation->setStartValue(QPoint(SCREEN_UNIT * 480, y));
		streamAnimation->setEndValue(QPoint(0, y));
		streamAnimation->start(QPropertyAnimation::DeleteWhenStopped);
		connect(streamAnimation, SIGNAL(finished()), this, SLOT(Vanish()));
	}
	else
	{
		move(QCursor::pos().x() - size().width() / 2, QCursor::pos().y() - size().height() / 2);
	}
}

void PhotoWindow::Vanish()
{
	QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity", this);
	animation->setDuration(500);
	animation->setStartValue(windowOpacity());
	animation->setEndValue(0);
	animation->start(QPropertyAnimation::DeleteWhenStopped);
	connect(animation, SIGNAL(finished()), this, SLOT(close()));
}

void PhotoWindow::RefreshOriginalPhoto(QStringList filelist)
{
	qDebug() << "PhotoWindow::RefreshOriginalPhoto";
	if (filelist.contains(photoFileName))
	{
		SetPhoto(photoFileName);
	}
}


}