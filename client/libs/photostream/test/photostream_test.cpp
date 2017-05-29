//
// Created by Qibin Chen on 25/05/2017.
//
#include "wechatstream.h"
#include <QtWidgets>
#include <iostream>
using namespace photostream;

int main()
{
	QThread *stream = new WechatStream;
	stream->start();
}
