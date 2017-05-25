//
// Created by ivanium on 2017/5/24.
//

#include "User.h"
#include <QDebug>
namespace server {

    const QString Date::getStrFullTime () const {
        QString time(
                QString("%1.%2.%3 %4:%5:%6").arg(_year).arg(_month).arg(_date).arg(_hour).arg(_minute).arg(_second));
        return time;
    }

    const QString Date::getStrTime () const {
        QString time(
                QString("%1.%2.%3").arg(_year).arg(_month).arg(_date)
        );
        return time;
    }

    void UserLog::addEvent (Event *event) {
        log.append(*event);
    }

    const QList<Event> *UserLog::getLog() const {
        return &log;
    }

    void User::changeNickname (Date date , QString newNickname) {
        _nickname = newNickname;
        Event event(date , Operation::changeNickname , newNickname);
        _log.addEvent(&event);
    }

    void User::changePassword (Date date , QString newPassword) {
        _password = newPassword;
        Event event(date , Operation::changePassword , newPassword);
        _log.addEvent(&event);
    }

    bool User::login (Date date , QString password) {
        if (passwordCheck(password)) {
            online = true;
            Event event(date , Operation::login , password);
            _log.addEvent(&event);
        } else {
            online = false;
            Event event(date , pwError , password);
            _log.addEvent(&event);
        }
        return online;
    }

    void User::logout (Date date) {
        online = false;
        Event event(date , Operation::logout);
        _log.addEvent(&event);
    }

    void User::upload (Date date , QString filename) {
        Event event(date , uploadPhoto , filename);
        _log.addEvent(&event);
    }

    void User::download (Date date , QString filename) {
        Event event(date , downloadPhoto , filename);
        _log.addEvent(&event);
    }

    void User::judge (Date date , QString filename) {
        totalJudge += 1;
        Event event(date , judgePhoto , filename);
        _log.addEvent(&event);
    }

    void User::unjudge (Date date , QString filename) {
        totalJudge -= 1;
        Event event(date , unjudgePhoto , filename);
        _log.addEvent(&event);
    }

    const QList<Event> *User::getLog () const {
        return _log.getLog();
    }
}
