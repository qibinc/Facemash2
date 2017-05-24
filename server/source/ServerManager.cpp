//
// Created by ivanium on 2017/5/24.
//

#include "ServerManager.h"

UserStatus Server::ServerManager::logup (Server::Date date , QString userID , QString password) {
    if(userManager->addUser(date, userID, password)){
        return succeed;
    }
    return IDCorrupt;
}

UserStatus Server::ServerManager::login (Server::Date date , QString UserID , QString password) {
    if(userManager->login(date, UserID, password)){
        return succeed;
    }
    return wrongPW;
}

UserStatus Server::ServerManager::logout (Server::Date date , QString UserID) {
    userManager->logout(date, UserID);
    return succeed;
}

bool Server::ServerManager::uploadPhoto (Server::Date date , QString userID , QString filename) {

    return false;
}

bool Server::ServerManager::downloadPhoto (Server::Date date , QString userID , QString filename) {
    return false;
}

bool Server::ServerManager::judgePhoto (Server::Date date , QString userID , QString filename , int score) {
    return false;
}

bool Server::ServerManager::unJudgePhoto (Server::Date date , QString userID , QString filename , int score) {
    return false;
}

const QList<QImage> *Server::ServerManager::initClientWithThumbnails () {
    return nullptr;
}

const QImage *Server::ServerManager::responseWithFullImage (QString filename) {
    return nullptr;
}
