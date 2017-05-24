//
// Created by ivanium on 2017/5/24.
//

#ifndef FACEMASH2_SERVERMANAGER_H
#define FACEMASH2_SERVERMANAGER_H

#include "UserManager.h"
#include "PhotoManager.h"

enum UserStatus{
    succeed,
    IDCorrupt,
    wrongPW,
    isOnline
};

namespace Server {

class ServerManager {
private:
    UserManager *userManager;
    PhotoManager *photoManager;
public:
    UserStatus logup(Date date, QString userID, QString password);
    UserStatus login(Date date, QString UserID, QString password);
    UserStatus logout(Date date, QString UserID);

    bool uploadPhoto(Date date, QString userID, QString filename);
    bool downloadPhoto(Date date, QString userID, QString filename);

    bool judgePhoto(Date date, QString userID, QString filename, int score);
    bool unJudgePhoto(Date date, QString userID, QString filename, int score);

    const QList<QImage> *initClientWithThumbnails();
    const QImage *responseWithFullImage(QString filename);
};

}
#endif //FACEMASH2_SERVER_H
