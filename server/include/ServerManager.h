//
// Created by ivanium on 2017/5/24.
//

#ifndef FACEMASH2_SERVERMANAGER_H
#define FACEMASH2_SERVERMANAGER_H

#include "UserManager.h"
#include "PhotoManager.h"
#include <QSettings>
#include "myserver.h"

namespace server {

enum UserStatus{
    succeed,
    IDCorrupt,
    wrongPW,
    isOnline
};

class ServerManager : public QObject{
    Q_OBJECT
private:
    UserManager *userManager;
    PhotoManager *photoManager;
    dyh::MyServer *myServer;
public:
    ServerManager(){
        userManager = new UserManager;
        photoManager = new PhotoManager;
        myServer = new dyh::MyServer(this);
        QObject::connect(myServer, SIGNAL(GetMessageFromClient(dyh::User*)), this, SLOT(parseData(dyh::User*)));
    }

    ~ServerManager (){
        delete userManager;
        delete photoManager;
        delete myServer;
    }

    void setUserManager (UserManager *userManager);

    void setPhotoManager (PhotoManager *photoManager);

    void backUpSettings();
    void initWithSettings ();

    UserStatus signUp (Date date , QString userID , QString password = QString::null);
    UserStatus login (server::Date date , QString UserID , QList<QString> groupnames , QList<QString> filenames , QString password = "");
    UserStatus logout(Date date, QString UserID);
    QList<QString> queryLog(QString userID);

    bool uploadPhoto (server::Date date , QString userID , QString groupname , QString filename ,
                          QImage *image);
//    bool downloadPhoto(Date date, QString userID, QString filename);

    bool judgePhoto (server::Date date , QString userID , QString groupname , QString filename ,
                         int score);
    bool unJudgePhoto (server::Date date , QString userID , QString groupname , QString filename ,
                           int score);

//    const QList<QImage> *initClientWithThumbnails (QList<QString> groupnames , QList<QString> filenames);
    const QImage *responseWithFullImage (QString username , QString groupname , QString filename);

public slots:
    void parseData(dyh::User *userData);
};

}
#endif //FACEMASH2_SERVER_H
