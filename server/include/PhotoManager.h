//
// Created by ivanium on 2017/5/21.
//

#ifndef FACEMASH2_PHOTOMANAGER_H
#define FACEMASH2_PHOTOMANAGER_H

#include <QString>
#include <QImage>
#include <QList>
#include <algorithm>

#include "Photo.h"

//#define defaultWidth 720
//#define defaultHeight 1280

namespace server{

class PhotoManager {
private:
//    QList<Photo> _album;
    QList<Group> _groups;
    QList<Group>::iterator search(QString groupname);
public:
//    void setting(QString settingFile);

    void addPhoto (QString groupname , QString filename , QImage *image);
//    void addPhotoBatch(QList<Photo> album);//todo change to addGroup

    void addScoreToPhoto (QString groupname , QString filename , int score , bool isJudging);
//    QList<Photo> getAlbum(){ return _album; }
    const QImage *getImage (QString groupname , QString filename , ImageType type);
    const QList<SimpleGroup> *getImages (QList<QString> groupnames , QList<QString> filenames , ImageType type);
    const double getScore(QString groupname, QString filename) ;
};

}
#endif //FACEMASH2_PHOTOSYSTEM_H
