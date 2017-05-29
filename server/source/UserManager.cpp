//
// Created by ivanium on 2017/5/24.
//

#include "UserManager.h"
#include <QDebug>

namespace server{

bool UserManager::addUser (Date date , QString ID , QString password , QString nickname) {
    for (int i = 0; i < userList.size(); ++i) {
        if(userList.at(i).getID() == ID){
            return false;
        }
    }
    User user(date, ID, password, nickname);
    userList.append(user);
    return true;
}

bool UserManager::changeUserPw (Date date , QString ID , QString oldPw , QString newPw) {
    for(int i = 0; i < userList.size(); ++i){
        User temp = userList.at(i);
        if(temp.getID() == ID){
            if(temp.passwordCheck(oldPw)){
                temp.changePassword(date, newPw);
                return true;
            }
            return false;
        }
    }
    return false;
}

void UserManager::deleteUser (QString ID) {
    for (int i = 0; i < userList.size(); ++i) {
        if(userList.at(i).getID() == ID){
            qDebug()<<userList.at(i).getID() + " is removed";
            userList.removeAt(i);
            return;
        }
    }
}

bool UserManager::login (Date date , QString ID , QString password) {
    for (int i = 0; i < userList.size(); ++i) {
        if(userList.at(i).getID() == ID){
            return userList[i].login(date, password);
        }
    }
    return false;
}

void UserManager::logout (Date date , QString ID) {
    for (int i = 0; i < userList.size(); ++i) {
        if(userList.at(i).getID() == ID){
            userList[i].logout(date);
            break;
        }
    }
}

const QList<QString> UserManager::queryLog (QString userID){
    QList<QString> log;
    for (QList<User>::iterator iter = userList.begin(); iter != userList.end(); ++iter) {
        if(iter->getID() == userID){
//            const QList<Event> *events = iter->getLog();
//            for (QList<Event>::const_iterator ei = events->begin(); ei != events->end() ; ++ei) {
//                log.append(ei->toQString());
//            }
            return (*iter).getLog();
        }
    }
    return log;
}

bool UserManager::upload (Date date , QString ID , QString filename) {
    for (int i = 0; i < userList.size(); ++i) {
        if(userList.at(i).getID() == ID){
            userList[i].upload(date, filename);
            return true;
        }
    }
    return false;
}

bool UserManager::download (Date date , QString ID , QString filename) {
    for (int i = 0; i < userList.size(); ++i) {
        if(userList.at(i).getID() == ID){
            userList[i].download(date, filename);
            return true;
        }
    }
    return false;
}

bool UserManager::judgePhoto (Date date , QString ID , QString filename) {
    for (int i = 0; i < userList.size(); ++i) {
        if(userList.at(i).getID() == ID){
            userList[i].judge(date, filename);
            return true;
        }
    }
    return false;
}

void UserManager::setting (QString settingFile) {
    QSettings setting(settingFile,QSettings::IniFormat);
    setting.beginGroup("users");
    setting.setValue("length", userList.length());
    int i = 0;
    for (QList<User>::iterator iter = userList.begin(); iter != userList.end() ; ++iter) {
        setting.beginGroup(QString("user%1").arg(i++));
        setting.setValue("ID", (*iter).getID());
        setting.setValue("nickname", (*iter).getNickname());
        setting.setValue("password", (*iter).getPassword());
        setting.setValue("judgeTime", (*iter).getTotalJudge());
//        setting.setValue("errorTime", 0);
//        setting.setValue("online", false);
        setting.endGroup();
    }
    setting.endGroup();

}

void UserManager::init (QString settingFile) {//todo finish the init
    QSettings setting(settingFile, QSettings::IniFormat);
    setting.beginGroup("users");
    int length = setting.value("length").toInt();
    for (int i = 0; i < length; ++i) {
        setting.beginGroup(QString("user%1").arg(i));
//        setting.value()
    }

}

}