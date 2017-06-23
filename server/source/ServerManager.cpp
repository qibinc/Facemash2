//Name : ServerManager.cpp
//Author: qiao yifan
//Date : 2017-05-24
//Description : Main part of the server
//Copyright : Using QT to implement the Tcp connection and using some data structs such as QString etc. The other part is finished by qiao yifan. To make the description simpler and shorter, I won't declare QT's using in the project server while I use it almost every single file.


#include "ServerManager.h"
#include "Photo.h"
#include <QDir>

namespace server {

UserStatus server::ServerManager::signUp (server::Date date , QString userID , QString password) {
    if(userManager->addUser(date, userID, password)){
        userManager->login(date, userID, password);
        return succeed;
    }
    return IDCorrupt;
}

UserStatus server::ServerManager::login (server::Date date , QString UserID , QList<QString> groupnames , QList<QString> filenames , QString password) {//todo specify the filenames
    userManager->addUser(date, UserID, password);
    if(userManager->login(date, UserID, password)){
        //todo encapsulate following
        qDebug()<<"server::ServerManager::login ,groupnames:"<<groupnames<<"filenames"<<filenames;
        const QList<SimpleGroup>* groups = photoManager->getImages(groupnames, filenames, Thumbnail);
        qint32 groupnum = groups->length();
        QList<qint32> photonums;
        QList<QString> groupnames;
        QList<QImage> images;
        QList<QSize> sizes;
        QList<QString> imagenames;
        QList<double> scores;
        for(int i = 0; i < groupnum; ++i){
            groupnames.append(groups->at(i).getGroupName());
            photonums.append(groups->at(i).getPhotosNum());
            images.append(groups->at(i).getImages());
            sizes.append(groups->at(i).getSizes());
            imagenames.append(groups->at(i).getNames());
            scores.append(groups->at(i).getScores());
        }
        qDebug()<<"server::ServerManager::login, user is:" << UserID;
        qDebug()<<"server::ServerManager::login, return groups num is:" << groupnum;

        myServer->PassAllPhotos(UserID, groupnum, photonums, groupnames, images, sizes, imagenames, scores);
        delete groups;
        return succeed;
    }
    else {
        qDebug()<<"server::ServerManager::login, "<<UserID<< "is online";
    }
    return wrongPW;
}

UserStatus server::ServerManager::logout (server::Date date , QString UserID) {
    userManager->logout(date, UserID);
    return succeed;
}

QList<QString> server::ServerManager::queryLog (QString userID) {
    QList<QString> logList = userManager->queryLog(userID);
    QString log = "";
    for(QList<QString>::iterator iter = logList.begin(); iter != logList.end(); ++iter){
        log = log + (*iter) + "\n";
    }
    myServer->PassUserLog(userID, log);
    return logList;//todo remove return value
}

bool server::ServerManager::uploadPhoto (server::Date date , QString userID , QString groupname , QString filename , QImage *image) {
    if(userManager->upload(date, userID, filename)){
        photoManager->addPhoto(groupname , filename , image);
        if(!QDir("server" + groupname+"/").exists()){
            QDir().mkdir("server" + groupname + "/");
        }
        if(image->save("server" + groupname + '/' + filename, 0)){
            qDebug()<<"save " + groupname + "-" + filename + " successful";
        }
        else {
            qDebug()<<"save " + groupname + "-" + filename + " failed";
        }
        QList<QString> users = userManager->searchOnlineUsers();
        QList<qint32> photonums;    photonums.append(1);
        QList<QString> groupnames, photonames;
        QList<QSize> sizes;  sizes.append(image->size());
        QList<double> scores;   scores.append(0);
        QList<QImage> images;   images.append(*image);
        groupnames.append(groupname);
        photonames.append(filename);
        for(QList<QString>::iterator iter = users.begin(); iter != users.end() && (*iter) != userID ; ++iter){
            myServer->PassAllPhotos((*iter), 1, photonums, groupnames, images, sizes, photonames, scores);
        }
        return true;
    }
    return false;
}

//bool server::ServerManager::downloadPhoto (server::Date date , QString userID , QString filename) {
//    return false;
//}

bool server::ServerManager::judgePhoto (server::Date date , QString userID , QString groupname , QString filename , int score) {
    photoManager->addScoreToPhoto(groupname , filename , score , true);
    userManager->judgePhoto(date, userID, filename);
    QList<QString> users = userManager->searchOnlineUsers();
    QList<qint32> photonums;    photonums.append(1);
    QList<QString> groupnames, photonames;
    groupnames.append(groupname);   photonames.append(filename);
    QList<double> scores;
    double sc = photoManager->getScore(groupname, filename);
    if(sc == -1){
        qDebug()<< "Error in :server::ServerManager::judgePhoto, server can't find the photo";
        sc = 0;
    }
    scores.append(sc);
    for(QList<QString>::iterator iter = users.begin(); iter != users.end(); ++iter){
        myServer->UpdatePoints((*iter), 1, photonums, groupnames, photonames, scores);
    }
    return true;
}

bool server::ServerManager::unJudgePhoto (server::Date date , QString userID , QString groupname , QString filename , int score) {
    photoManager->addScoreToPhoto(groupname , filename , score , false);
    userManager->unjudgePhoto(date, userID, filename);
    //todo get the func
    QList<QString> users = userManager->searchOnlineUsers();
    QList<qint32> photonums;    photonums.append(1);
    QList<QString> groupnames, photonames;
    groupnames.append(groupname);   photonames.append(filename);
    QList<double> scores;
    scores.append(photoManager->getScore(groupname, filename));
    for(QList<QString>::iterator iter = users.begin(); iter != users.end(); ++iter){
        myServer->UpdatePoints((*iter), 1, photonums, groupnames, photonames, scores);
    }
    return true;
}

//const QList<QImage> *server::ServerManager::initClientWithThumbnails (QList<QString> groupnames , QList<QString> filenames) {
//    const QList<Group> *groups = photoManager->getImages(groupnames , filenames , server::Thumbnail);
//
//    return ;
//}

const QImage *server::ServerManager::responseWithFullImage (QString username , QString groupname , QString filename) {
    qDebug()<<"in responsewith full image";
    const QImage* image = photoManager->getImage(groupname , filename , server::FullImage);
    QList<qint32> photonums;    photonums.append(1);
    QList<QString> groupnames, photonames;
    QList<QSize> sizes; sizes.append(image->size());
    QList<double> scores;   scores.append(photoManager->getScore(groupname, filename));
    QList<QImage> images;   images.append(*image);
    groupnames.append(groupname);
    photonames.append(filename);
    myServer->PassAllPhotos(username, 1, photonums, groupnames, images, sizes, photonames, scores);
    return NULL;
}

void server::ServerManager::setUserManager (server::UserManager *userManager) {
    ServerManager::userManager = userManager;
}

void server::ServerManager::setPhotoManager (server::PhotoManager *photoManager) {
    ServerManager::photoManager = photoManager;
}

void server::ServerManager::backUpSettings () {
    userManager->setting("usersSettings.ini");
//    photoManager->setting("photosSetting.ini");
}

void server::ServerManager::initWithSettings () {

}

void server::ServerManager::parseData (dyh::User *userData) {
    qDebug()<<"server::ServerManager::parseData(), received signal";
    QDate date = userData->_datetime.date();
    QTime time = userData->_datetime.time();
    Date tempDate(date.year(), date.month(), date.day(), time.hour(), time.minute(), time.second());

    switch (userData->_clienttype)
    {
        case dyh::LOGIN: {
            QList<QString> gnames, fnames;
            for(QList<dyh::Group>::iterator i = userData->_groups.begin(); i != userData->_groups.end(); ++i){
                gnames.append(i->_date);
                for(QList<dyh::Photo>::iterator j = i->_photos.begin(); j != i->_photos.end(); ++j){
                    fnames.append(j->_title);
                }
            }
            this->login(tempDate , userData->_username , gnames , fnames);
            break;
        }
        case dyh::LOGOUT: {
            this->logout(tempDate , userData->_username);
            break;
        }
        case dyh::FORBIG: {
            QString groupname = userData->_groups.at(0)._date;
            QString filename = userData->_groups.at(0)._photos.at(0)._title;
            this->responseWithFullImage(userData->_username , groupname , filename);
            break;
        }
        case dyh::ADD: {
            QString groupname = userData->_groups.at(0)._date;
            QString filename = userData->_groups.at(0)._photos.at(0)._title;
            QImage image = userData->_groups.at(0)._photos.at(0)._photo;
            this->uploadPhoto(tempDate , userData->_username , groupname , filename , &image);
            break;
        }
        case dyh::EVAL: {
            QString groupname = userData->_groups.at(0)._date;
            QString filename = userData->_groups.at(0)._photos.at(0)._title;
            int score = userData->_groups.at(0)._photos.at(0)._points;
            this->judgePhoto(tempDate , userData->_username , groupname , filename , score);
            break;
        }
        case dyh::FORLOG: {
            this->queryLog(userData->_username);
            break;
        }
        default:;
    }
    delete userData;
}

}
