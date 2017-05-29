//
// Created by ivanium on 2017/5/24.
//

#include "ServerManager.h"

UserStatus server::ServerManager::signUp (server::Date date , QString userID , QString password) {
    if(userManager->addUser(date, userID, password)){
        return succeed;
    }
    return IDCorrupt;
}

UserStatus server::ServerManager::login (server::Date date , QString UserID , QString password) {
    if(userManager->login(date, UserID, password)){
        return succeed;
    }
    return wrongPW;
}

UserStatus server::ServerManager::logout (server::Date date , QString UserID) {
    userManager->logout(date, UserID);
    return succeed;
}

QList<QString> server::ServerManager::queryLog (QString userID) {
    return userManager->queryLog(userID);
}

bool server::ServerManager::uploadPhoto (server::Date date , QString userID , QString filename , QImage *image) {
    if(userManager->upload(date, userID, filename)){
        photoManager->addPhoto(QString() , filename , image);
        if(image->save(filename, 0)){
            qDebug()<<"save " + filename + " successful";
        }
        else
            qDebug()<<"save " + filename + " failed";
        return true;
    }
    return false;
}

bool server::ServerManager::downloadPhoto (server::Date date , QString userID , QString filename) {
    //todo delete this func
    return false;
}

bool server::ServerManager::judgePhoto (server::Date date , QString userID , QString filename , int score) {
    photoManager->addScoreToPhoto(QString() , filename , score , true);
    userManager->judgePhoto(date, userID, filename);
    return true;
}

bool server::ServerManager::unJudgePhoto (server::Date date , QString userID , QString filename , int score) {
    photoManager->addScoreToPhoto(QString() , filename , score , false);
    return true;
}

const QList<QImage> *server::ServerManager::initClientWithThumbnails (QList<QString> filenames) {
    return photoManager->getImages(QString() , filenames , server::Thumbnail);//todo unnecessary return, after send release the pointer.
}

const QImage *server::ServerManager::responseWithFullImage (QString filename) {
    return photoManager->getImage(QString() , filename , server::FullImage);
}

void server::ServerManager::setUserManager (server::UserManager *userManager) {
    ServerManager::userManager = userManager;
}

void server::ServerManager::setPhotoManager (server::PhotoManager *photoManager) {
    ServerManager::photoManager = photoManager;
}

void server::ServerManager::backUpSettings () {
    userManager->setting("usersSettings.ini");
    photoManager->setting("photosSetting.ini");
}

void server::ServerManager::initWithSettings () {

}
