//
// Created by ivanium on 2017/5/24.
//

#include "ServerManager.h"

UserStatus server::ServerManager::logup (server::Date date , QString userID , QString password) {
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

bool server::ServerManager::uploadPhoto (server::Date date , QString userID , QString filename) {

    return false;
}

bool server::ServerManager::downloadPhoto (server::Date date , QString userID , QString filename) {

    return false;
}

bool server::ServerManager::judgePhoto (server::Date date , QString userID , QString filename , int score) {
    return false;
}

bool server::ServerManager::unJudgePhoto (server::Date date , QString userID , QString filename , int score) {
    return false;
}

const QList<QImage> *server::ServerManager::initClientWithThumbnails () {
    return nullptr;
}

const QImage *server::ServerManager::responseWithFullImage (QString filename) {
    return nullptr;
}
