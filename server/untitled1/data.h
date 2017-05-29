#ifndef DATA_H
#define DATA_H

#include <QImage>
#include <QString>

enum ClientType {DEFAULTc, LOGIN, LOGOUT, FORBIG, ADD, EVAL, FORLOG}; //用户的操作种类
enum ServerType {DEFAULTs, PHOTOS, LOG, POINTS}; //服务器的操作种类

struct Photo
{
    QImage _photo;
    QString _title;
    QString _uploader;
    QSize _size;
    double _points;
    Photo();
    Photo(const QString& title);
    Photo(const QString& title, double points);
    Photo(const QString& filepath, const QString& title, const QString& uploader, double points);
};

struct Group
{
    QString _date;
    qint32 _photonum;
    QList<Photo> _photos;
    Group();
};

struct User
{
    QString _username;
    QString _password;
    QString _datetime;
    ClientType _clienttype;
    ServerType _servertype;
    QList<Group> _groups;
    qint32 _groupnum;
    QString _log;
    QByteArray _config;
    User();
};

QDataStream &operator<<(QDataStream & out, const Photo& photo);
QDataStream &operator>>(QDataStream& in, Photo& photo);

QDataStream &operator<<(QDataStream & out, const Group& group);
QDataStream &operator>>(QDataStream & in, Group& group);

QDataStream &operator <<(QDataStream & out, const User& user);
QDataStream &operator >>(QDataStream &in, User& user);

#endif // DATA_H
