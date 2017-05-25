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

    bool UserManager::changeUerPw (Date date , QString ID , QString oldPw , QString newPw) {
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
}