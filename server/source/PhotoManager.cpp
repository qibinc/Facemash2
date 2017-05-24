//
// Created by ivanium on 2017/5/23.
//

#include "PhotoManager.h"
#include <QDebug>

using namespace Server;

bool comp(Photo &p1, Photo &p2) {// conpare function, can be extended with multiply sort method
    return (p1.getTotalScore() > p2.getTotalScore());
}

QList<Photo>::iterator PhotoManager::search (QString filename) {
    for (QList<Photo>::iterator i = _album.begin(); i != _album.end(); ++i) {
        if((*i).getFileName() == filename){
            return i;
        }
    }
    return _album.end();
}

void PhotoManager::addPhoto(QString filename, QImage *image) {
    QList<Photo>::iterator i = search(filename);
    Photo photo(filename, image);
    if(i != _album.end()){
        (*i).setImage(*image);
    }
    else{
        _album.append(photo);//todo fix bug
    }
    sortPhoto(comp);
};

void PhotoManager::addPhotoBatch(QList<Photo> album) {
    while(!album.isEmpty()){
        _album.append(album.last());
        album.pop_back();
    }
    sortPhoto(comp);
}

void PhotoManager::addScoreToPhoto (QString filename , int score , bool isJudging) {
    QList<Photo>::iterator i = search(filename);
    if(i != _album.end()){
        i->addScore(score , isJudging);
    }
}


void PhotoManager::sortPhoto(bool (*compare)(Photo &, Photo &)) {
    std::sort(_album.begin(), _album.end(), compare);
}

const QImage *PhotoManager::getImage(QString filename, ImageType type){
    QList<Photo>::iterator i = search(filename);
    if(i != _album.end()){
        if(type == FullImage)
            return (*i).getFullImage();
        else if(type == Thumbnail)
            return  (*i).getThumbnail();
    }
    return NULL;
}

const QList<QImage> *PhotoManager::getImages (QList<QString> filenames, ImageType type) {
    sortPhoto(comp);
    QList<QImage> *album = new QList<QImage>;
    for (QList<QString>::iterator stri = filenames.begin(); stri != filenames.end() ; ++stri) {
        album->append(*getImage((*stri), type));
    }
    return album;
}
