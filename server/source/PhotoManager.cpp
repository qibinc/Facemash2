//
// Created by ivanium on 2017/5/23.
//

#include "PhotoManager.h"
#include <QSettings>
#include <QDebug>

using namespace server;

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

    for (QList<Photo>::iterator iter = _album.begin(); iter != _album.end() ; ++iter) {
        bool flag = true;
        QString name = iter->getFileName();
        for (QList<QString>::iterator stri = filenames.begin(); stri != filenames.end() ; ++stri) {
            if((*stri) == name){
                flag = false;
                break;
            }
        }
        if(flag){
            if(type == FullImage){
                album->append(*(iter->getFullImage()));
            }
            else if (type == Thumbnail){
                album->append(*(iter->getThumbnail()));
            }
        }
    }
    return album;
}

void PhotoManager::setting (QString settingFile) {
    QSettings setting(settingFile,QSettings::IniFormat);
    setting.beginGroup("Photos");
    int i = 0;
    for (QList<Photo>::iterator iter = _album.begin(); iter != _album.end() ; ++iter) {
        setting.beginGroup(QString("photo%1").arg(i++));
        setting.setValue("filename" , (*iter).getFileName());
        setting.setValue("storePath" , (*iter).getFileLocation());
        setting.setValue("score" , (*iter).getTotalScore());
        setting.setValue("judgeTime" , (*iter).getTotalJudge());
        setting.endGroup();
    }
    setting.endGroup();
}
