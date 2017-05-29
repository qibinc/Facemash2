//
// Created by ivanium on 2017/5/24.
//

#include "ServerManager.h"
#include "Photo.h"

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
        //todo get pass func and encapsulate following
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
        myServer->PassAllPhotos(UserID, groupnum, photonums, groupnames, images, sizes, imagenames, scores);
        delete groups;
        return succeed;
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

bool server::ServerManager::uploadPhoto (server::Date date , QString userID , QString groupname , QString filename ,
                                         QImage *image) {
    if(userManager->upload(date, userID, filename)){
        photoManager->addPhoto(groupname , filename , image);
        if(image->save(filename, 0)){
            qDebug()<<"save " + groupname + "-" + filename + " successful";
        }
        else {
            qDebug()<<"save " + groupname + "-" + filename + " failed";
        }
        //todo get pass func
        QList<QString> users = userManager->searchOnlineUsers();
        QList<qint32> photonums;    photonums.append(1);
        QList<QString> groupnames, photonames;
        QList<QSize> sizes;  sizes.append(image->size());
        QList<double> scores;   scores.append(0);
        groupnames.append(groupname);
        photonames.append(filename);
        for(QList<QString>::iterator iter = users.begin(); iter != users.end(); ++iter){
            myServer->PassAllPhotos((*iter), 1, photonums, groupnames, image, sizes, photonames, scores);
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
    //todo get func
    const QImage* image = photoManager->getImage(groupname , filename , server::FullImage);
    QList<qint32> photonums;    photonums.append(1);
    QList<QString> groupnames, photonames;
    QList<QSize> sizes; sizes.append(image->size());
    QList<double> scores;   scores.append(photoManager->getScore(groupname, filename));
    groupnames.append(groupname);
    photonames.append(filename);
    myServer->PassAllPhotos(username, 1, photonums, groupnames, *image, sizes, photonames, scores);
    delete image;
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
    QDate date = userData->_datetime.date();
    QTime time = userData->_datetime.time();
    Date tempDate(date.year(), date.month(), date.day(), time.hour(), time.minute(), time.second());
//    QString
    switch (userData->_clienttype)
    {
        case dyh::LOGIN:
            this->login(tempDate, userData->_username, userData.);
            break;
        case dyh::LOGOUT:
            this->logout(tempDate, userData->_username);
            break;
        case dyh::FORBIG:
            this->responseWithFullImage(userData->_username, groupname, filename);
            break;
        case dyh::ADD;
            this->uploadPhoto(tempDate, userData->_username, groupname, filename, image);
            break;
        case dyh::EVAL:
            this->judgePhoto(tempDate, userData->_username, groupname, filename, score);
            break;
        case dyh::FORLOG:
            this->queryLog(userData->_username);
            break;
        default:;
    }
    delete userData;
}

}
