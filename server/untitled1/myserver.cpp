#include "myserver.h"

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
    _readwritesocket = _server->nextPendingConnection();
    QObject::connect(_readwritesocket, SIGNAL(readyRead()), this, SLOT(KeepMessage()));
}

void MyServer::KeepMessage()
{
    if(totalBytes == 0 && _readwritesocket->bytesAvailable() >= sizeof(qint64))
    {
        QDataStream in(_readwritesocket);
        in.setVersion(QDataStream::Qt_4_6);
        in>>totalBytes;
        QString path = KeepPath + "cache.txt";
        LocalFile = new QFile(path);
        if(!LocalFile->open(QFile::WriteOnly))
        {
            qDebug()<<"Open File Error!";
            return;
        }
    }

    if(BytesReceived < totalBytes)
    {
        BytesReceived += _readwritesocket->bytesAvailable();
        inArray = _readwritesocket->readAll();
        LocalFile->write(inArray);
        inArray.resize(0);
        if(BytesReceived == totalBytes)
        {
            LocalFile->close();
            totalBytes = 0;
            BytesReceived = 0;
            emit GetMessageFromClient();
        }
    }
}

void MyServer::SetPath(const QString &path)
{
    KeepPath = path;
}


void MyServer::SendMessage()
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
}

void MyServer::PassAllPhotos(qint32 groupnum, const QList<qint32> &photonums, const QList<QString> &dates, const QList<QString> &filepaths, const QList<QString> &titles, const QList<QString> &uploaders, const QList<double> &points)
{
    qDebug()<<"pass!";
    qDebug()<<photonums.size();
    qDebug()<<filepaths.size();
    for(int i = 0; i < titles.size(); i++)
    {
        qDebug()<<titles.at(i);
    }
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
            qDebug()<<filepaths.at(k);
            //qDebug()<<pixmap.isNull();
            //QLabel label;
            //label.setPixmap(pixmap);
            group._photos.append(Photo(filepaths.at(k), titles.at(k), uploaders.at(k), points.at(k)));
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
    qint64 _size = _readwritesocket->write(BtArray);
    qDebug()<<_size;
}

void MyServer::PassUserLog(const QString &username, const QString &log)
{
    qDebug()<<"Pass User Log!";
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
    qint64 _size = _readwritesocket->write(BtArray);
    qDebug()<<_size;
}


void MyServer::UpdatePoints(qint32 groupnum, const QList<qint32> &photonums, const QList<QString> &dates, const QList<QString> &titles, const QList<double> &points)
{
    qDebug()<<"Update Points!";
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
    qint64 _size = _readwritesocket->write(BtArray);
    qDebug()<<_size;
}
