//
// Created by ivanium on 2017/5/24.
//

#ifndef FACEMASH2_USERMANAGER_H
#define FACEMASH2_USERMANAGER_H

#include <QList>
#include <QString>
#include <QSettings>

#include "User.h"
#include "Photo.h"

namespace server {

class UserManager {
private:
    QList<User> userList;
//    QString ad_ID;
//    QString ad_password;

public:
//    void addID(QString ID, QString password = QString::null);//todo finish admin system
//    void deleteID(QString ID);
//    void changeIDPassword(QString ID, QString oldPw, QString newPw);
    void setting(QString settingFile);
    void init(QString settingFile);

    bool addUser(Date date, QString ID, QString password = QString::null, QString nickname = QString::null);
    QList<QString> searchOnlineUsers();
    bool changeUserPw (Date date , QString ID , QString oldPw , QString newPw);
    void deleteUser(QString ID);

    bool login(Date date, QString ID, QString password = QString::null);
    void logout(Date date, QString ID);

    const QList<QString> queryLog (QString userID);

    bool upload(Date date, QString ID, QString filename);
    bool download(Date date, QString ID, QString filename);
    bool judgePhoto(Date date, QString ID, QString filename);
    bool unjudgePhoto(Date date, QString ID, QString filename);
};

}
#endif //FACEMASH2_USERSYSTEM_H
