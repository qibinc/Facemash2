//
// Created by Qibin Chen on 25/05/2017.
//

#ifndef FACEMASH2_FILESCANNER_H
#define FACEMASH2_FILESCANNER_H

#include <QtWidgets>

namespace localfilemanager
{

QList<QString> GetDirs(QString dir);

QList<QString> GetFiles(QString dir);

QPixmap OpenImage(QString filename);

}

#endif //FACEMASH2_FILESCANNER_H
