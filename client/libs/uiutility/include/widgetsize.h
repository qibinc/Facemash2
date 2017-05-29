//
// Created by 陈齐斌 on 20/05/2017.
//

#ifndef UIUTILITY_WIDGETSIZE_H
#define UIUTILITY_WIDGETSIZE_H

#include <QtWidgets>

namespace uiutility
{
/**
 * The Whole Screen Width is devided into 480 units
 */
#define SCREEN_UNIT QApplication::desktop()->screenGeometry().width() / 480

#define WINDOW_GEOMETRY QRect(60 * SCREEN_UNIT, 40 * SCREEN_UNIT, 360 * SCREEN_UNIT, 240 * SCREEN_UNIT)

#define PHOTO_LABEL_SIZE QSize(80 * SCREEN_UNIT, 80 * SCREEN_UNIT)

#endif //UIUTILITY_WIDGETSIZE_H
}
