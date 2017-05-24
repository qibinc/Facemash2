#include <iostream>
#include "PhotoManager.h"
#include "UserManager.h"

#include <QDebug>
#include <QtWidgets>

using namespace std;
int main(int argc, char* argv[])
{
    Server::PhotoManager photoManager;
//    Server::UserManager userManager;
//    Server::Date date(30,59,11,24);
//    userManager.addUser(date, "ivanium", "nick", "1234");
//    userManager.download(date, "ivanium", "image1.jpg");
//    userManager.upload(date, "ivanium", "image2.jpg");
//    cout<<userManager.changeUerPw(date, "ivanium", "1234", "12345")<<endl;
//    cout<<userManager.changeUerPw(date, "ivanium", "1234", "12345")<<endl;
//
//    userManager.deleteUser("ivanium");

    cout << "Server Launched" << endl;

//    QString file("image1.jpg");
//    QImage *image = new QImage(file);
//    photoManager.addPhoto(file, image);
//    QApplication a(argc, argv);
//    QLabel* label=new QLabel("test server",0);
//    QPixmap mp = QPixmap::fromImage(*(photoManager.getImage(file, Server::FullImage)));
//    label->resize(400,400);
//    label->setPixmap(mp);
//    label->setScaledContents(false);
//    label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored);
//    label->show();
//    return a.exec();
	return 0;
}
