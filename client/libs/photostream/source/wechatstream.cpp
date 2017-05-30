//
// Created by Qibin Chen on 25/05/2017.
//

#include "wechatstream.h"
#include "python2.7/Python.h"

namespace photostream
{

WechatStream::WechatStream(QObject *parent) : QThread(parent)
{
}

void WechatStream::run()
{
	pycode = fopen("main.py", "r");

	Py_Initialize();
	PyRun_SimpleFile(pycode, "main.py");
}

}
