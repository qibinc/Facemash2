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
enum ImageType{
    FullImage,
    Thumbnail
};

class SinglePhoto{
    
};

class Group{
private:
    QString _groupName;
    QList<Photo> _album;
public:
    Group(QString groupname, QList<Photo> *album):
            _groupName(groupname), _album(*album){};
    const QString &getGroupName () const { return _groupName; }
    void setGroupName (const QString &_groupName) { Group::_groupName = _groupName; }

    QList<Photo> &getAlbum() { return  _album; };
    QList<Photo>::iterator search(QString filename);

    void sortPhoto(bool (*compare)(Photo &, Photo &));
};


class PhotoManager {
private:
//    QList<Photo> _album;
    QList<Group> groups;
    QList<Group>::iterator search(QString groupname);
public:
    void setting(QString settingFile);

    void addPhoto (QString groupname , QString filename , QImage *image);
    void addPhotoBatch(QList<Photo> album);//todo change to addGroup

    void addScoreToPhoto (QString groupname , QString filename , int score , bool isJudging);
//    QList<Photo> getAlbum(){ return _album; }//todo for test
    const QImage *getImage (QString groupname , QString filename , ImageType type);
    const QList<Group> *getImages (QList<QString> groupnames , QList<QString> filenames , ImageType type);
};

}
#endif //FACEMASH2_PHOTOSYSTEM_H
