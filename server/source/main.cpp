#include <iostream>
#include "PhotoManager.h"
#include "UserManager.h"

#include <QDebug>
#include <QtWidgets>
#include <include/ServerManager.h>
#include <QDateTime>
using namespace std;
int main(int argc, char* argv[])
{
//    server::PhotoManager photoManager;
//    server::UserManager userManager;
    QApplication a(argc, argv);
    server::ServerManager serverManager;
    cout << "server Launched" << endl;
//    server::Date date;
//
//    QString file("star.png");
//    QImage *image = new QImage(file);
//    QString user("ivanium"), user2("qqq");
//    serverManager.login(date , user , QList<QString>() , QList<QString>());
//    serverManager.login(date , user , QList<QString>() , QList<QString>());
//
//    dyh::User data;
//    dyh::Group g;
//    dyh::Photo p;
//    p._points = 2.50;
//    p._title = "star.png";
//    p._photo = QImage(file);
//    p._size = p._photo.size();
//    g._date = "2017.5.32";
//    g._photonum = 1;
//    g._photos.append(p);
//
//    data._groups.append(g);
//    data._username = "ivanium";
//    data._clienttype = dyh::ADD;
//    data._groupnum = 1;
//    data._datetime = QDateTime::currentDateTime();
//    serverManager.parseData(&data);
//    serverManager.logout(date, user);
//
//    serverManager.logout(date, user);
//    serverManager.logout(date, user2);


//    QLabel* label = new QLabel("test server",0);
//    QPixmap mp = QPixmap::fromImage((*images).at(0));
//    label->resize(1200,1200);
//    label->setPixmap(mp);
//    label->setScaledContents(false);
//    label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored);
//    label->show();
    return a.exec();
	return 0;
}
