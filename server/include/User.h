//
// Created by ivanium on 2017/5/21.
//

#ifndef FACEMASH2_USER_H
#define FACEMASH2_USER_H

#include <QString>
#include <QList>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlDatabase>

#include <time.h>

namespace server {
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setHostName("localhost");    //数据库主机名
//    db.setDatabaseName("UserSystem");    //数据库名
//    db.setUserName("ivanium");        //数据库用户名
//    db.setPassword("123456");        //数据库密码
//    db.open();          //打开数据库连接
//    db.close();         //释放数据库连接

class Date {
private:
    int _year, _month, _date, _hour, _minute, _second;
public:
    Date(int year = 2017, int month = 5, int date = 1, int s = 0, int min = 0, int h = 0):
            _year(year), _month(month), _date(date), _hour(h), _minute(min), _second(s)
    {};

    const int getYear () const { return _year; };
    const int getMonth () const { return _month; };
    const int getDay () const { return _date; };
    const int getSecond () const { return _hour * 3600 + _minute * 60 + _second; };

    const QString getStrFullTime () const;
    const QString getStrTime() const;

};

enum Operation {
    nullOperation,
    createAccount,
    changeNickname,
    changePassword,
    login,
    pwError,
    logout,
    uploadPhoto,
    downloadPhoto,
    judgePhoto,
    unjudgePhoto
};

class Event {
private:
    QString _userName;
    Operation _opt;
    QString _object;
    Date _date;
public:
    Event (Date date, QString userName, Operation opt = nullOperation, QString object = QString::null) :
            _userName(userName), _opt(opt), _object(object), _date(date) {};

    const Operation getOperation () const { return _opt; };

    const QString getObject() const { return  _object; };

    const Date getDate () const { return _date; };

    const QString toQString () const;
};

class UserLog {
private:
    QList<Event> log;
public:
    void addEvent (Event *event);

    const QList<Event> *getLog () const;
};

//class UserManager;

class User {
private:
    QString _nickname;
    QString _ID;
    QString _password;
    int errorTime;
    bool online;

    int totalJudge;
    UserLog _log;
public:
    const QString &getNickname () const { return _nickname; }
    const QString &getPassword () const { return _password; }
    int getTotalJudge () const { return totalJudge; }

    User (Date createDate, QString ID, QString password = QString::null, QString nickname = QString::null):
    _ID(ID), _password(password), _nickname(nickname), errorTime(0), online(false), totalJudge(0)
    {
        Event event(createDate, this->getID(), createAccount, QString::null);
        _log.addEvent(&event);
    };

    bool passwordCheck (QString password) { return (_password == password); };

    const QString getID() const { return _ID; };
    const QList<QString> getLog () const;

    void changeNickname (Date date, QString newNickname);

    void changePassword (Date date, QString newPassword);
    bool login (Date date, QString password);

    void logout (Date date);
    void upload(Date date, QString filename);

    void download(Date date, QString filename);
    void judge (Date date , QString filename);

    void unjudge (Date date , QString filename);
};

}
#endif //FACEMASH2_USER_H
