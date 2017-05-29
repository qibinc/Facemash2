//
// Created by ivanium on 2017/5/24.
//

#include "User.h"

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
        qDebug()<<event->toQString();
    }

    const QList<Event> *UserLog::getLog () const {
        return &log;
    }

    void User::changeNickname (Date date , QString newNickname) {
        _nickname = newNickname;
        Event event(date , this->getID(), Operation::changeNickname , newNickname);
        _log.addEvent(&event);
    }

    void User::changePassword (Date date , QString newPassword) {
        _password = newPassword;
        Event event(date , this->getID(), Operation::changePassword , newPassword);
        _log.addEvent(&event);
    }

    bool User::login (Date date , QString password) {
        if (passwordCheck(password)) {
            if(!online){
                online = true;
                Event event(date , this->getID(), Operation::login , password);
                _log.addEvent(&event);
            }
            else {
                qDebug() << this->getID() + " is online";
                return false;
            }
        } else {
            online = false;
            Event event(date , this->getID(), pwError , password);
            _log.addEvent(&event);
        }
        return online;
    }

    void User::logout (Date date) {
        if(online){
            online = false;
            Event event(date , this->getID(), Operation::logout);
            _log.addEvent(&event);
        }
        else{
            qDebug()<<this->getID() + " is offline";
        }
    }

    void User::upload (Date date , QString filename) {
        Event event(date , this->getID(), uploadPhoto , filename);
        _log.addEvent(&event);
    }

    void User::download (Date date , QString filename) {
        Event event(date , this->getID(), downloadPhoto , filename);
        _log.addEvent(&event);
    }

    void User::judge (Date date , QString filename) {
        totalJudge += 1;
        Event event(date , this->getID(), judgePhoto , filename);
        _log.addEvent(&event);
    }

    void User::unjudge (Date date , QString filename) {
        totalJudge -= 1;
        Event event(date , this->getID(), unjudgePhoto , filename);
        _log.addEvent(&event);
    }

    const QList<QString> User::getLog () const {
        QList<QString> log;
        const QList<Event> *events = _log.getLog();
        for (QList<Event>::const_iterator ei = events->begin(); ei != events->end() ; ++ei) {
            log.append(ei->toQString());
        }
        return log;
    }

    const QString Event::toQString () const {
        QString str = _date.getStrFullTime() + ": " + _userName + " ";
        switch (_opt){
            case nullOperation:
                str = str + "nullOperation ";
                break;
            case createAccount:
                str = str + "createAccount ";
                break;
            case changeNickname:
                str = str + "changeNickname ";
                break;
            case changePassword:
                str = str + "changePassword ";
                break;
            case login:
                str = str + "login ";
                break;
            case pwError:
                str = str + "pwError ";
                break;
            case logout:
                str = str + "logout ";
                break;
            case uploadPhoto:
                str = str + "uploadPhoto ";
                break;
            case downloadPhoto:
                str = str + "downloadPhoto ";
                break;
            case judgePhoto:
                str = str + "judgePhoto ";
                break;
            case unjudgePhoto:
                str = str + "unjudgePhoto ";
                break;
            default: ;
        }
        str = str + _object;
        return str;
    }
}
