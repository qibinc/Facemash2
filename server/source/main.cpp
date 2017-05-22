#include <iostream>
#include "PhotoSystem.hpp"
//#include <QApplication>
//#include <QtGui/QPixmap>
//#include <QtWidgets/QLabel>
//#include <QImage>

using namespace std;
int main(int argc, char* argv[])
{
    Server::PhotoManager manager;

    QImage image1("image1.jpg");
    Server::Photo testPhoto("testPhoto1", &image1, -1);
    manager.addPhoto(testPhoto);

	cout << "Server Launched" << endl;

//    QApplication a(argc, argv);
//    QLabel* label=new QLabel("",0);
//    QPixmap mp;
//    mp.fromImage(*(manager._album[0].getImage()));
//    label->setPixmap(mp);
//    label->show();
//    return a.exec();
	return 0;
}
