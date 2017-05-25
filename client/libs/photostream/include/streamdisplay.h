//
// Created by Qibin Chen on 25/05/2017.
//

#ifndef FACEMASH2_STREAMDISPLAY_H
#define FACEMASH2_STREAMDISPLAY_H

#include <QtWidgets>

namespace photostream
{

class StreamDisplay : public QObject
{
Q_OBJECT

	QString from_dir, to_dir;

public:
	StreamDisplay(QString to_dir, QString from_dir = "wechat_photo_stream_temp/", QObject *parent = nullptr);

public slots:
	void Refresh();
};

}

#endif //FACEMASH2_STREAMDISPLAY_H
