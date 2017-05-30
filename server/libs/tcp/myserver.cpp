#include "myserver.h"
namespace dyh
{
MyServer::MyServer(QObject *parent):
    QObject(parent),totalBytes(0),BytesReceived(0)
{
    _server = new QTcpServer(this);
    _server->listen(QHostAddress::Any, 8888);
    QObject::connect(_server, SIGNAL(newConnection()), this, SLOT(GetConnection()));
    //QObject::connect(_server, SIGNAL(newConnection()), this, SLOT(test()));
}

MyServer::~MyServer()
{

}

void MyServer::GetConnection()
{
    qDebug()<<"Connected!";
    QTcpSocket* _socket = _server->nextPendingConnection();
    //_readwritesockets.append(_socket);
    //_socketdescriptors.append(_socket->socketDescriptor());
    QObject::connect(_socket, SIGNAL(readyRead()), this, SLOT(KeepMessage()));
    QObject::connect(_socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

void MyServer::KeepMessage()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if(totalBytes == 0 && socket->bytesAvailable() >= sizeof(qint64))
    {
        QDataStream in(socket);
        in.setVersion(QDataStream::Qt_4_6);
        in>>totalBytes;
        /*QString path = KeepPath + "cache.txt";
        LocalFile = new QFile(path);
        if(!LocalFile->open(QFile::WriteOnly))
        {
            qDebug()<<"Open File Error!";
            return;
        }*/
    }

    if(BytesReceived < totalBytes)
    {
        BytesReceived += socket->bytesAvailable();
        inArray.append(socket->readAll());
        //LocalFile->write(inArray);
        //inArray.resize(0);
        if(BytesReceived == totalBytes)
        {
            //LocalFile->close();
            totalBytes = 0;
            BytesReceived = 0;

            User *user = new User;
            QDataStream in(&inArray, QIODevice::ReadOnly);
            in.setVersion(QDataStream::Qt_4_6);

            in>>(*user);

            inArray.resize(0);

            if(user->_clienttype == LOGIN)
            {
                if(_map.contains(user->_username))
                {
                    qDebug()<<"UserName Existed!";
                    socket->disconnectFromHost();
                    socket->waitForDisconnected();
                    delete user;
                }
                else
                {
                    _map.insert(user->_username,socket);
                    emit GetMessageFromClient(user);
                }
            }
            else if(user->_clienttype == LOGOUT)
            {
                _map.remove(user->_username);
                emit GetMessageFromClient(user);
            }
            else{
                emit GetMessageFromClient(user);
            }
        }
    }
}


/*void MyServer::SendMessage()
{
    qDebug()<<"hehe";
    QList<qint32> groupnums;
    groupnums.append(1);
    groupnums.append(1);
    QList<QString> dates;
    dates.append("2017-5-26");
    dates.append("2017-5-27");
    QList<QString> filenames;
    filenames.append("E:/Documents/OOP/test1.jpg");
    filenames.append("E:/Documents/OOP/test2.jpg");
    QList<QString> titles;
    titles.append("DYH");
    titles.append("ZJX");
    QList<QString> uploaders;
    uploaders.append("me");
    uploaders.append("you");
    QList<double> points;
    points.append(2.0);
    points.append(1.0);
    PassAllPhotos(groupnums.size(),groupnums, dates, filenames, titles, uploaders, points);
}


void MyServer::SendPoints()
{
    qDebug()<<"xixi!";
    QList<qint32> groupnums;
    groupnums.append(1);
    groupnums.append(1);
    QList<QString> dates;
    dates.append("2017-5-26");
    dates.append("2017-5-27");
    //QList<QString> filenames;
    //filenames.append("E:/Documents/OOP/test1.jpg");
    //filenames.append("E:/Documents/OOP/test2.jpg");
    QList<QString> titles;
    titles.append("DYH");
    titles.append("ZJX");
    //QList<QString> uploaders;
    //uploaders.append("me");
    //uploaders.append("you");
    QList<double> points;
    points.append(23.0);
    points.append(15.0);
    UpdatePoints(groupnums.size(),groupnums,dates,titles,points);
}*/

void MyServer::PassAllPhotos(const QString& username, qint32 groupnum, const QList<qint32> &photonums, const QList<QString> &dates, const QList<QImage> &images, const QList<QSize> &sizes, const QList<QString> &titles, const QList<double> &points)
{
    qDebug()<<"pass photos!";
    qDebug()<<photonums.size();
    //qDebug()<<filepaths.size();
    for(int i = 0; i < titles.size(); i++)
    {
        qDebug()<<titles.at(i);
    }

    QTcpSocket *socket = _map.value(username);

    User user;
    //user._groupnum = photonums.size();
    user._groupnum = groupnum;
    user._servertype = PHOTOS;

    for(int i = 0, k = 0; i < user._groupnum; i++)
    {
        Group group;
        group._photonum = photonums.at(i);
        group._date = dates.at(i);
        for(int j = 0; j < group._photonum; j++)
        {
            //QPixmap pixmap(filepaths.at(k));
            //qDebug()<<filepaths.at(k);
            //qDebug()<<pixmap.isNull();
            //QLabel label;
            //label.setPixmap(pixmap);
            group._photos.append(Photo(images.at(k), titles.at(k), sizes.at(k), points.at(k)));
            qDebug()<<"here:"<<group._photos.size();
            //group._photos.at(0)._photo.save(QString::number(k) + ".jpg",0,100);
            k++;
        }
        user._groups.append(group);
    }

    QByteArray BtArray;
    QDataStream out(&BtArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out<<(qint64)0;
    out<<user;
    out.device()->seek(0);
    out<<(qint64)(BtArray.size() - sizeof(qint64));
    qDebug()<<BtArray.size();
    qint64 _size = socket->write(BtArray);

    qDebug()<<_size;
}

void MyServer::PassUserLog(const QString &username, const QString &log)
{
    qDebug()<<"Pass User Log!";
    QTcpSocket *socket = _map.value(username);
    User user;
    user._username = username;
    user._log = log;
    user._servertype = LOG;
    QByteArray BtArray;
    QDataStream out(&BtArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out<<(qint64)0;
    out<<user;
    out.device()->seek(0);
    out<<(qint64)(BtArray.size() - sizeof(qint64));
    qDebug()<<BtArray.size();
    qint64 _size = socket->write(BtArray);
    socket->waitForBytesWritten();
    qDebug()<<_size;
}


void MyServer::UpdatePoints(const QString& username, qint32 groupnum, const QList<qint32> &photonums, const QList<QString> &dates, const QList<QString> &titles, const QList<double> &points)
{
    qDebug()<<"Update Points!";

    QTcpSocket *socket = _map.value(username);

    User user;
    user._servertype = POINTS;
    user._groupnum = groupnum;
    for(int i = 0, k = 0; i < groupnum; i++)
    {
        Group group;
        group._photonum = photonums.at(i);
        group._date = dates.at(i);
        for(int j = 0; j < group._photonum; j++)
        {
            group._photos.append(Photo(titles.at(k),points.at(k)));
            k++;
            //group._photos.at(j)._title = titles.at(k);
            //group._photos.at(j)
        }
        user._groups.append(group);
    }

    QByteArray BtArray;
    QDataStream out(&BtArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out<<(qint64)0;
    out<<user;
    out.device()->seek(0);
    out<<(qint64)(BtArray.size() - sizeof(qint64));
    qDebug()<<BtArray.size();
    qint64 _size = socket->write(BtArray);
    socket->waitForBytesWritten();
    qDebug()<<_size;
}
}
