//
// Created by Qibin Chen on 25/05/2017.
//

#ifndef FACEMASH2_WECHATSTREAM_H
#define FACEMASH2_WECHATSTREAM_H

#include <QtWidgets>

namespace photostream
{

class WechatStream : public QThread
{
protected:
	void run() override ;

public:
	WechatStream(QObject *parent = nullptr);
};
}

#endif //FACEMASH2_WECHATSTREAM_H
