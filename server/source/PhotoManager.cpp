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

void Group::sortPhoto(bool (*compare)(Photo &, Photo &)) {
    std::sort(_album.begin(), _album.end(), compare);
}

QList<Photo>::iterator Group::search (QString filename) {
    for (QList<Photo>::iterator i = _album.begin(); i != _album.end(); ++i) {
        if((*i).getFileName() == filename){
            return i;
        }
    }
    return _album.end();
}

QList<Group>::iterator PhotoManager::search (QString groupname) {
    for (QList<Group>::iterator iter= groups.begin(); iter != groups.end() ; ++iter) {
        if(iter->getGroupName() == groupname){
            return iter;
        }
    }
    return groups.end();
}

void PhotoManager::addPhoto (QString groupname , QString filename , QImage *image) {
    QList<Group>::iterator g = search(groupname);
    Photo photo(filename, image);
    if(g != groups.end()) {
        QList<Photo>::iterator i = g->search(filename);
        if (i != g->getAlbum().end()) {
            (*i).setImage(*image);
        } else {
            g->getAlbum().append(photo);
        }
        g->sortPhoto(comp);
    }
    else{
        QList<Photo> album;
        album.append(photo);
        groups.append(Group(groupname, &album));
    }
};


void PhotoManager::addPhotoBatch(QList<Photo> album) {
    while(!album.isEmpty()){
        _album.append(album.last());
        album.pop_back();
    }
    sortPhoto(comp);
}

void PhotoManager::addScoreToPhoto (QString groupname , QString filename , int score , bool isJudging) {
    QList<Group>::iterator g = search(groupname);
    if(g != groups.end()){
        QList<Photo>::iterator i = search(filename);
        if(i != g->getAlbum().end()){
            i->addScore(score , isJudging);
        }
    }
}

const QImage *PhotoManager::getImage (QString groupname , QString filename , ImageType type) {
    QList<Group>::iterator g = search(groupname);
    if(g != groups.end()){
        QList<Photo>::iterator i = search(filename);
        if(i != g->getAlbum().end()){
            if(type == FullImage) {
                return (*i).getFullImage();
            }
            else if(type == Thumbnail) {
                return  (*i).getThumbnail();
            }
        }
    }
    return NULL;
}

const QList<Group> *PhotoManager::getImages (QList<QString> groupnames , QList<QString> filenames , ImageType type) {
    sortPhoto(comp);
    QList<Group> *tempgroups = new QList<Group>;
    for (QList<Group>::iterator g = groups.begin(); g != groups.end(); ++g) {
        bool flag1 = true;
        QString groupname = g->getGroupName();
        for(QList<QString>::iterator strg = groupnames.begin(); strg != groupnames.end(); ++strg){
            if((*strg) == groupname){
                flag1 = false;

                QList<QImage> album;
                for (QList<Photo>::iterator iter = g->getAlbum().begin(); iter != g->getAlbum().end(); ++iter) {
                    bool flag2 = true;
                    QString filename = iter->getFileName();
                    for (QList<QString>::iterator stri = filenames.begin(); stri != filenames.end(); ++stri) {
                        if ((*stri) == filename) {
                            flag2 = false;
                            break;
                        }
                    }
                    if (flag2) {
                        if (type == FullImage) {
                            album.append(*(iter->getFullImage()));
                        } else if (type == Thumbnail) {
                            album.append(*(iter->getThumbnail()));
                        }
                    }
                }
                tempgroups->append(Group(groupname, &album));
                break;
            }
        }
        if(flag1){
            tempgroups->append(*g);
        }
    }
    return tempgroups;
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
