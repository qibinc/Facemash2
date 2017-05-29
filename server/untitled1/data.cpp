#include "data.h"

Photo::Photo()
{

}

Photo::Photo(const QString &title):
    _title(title)
{

}

Photo::Photo(const QString &title, double points):
    _title(title), _points(points)
{

}

Photo::Photo(const QImage &photo, const QString &title, const QString &uploader, const QSize& size, double points):
    _photo(photo), _title(title), _uploader(uploader), _size(size), _points(points)
{

}

QDataStream &operator<<(QDataStream & out, const Photo& photo)
{
    out<<photo._photo;
    out<<photo._title;
    out<<photo._uploader;
    out<<photo._size;
    out<<photo._points;
    return out;
}

QDataStream &operator>>(QDataStream& in, Photo& photo)
{
    in>>photo._photo;
    in>>photo._title;
    in>>photo._uploader;
    in>>photo._size;
    in>>photo._points;
    return in;
}


Group::Group()
{

}


QDataStream &operator<<(QDataStream & out, const Group& group)
{
    out<<group._date;
    out<<group._photonum;
    out<<group._photos;
    return out;
}

QDataStream &operator>>(QDataStream & in, Group& group)
{
    in>>group._date;
    in>>group._photonum;
    in>>group._photos;
    return in;
}


User::User():
    _clienttype(DEFAULTc),_servertype(DEFAULTs)
{

}

QDataStream &operator <<(QDataStream & out, const User& user)
{
    out<<user._username;
    //out<<user._password;
    out<<user._datetime;
    out<<(qint32)user._clienttype;
    out<<(qint32)user._servertype;
    out<<user._log;
    out<<user._groupnum;
    out<<user._groups;
    out<<user._config;
    return out;
}

QDataStream &operator >>(QDataStream &in, User& user)
{
    in>>user._username;
    //in>>user._password;
    in>>user._datetime;
    in>>(qint32&)user._clienttype;
    in>>(qint32&)user._servertype;
    in>>user._log;
    in>>user._groupnum;
    in>>user._groups;
    in>>user._config;
    return in;
}
