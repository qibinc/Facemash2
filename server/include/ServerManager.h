//Name : ServerManager.h
//Author: qiao yifan
//Date : 2017-05-24
//Description : Main part of the server
//Copyright : Using QT to implement the Tcp connection and using some data structs such as QString etc. The other part is finished by qiao yifan. To make the description simpler and shorter, I won't declare QT's using in the project server while I use it almost every single file.

#ifndef FACEMASH2_SERVERMANAGER_H
#define FACEMASH2_SERVERMANAGER_H

#include "UserManager.h"
#include "PhotoManager.h"
#include <QSettings>
#include "myserver.h"

namespace server {

// enum type of user status when user log in
enum UserStatus{
    succeed,
    IDCorrupt, //user's ID is already signed
    wrongPW,
    isOnline
};

class ServerManager : public QObject{
    Q_OBJECT
private:
    UserManager *userManager;   //sub managers' pointers to conbine different objects' features
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

    //Setters
    void setUserManager (UserManager *userManager);
    void setPhotoManager (PhotoManager *photoManager);

    //todo 
    //back up server settings and init server with settings, including users' information and photos' information
    void backUpSettings();
    void initWithSettings ();

    //
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
