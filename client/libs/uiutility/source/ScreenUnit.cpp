//
// Created by 陈齐斌 on 20/05/2017.
//

#include "ScreenUnit.h"
#include <QDesktopWidget>
#include <QApplication>

namespace utility
{

int ScreenUnit::Unit()
{
	return QApplication::desktop()->screenGeometry().width() / 480;
}

}