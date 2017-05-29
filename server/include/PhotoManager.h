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

#define defaultWidth 720
#define defaultHeight 1280

namespace server{
enum ImageType{
    FullImage,
    Thumbnail
};

class Group{
private:
    QString groupName;
    QList<Photo> _album;
public:
    const QString &getGroupName () const { return groupName; }
    QList<Photo> &getAlbum() { return  _album; };
};

class PhotoManager {
private:
    QList<Photo> _album;

    QList<Photo>::iterator search(QString filename);
public:
    void setting(QString settingFile);
//    PhotoManager(){};
//        void updatePhoto(info clientInfo){};
    void addPhoto(QString filename, QImage *image);
    void addPhotoBatch(QList<Photo> album);
    void addScoreToPhoto (QString filename , int score , bool isJudging);

    void sortPhoto(bool (*compare)(Photo &, Photo &));
//    QList<Photo> getAlbum(){ return _album; }//todo for test
    const QImage *getImage(QString filename, ImageType type);
    const QList<QImage> *getImages(QList<QString> filenames, ImageType type);
//
//    QImage *getThumbnail(QString filename);
//    QList<QImage> *getThumbnails(QList<QString> filenames);
};

}
#endif //FACEMASH2_PHOTOSYSTEM_H
