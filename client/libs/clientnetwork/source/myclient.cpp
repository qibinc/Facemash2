#include "myclient.h"
#include "data.h"
#include "filescanner.h"

namespace clientnetwork
{

MyClient::MyClient(QObject *parent) :
        QObject(parent), totalBytes(0), BytesReceived(0),
        HostIP(QHostAddress(QHostAddress::LocalHost).toString()),
        KeepPath("./")
{
    _readwritesocket = new QTcpSocket(this);
    //_readwritesocket->connectToHost("101.5.218.89", 8888);
    // _readwritesocket->waitForConnected(2000);
    //QObject::connect(_readwritesocket, SIGNAL(readyRead()), this, SLOT(ReceiveMessage()));
    //QObject::connect(this, SIGNAL(Received(User*)), this, SLOT(DealWithMessage(User*)));
}

MyClient::~MyClient()
{
    //delete _user;
}

void MyClient::SetIP(const QString &hostip)
{
    HostIP = hostip;
}


void MyClient::SetPath(const QString &path)
{
    KeepPath = path;
}

void MyClient::SetupConnection()
{
	_readwritesocket->connectToHost(HostIP, 8888);
    _readwritesocket->waitForConnected(2000);
	if (_readwritesocket->ConnectedState != QTcpSocket::ConnectedState)
	{
		qDebug() << "Failed to connect to server";
		return ;
	}
    QObject::connect(_readwritesocket, SIGNAL(readyRead()), this, SLOT(ReceiveMessage()));
    QObject::connect(this, SIGNAL(Received(User * )), this, SLOT(DealWithMessage(User * )));
}

void MyClient::DealWithMessage(User * user)
{
    qDebug() << "DealWithHere!";
    switch (user->_servertype)
    {
        case PHOTOS:
            SavePhotos(user);
            break;
        case LOG:
            SaveLog(user);
            break;
        case POINTS:
            UpdatePoints(user);
            break;
        default:
            break;
    }
}

void MyClient::ReceiveMessage()
{
    qDebug() << "Receiving!";
    qDebug() << _readwritesocket->bytesAvailable();
    if (totalBytes == 0 && _readwritesocket->bytesAvailable() >= sizeof(qint64))
    {
        QDataStream in(_readwritesocket);
        in.setVersion(QDataStream::Qt_4_6);
        in >> totalBytes;
    }

    if (BytesReceived < totalBytes)
    {
        BytesReceived += _readwritesocket->bytesAvailable();
        QByteArray tempArray = _readwritesocket->readAll();
        inArray.append(tempArray);
        if (BytesReceived == totalBytes)
        {
            totalBytes = 0;
            BytesReceived = 0;
            QDataStream in(&inArray, QIODevice::ReadOnly);
            in.setVersion(QDataStream::Qt_4_6);
            User * _user = new User;
            in >> (*_user);
            inArray.resize(0);
            emit Received(_user);
        }
    }
}


void MyClient::SavePhotos(User * user)
{
    qDebug() << "clientnetwork::SavePhotos";
    QFile *file = new QFile(KeepPath + "config.json");
    if (!file->open(QFile::ReadWrite))
    {
        qDebug() << "Open Config File Error in SavePhotos!";
        return;
    }

    QList<QString> filepaths;

    QByteArray JsonArray = file->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(JsonArray);
    QJsonObject object = doc.object();

    //QJsonObject object;
    for (int i = 0; i < user->_groupnum; i++)
    {
        QJsonObject inobj;
        QString Prefix = KeepPath + user->_groups.at(i)._date;
        qDebug() << Prefix;

        QDir *dir = new QDir;//若没有路径则新建目录！
        if (!dir->exists(Prefix))
        {
            dir->mkdir(Prefix);
        }
        delete dir;

        for (int j = 0; j < user->_groups.at(i)._photonum; j++)
        {
            QJsonObject inobj2;
            //inobj2.insert("uploader", user->_groups.at(i)._photos.at(j)._uploader);
            _map.insert(user->_groups.at(i)._date + user->_groups.at(i)._photos.at(j)._title, user->_groups.at(i)._photos.at(j)._points);
            inobj2.insert("points", user->_groups.at(i)._photos.at(j)._points);
            //inobj2.insert("type", "small");
            inobj2.insert("width", user->_groups.at(i)._photos.at(j)._size.width());
            inobj2.insert("height", user->_groups.at(i)._photos.at(j)._size.height());
            QString Locate = Prefix + "/" + user->_groups.at(i)._photos.at(j)._title;
            filepaths.append(Locate);
            qDebug() << Locate;
            if (!user->_groups.at(i)._photos.at(j)._photo.save(Locate, 0, 100))
                qDebug() << "Save Photos Error!";
            inobj.insert(user->_groups.at(i)._photos.at(j)._title, inobj2);
        }

        object.insert(user->_groups.at(i)._date, inobj);
    }
    delete user;

    //QJsonDocument doc(object);
    //QByteArray jsonArray = doc.toJson();
    //file->write(jsonArray);
    //file->close();
    doc.setObject(object);
    JsonArray.resize(0);
    JsonArray = doc.toJson();
    file->seek(0);
    file->write(JsonArray);
    file->close();

    emit PhotosSaved(filepaths);
}

void MyClient::SaveLog(User * user)
{
    qDebug() << "SaveLogHere!";
    QFile *logfile = new QFile(KeepPath + "Log.txt");
    if (!logfile->open(QFile::WriteOnly))
    {
        qDebug() << "Open LogFile Error!";
        return;
    }
    logfile->write(user->_log.toLatin1());
    logfile->close();

    emit LogSaved();
}

void MyClient::UpdatePoints(User * user)
{
    qDebug() << "UpdatePointsHere!";
    QFile *pointsfile = new QFile(KeepPath + "config.json");
    if (!pointsfile->open(QFile::ReadWrite))
    {
        qDebug() << "Open Config File Error in UpdatePoints!";
        return;
    }
    QByteArray pointsArray = pointsfile->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(pointsArray);

    if (doc.isObject())
    {
        qDebug() << "isObject!";
    }

    QJsonObject obj = doc.object();

    for (int i = 0; i < user->_groupnum; i++)
    {
        for (int j = 0; j < user->_groups.at(i)._photonum; j++)
        {
            //obj[user->_groups.at(i)._date][user->_groups.at(i)._photos.at(j)._title]
            QJsonObject date = obj[user->_groups.at(i)._date].toObject();
            QJsonObject title = date[user->_groups.at(i)._photos.at(j)._title].toObject();
            _map.insert(user->_groups.at(i)._date + user->_groups.at(i)._photos.at(j)._title, user->_groups.at(i)._photos.at(j)._points);
            title["points"] = user->_groups.at(i)._photos.at(j)._points;
            date.insert(user->_groups.at(i)._photos.at(j)._title, title);
            obj.insert(user->_groups.at(i)._date, date);
        }
    }

    doc.setObject(obj);
    pointsArray.resize(0);
    pointsArray = doc.toJson();
    pointsfile->seek(0);
    pointsfile->write(pointsArray);
    pointsfile->close();

    emit PointsUpdated();
}



//Client Operations!

void MyClient::LogIn(const QString &username)
{
    QFile *file = new QFile(KeepPath + "config.json");
    if(!file->open(QFile::ReadWrite))
    {
        qDebug()<<"Open Config File Error in LogIn!";
        return;
    }

    QByteArray JsonArray = file->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(JsonArray);
    QJsonObject object = doc.object();

    User user;
    user._clienttype = LOGIN;
    //user._config = file->readAll();
    user._username = username;
    user._datetime = QDateTime::currentDateTime();//.toString(Qt::ISODate);
    UserName = username;

    file->close();

    if(!object.isEmpty())
    {
        QStringList dates = object.keys();
        user._groupnum = dates.size();
        for(int i = 0; i < user._groupnum; i++)
        {
            Group group;
            group._date = dates.at(i);
            QJsonObject dateobj = object[dates.at(i)].toObject();
            QStringList photos = dateobj.keys();
            group._photonum = photos.size();
            for(int j = 0; j < group._photonum; j++)
            {
                QJsonObject photoobj = dateobj[photos.at(j)].toObject();
                _map.insert(group._date + photos.at(j), photoobj["points"].toDouble());
                group._photos.append(Photo(photos.at(j)));
            }
            user._groups.append(group);
        }
    }

    QByteArray BtArray;
    QDataStream out(&BtArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out<<(qint64)0;
    out<<user;
    out.device()->seek(0);
    out<<(qint64)(BtArray.size() - sizeof(qint64));
    qDebug()<<BtArray.size();
    qint64 temp = _readwritesocket->write(BtArray);
    qDebug()<<temp;
}


void MyClient::LogOut()
{
    User user;
    user._clienttype = LOGOUT;
    user._datetime = QDateTime::currentDateTime();//.toString(Qt::ISODate);
    user._username = UserName;

    QByteArray outArray;
    QDataStream out(&outArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out << (qint64) 0;
    out << user;
    out.device()->seek(0);
    out << (qint64) (outArray.size() - sizeof(qint64));

    qint64 temp = _readwritesocket->write(outArray);


    _readwritesocket->waitForBytesWritten();
    _readwritesocket->disconnectFromHost();
    if (_readwritesocket->state() == QAbstractSocket::UnconnectedState ||
        _readwritesocket->waitForDisconnected(2000))
        qDebug() << "Disconnected";


}


void MyClient::AskforLog()
{
    //QFile *file = new QFile(KeepPath + "config.json");
    //if(!file->open(QFile::ReadOnly))
    //{
    //qDebug()<<"Open Config File Error in AskforLog!";
    //return;
    //}
    User user;
    user._clienttype = FORLOG;
    user._username = UserName;
    user._datetime = QDateTime::currentDateTime();
    //user._config = file->readAll();

    QByteArray BtArray;
    QDataStream out(&BtArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out << (qint64) 0;
    out << user;
    out.device()->seek(0);
    out << (qint64) (BtArray.size() - sizeof(qint64));

    qint64 temp = _readwritesocket->write(BtArray);


    //file->close();
}


void MyClient::UploadSinglePhoto(const QString &photopath)
{
	qDebug() << "clientnetwork::UploadSinglePhoto " << photopath;
    QString date = QDate::currentDate().toString(Qt::ISODate);
    QString title = QFileInfo(photopath).fileName();
    QImage image(photopath);

    QList<QString> filepaths;

    User user;
    user._clienttype = ADD;
    user._groupnum = 1;
    user._username = UserName;
    user._datetime = QDateTime::currentDateTime();//.toString(Qt::ISODate);
    Group group;
    group._photonum = 1;
    group._date = QDate::currentDate().toString(Qt::ISODate);
    group._photos.append(Photo(image,title,image.size(),0));
    user._groups.append(group);

    QByteArray outArray;
    QDataStream out(&outArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out << (qint64) 0;
    out << user;
    out.device()->seek(0);
    out << (qint64) (outArray.size() - sizeof(qint64));
    qint64 temp = _readwritesocket->write(outArray);

    QDir *dir = new QDir;
    if (!dir->exists(KeepPath + date))
    {
        qDebug() << "mkdir" + KeepPath + date;
        dir->mkdir(KeepPath + date);
    }
    delete dir;
    QFile::copy(photopath, KeepPath + date + "/" + title);//Copy 照片 到本地
    filepaths.append(KeepPath + date + "/" + title);
    _map.insert(date + title, 0);

    QFile *file = new QFile(KeepPath + "config.json");
    if (!file->open(QFile::ReadWrite))
    {
        qDebug() << "Open Config File Error in UploadOnePhoto!";
        return;
    }

    QByteArray array = file->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(array);
    QJsonObject object = doc.object();

    if(object.contains(date))
    {
        QJsonObject dateobj = object[date].toObject();
        QJsonObject photoobj;
        //photoobj.insert("uploader", UserName);
        photoobj.insert("points", 0);
        photoobj.insert("width", image.width());
        photoobj.insert("height", image.height());
        dateobj.insert(title, photoobj);
        object.insert(date, dateobj);
    }
    else
    {
        QJsonObject dateobj;
        QJsonObject photoobj;
        //photoobj.insert("uploader", UserName);
        photoobj.insert("points", 0);
        //photoobj.insert("type", "big");
        photoobj.insert("width", image.width());
        photoobj.insert("height", image.height());
        dateobj.insert(title, photoobj);
        object.insert(date, dateobj);
    }

    doc.setObject(object);
    array.resize(0);
    array = doc.toJson();
    file->seek(0);
    file->write(array);
    file->close();

    emit PhotosSaved(filepaths);
}

void MyClient::ScorePhoto(const QString &date, const QString &title, double points)
{
	qDebug() << "clientnetwork::ScorePhoto " << date << "/" << title << " " << points;

	User user;
    user._clienttype = EVAL;
    user._groupnum = 1;
    user._username = UserName;
    user._datetime = QDateTime::currentDateTime();
    Group group;
    group._date = date;
    group._photonum = 1;
    group._photos.append(Photo(title, points));
    user._groups.append(group);

    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out << (qint64) 0;
    out << user;
    out.device()->seek(0);
    out << (qint64) (array.size() - sizeof(qint64));
    qDebug() << array.size();
    qint64 temp = _readwritesocket->write(array);
    qDebug() << temp;

    /*QFile *file = new QFile(KeepPath + "config.json");
    if(!file->open(QFile::ReadWrite))
    {
        qDebug()<<"Open Config File Error in EvalPhoto!";
        return;
    }

    QByteArray JsonArray = file->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(JsonArray);
    QJsonObject object = doc.object();

    QJsonObject dateobj = object[date].toObject();
    QJsonObject photoobj = dateobj[title].toObject();
    photoobj["points"] += points;
    dateobj.insert(title, photoobj);
    object.insert(date, dateobj);

    doc.setObject(object);
    JsonArray.resize(0);
    JsonArray = doc.toJson();
    file->seek(0);
    file->write(JsonArray);
    file->close();*/
}


void MyClient::AskforBigPhoto(const QString &date, const QString &title)
{
    User user;
    user._clienttype = FORBIG;
    user._username = UserName;
    user._datetime = QDateTime::currentDateTime();//.toString(Qt::ISODate);
    user._groupnum = 1;
    Group group;
    group._photonum = 1;
    group._date = date;
    group._photos.append(Photo(title));
    user._groups.append(group);

    QByteArray outArray;
    QDataStream out(&outArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out<<(qint64)0;
    out<<user;
    out.device()->seek(0);
    out<<(qint64)(outArray.size() - sizeof(qint64));

    qint64 temp = _readwritesocket->write(outArray);
}

QSize MyClient::AskforOneSize(const QString &date, const QString &title)
{
    QFile *file = new QFile(KeepPath + "config.json");
    if(!file->open(QFile::ReadOnly))
    {
        qDebug()<<"Open Config Error in AskforOneSize!";
        return QSize();
    }
    QByteArray JsonArray;
    JsonArray = file->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(JsonArray);
    QJsonObject object = doc.object();
    file->close();

    QSize size;
    QJsonObject dateobj = object[date].toObject();
    QJsonObject photoobj = dateobj[title].toObject();
    size.setHeight(photoobj["height"].toInt());
    size.setWidth(photoobj["width"].toInt());
    return size;
}

double MyClient::AskforOnePoints(const QString &date, const QString &title)
{
    /*QFile *file = new QFile(KeepPath + "config.json");
    if(!file->open(QFile::ReadOnly))
    {
        qDebug()<<"Open Config Error in AskforOnePoints!";
        return -1;
    }
    QByteArray JsonArray;
    JsonArray = file->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(JsonArray);
    QJsonObject object = doc.object();
    file->close();

    //QSize size;
    QJsonObject dateobj = object[date].toObject();
    QJsonObject photoobj = dateobj[title].toObject();
    //size.setHeight(photoobj["height"]);
    //size.setWidth(photoobj["width"]);
    return photoobj["points"].toDouble();*/

    return _map.value(date + title);
}

}