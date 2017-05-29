//
// Created by ivanium on 2017/5/24.
//

#ifndef FACEMASH2_SERVERMANAGER_H
#define FACEMASH2_SERVERMANAGER_H

#include "UserManager.h"
#include "PhotoManager.h"
#include <QSettings>

enum UserStatus{
    succeed,
    IDCorrupt,
    wrongPW,
    isOnline
};

namespace server {

class ServerManager {
private:
    UserManager *userManager;
    PhotoManager *photoManager;
public:
    void setUserManager (UserManager *userManager);

    void setPhotoManager (PhotoManager *photoManager);

public:
    void backUpSettings();
    void initWithSettings ();

    UserStatus signUp (Date date , QString userID , QString password = QString::null);
    UserStatus login(Date date, QString UserID, QString password = QString::null);
    UserStatus logout(Date date, QString UserID);
    QList<QString> queryLog(QString userID);

    bool uploadPhoto (server::Date date , QString userID , QString filename , QImage *image);
    bool downloadPhoto(Date date, QString userID, QString filename);

    bool judgePhoto(Date date, QString userID, QString filename, int score);
    bool unJudgePhoto(Date date, QString userID, QString filename, int score);

    const QList<QImage> *initClientWithThumbnails (QList<QString> filenames = QList<QString>());
    const QImage *responseWithFullImage(QString filename);

//    parseData()
};

}
#endif //FACEMASH2_SERVER_H
