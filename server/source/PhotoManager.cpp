//
// Created by ivanium on 2017/5/23.
//

#include "PhotoManager.h"
#include <QSettings>
#include <QDebug>

namespace server {

bool comp(Photo &p1, Photo &p2) {// conpare function, can be extended with multiply sort method
    return (p1.getTotalScore() > p2.getTotalScore());
}

    QList<Group>::iterator PhotoManager::search (QString groupname) {
    for (QList<Group>::iterator iter= _groups.begin(); iter != _groups.end() ; ++iter) {
        if(iter->getGroupName() == groupname){
            return iter;
        }
    }
    return _groups.end();
}

void PhotoManager::addPhoto (QString groupname , QString filename , QImage *image) {
    QList<Group>::iterator g = search(groupname);
    Photo photo(filename, image);
    if(g != _groups.end()) {
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
        _groups.append(Group(groupname, &album));
    }
};


//void PhotoManager::addPhotoBatch(QList<Photo> album) {
//    while(!album.isEmpty()){
//        _album.append(album.last());
//        album.pop_back();
//    }
//    sortPhoto(comp);
//}

void PhotoManager::addScoreToPhoto (QString groupname , QString filename , int score , bool isJudging) {
    QList<Group>::iterator g = search(groupname);
    if(g != _groups.end()){
        QList<Photo>::iterator i = g->search(filename);
        if(i != g->getAlbum().end()){
            i->addScore(score , isJudging);
        }
    }
}

const QImage *PhotoManager::getImage (QString groupname , QString filename , ImageType type) {
    QList<Group>::iterator g = search(groupname);
    if(g != _groups.end()){
        QList<Photo>::iterator i = g->search(filename);
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

const QList<SimpleGroup> *PhotoManager::getImages (QList<QString> groupnames , QList<QString> filenames , ImageType type) {
//    sortPhoto(comp);
    QList<SimpleGroup> *tempgroups = new QList<SimpleGroup>;
    for (QList<Group>::iterator g = _groups.begin(); g != _groups.end(); ++g) {
        bool flag1 = true;
        QString groupname = g->getGroupName();
        qDebug()<<"PhotoManager::getImages groupname"<<groupname;
        for(QList<QString>::iterator strg = groupnames.begin(); strg != groupnames.end(); ++strg){
            if((*strg) == groupname){
                flag1 = false;

                QList<SimplePhoto> album;
                for (QList<Photo>::iterator iter = g->getAlbum().begin(); iter != g->getAlbum().end(); ++iter) {
                    bool flag2 = true;
                    QString filename = iter->getFileName();
                    qDebug()<<"PhotoManager::getImages filename"<<filename;

                    for (QList<QString>::iterator stri = filenames.begin(); stri != filenames.end(); ++stri) {
                        if ((*stri) == filename) {
                            flag2 = false;
                            break;
                        }
                    }
                    if (flag2) {
                        double score =  (iter->getTotalJudge() == 0) ? 0 : ((double)(iter->getTotalScore())/iter->getTotalJudge());
                        if (type == FullImage) {
                            SimplePhoto sp(filename, iter->getFullImage(), iter->getFullImage()->size(), score);
                            album.append(sp);
                        } else if (type == Thumbnail) {
                            SimplePhoto sp(filename, iter->getThumbnail(), iter->getFullImage()->size(), score);
                            album.append(sp);
                        }
                    }
                }
                if(album.length() > 0){
                    tempgroups->append(SimpleGroup(groupname, &album));
                }
                break;
            }
        }
        if(flag1){
            QList<SimplePhoto> album;
            for (QList<Photo>::iterator iter = g->getAlbum().begin(); iter != g->getAlbum().end() ; ++iter) {
                double score =  (iter->getTotalJudge() == 0) ? 0 : ((double)(iter->getTotalScore())/iter->getTotalJudge());
                if (type == FullImage) {
                    SimplePhoto sp(iter->getFileName(), iter->getFullImage(), iter->getFullImage()->size(), score);
                    album.append(sp);
                } else if (type == Thumbnail) {
                    SimplePhoto sp(iter->getFileName(), iter->getThumbnail(), iter->getFullImage()->size(), score);
                    album.append(sp);
                }
            }
            if(album.length() > 0){
                tempgroups->append(SimpleGroup(groupname, &album));
            }
        }
    }
    return tempgroups;
}

//void PhotoManager::setting (QString settingFile) {
//    QSettings setting(settingFile,QSettings::IniFormat);
//    setting.beginGroup("Photos");
//    int i = 0;
//    for (QList<Photo>::iterator iter = _album.begin(); iter != _album.end() ; ++iter) {
//        setting.beginGroup(QString("photo%1").arg(i++));
//        setting.setValue("filename" , (*iter).getFileName());
//        setting.setValue("storePath" , (*iter).getFileLocation());
//        setting.setValue("score" , (*iter).getTotalScore());
//        setting.setValue("judgeTime" , (*iter).getTotalJudge());
//        setting.endGroup();
//    }
//    setting.endGroup();
//}

const double PhotoManager::getScore (QString groupname , QString filename) {
    for(QList<Group>::iterator iter = _groups.begin(); iter != _groups.end(); ++iter){
        if(iter->getGroupName() == groupname){
            for(QList<Photo>::const_iterator i = iter->getAlbum().begin(); i != iter->getAlbum().end(); ++i){
                if (i->getFileName() == filename){
                    return i->getTotalJudge() == 0 ? 0 : (double)(i->getTotalScore())/(i->getTotalJudge());
                }
            }
        }
    }
    return 0;
}
}
