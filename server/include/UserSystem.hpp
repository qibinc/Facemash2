//
// Created by ivanium on 2017/5/21.
//

#ifndef FACEMASH2_USERSYSTEM_H
#define FACEMASH2_USERSYSTEM_H

#include <string>
#include <vector>
#include <time.h>

class Date{
private:
    int _year, _month, _date, _hour, _minute, _second;

public:
    int getYear();
    int getMonth();
    int getDay();
    int getTime();
    string getStrTime();

};//todo finish date adapter

enum Operation{
    nullOperation, createAccount, modifyNickname, modifyPassword, uploadPhoto, downloadPhoto, scorePhoto, cancelScorePhoto
};

class Event{
private:
    Operation _opt;
    Date _date;
public:
    Event(Operarion = nullOperation, Date date){
        _opt = Operation;
        _date = date;
    };
    const Operation getOperation() {
        return _opt;
    };
    const Date getDate() {
        return _date;
    }
};

class UserLog{

};

class User{
private:
    string _nickname;
    string _ID, _password;
    UserLog _log;

public:
    User(string ID, string password, string nickname = "");
    ~User(){};
    bool passwordCheck(string password);

};

#endif //FACEMASH2_USERSYSTEM_H
