#include <iostream>
#include "PhotoManager.h"
#include "UserManager.h"

#include <QDebug>
#include <QtWidgets>
#include <include/ServerManager.h>

using namespace std;
int main(int argc, char* argv[])
{
    server::PhotoManager photoManager;
    server::UserManager userManager;
    server::ServerManager serverManager;
    serverManager.setUserManager(&userManager);
    serverManager.setPhotoManager(&photoManager);
    server::Date date;
//    userManager.addUser(date, "ivanium", "nick", "1234");
//    userManager.download(date, "ivanium", "image1.jpg");
//    userManager.upload(date, "ivanium", "image2.jpg");
//    cout<<userManager.changeUserPw(date, "ivanium", "1234", "12345")<<endl;
//    cout<<userManager.changeUserPw(date, "ivanium", "1234", "12345")<<endl;
//
//    userManager.deleteUser("ivanium");

    cout << "server Launched" << endl;

    QString file("1.jpg");
    QImage *image = new QImage(file);
    QString user("ivanium"), user2("qqq");
    serverManager.signUp(date, user);
    serverManager.login(date, user);
    serverManager.login(date, user);
    serverManager.logout(date, user);
    serverManager.signUp(date, user2);

    serverManager.logout(date, user);
    serverManager.logout(date, user2);

    serverManager.login(date, user2);
    serverManager.login(date, user);
    serverManager.uploadPhoto(date, user, file, image);
//    const QImage *ima = photoManager.getImage(file, server::Thumbnail);
    serverManager.judgePhoto(date, user, file, 10);
    qDebug()<<serverManager.queryLog(user);
    const QList<QImage>* images = serverManager.initClientWithThumbnails();
    serverManager.backUpSettings();
//    serverManager.downloadPhoto(date, user, file);
//    photoManager.addPhoto(file, image);
    QApplication a(argc, argv);
    QLabel* label = new QLabel("test server",0);
    QPixmap mp = QPixmap::fromImage((*images).at(0));
    label->resize(1200,1200);
    label->setPixmap(mp);
    label->setScaledContents(false);
    label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored);
    label->show();
    return a.exec();
	return 0;
}
