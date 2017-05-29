#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QtNetwork/QTcpSocket>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include "data.h"

class MyClient : public QObject
{
    Q_OBJECT

private:
    QTcpSocket* _readwritesocket;
    qint64 totalBytes;//总字节数
    qint64 BytesReceived;//已接收字节数

    QString KeepPath;//保存根目录
    //QFile *file;

    //User *_user;
    QByteArray inArray;

    QString UserName;
    //QString _password;

    QString HostIP;

    void SavePhotos(User *user);
    //void SaveBigPhoto(User *user);
    void SaveLog(User *user);
    void UpdatePoints(User *user);

private slots:
    void DealWithMessage(User *user);
    void ReceiveMessage();

signals:
    void Received(User*);
    void PhotosSaved(QList<QString>*);
    void LogSaved();
    void PointsUpdated();

public:
    explicit MyClient(QObject* parent = 0);
    ~MyClient();
    void SetPath(const QString& path);
    void SetIP(const QString& hostip);
    void SetupConnection();

    void EvalPhoto(const QString& date, const QString& title, double points);
    void LogIn(const QString& username);
    void LogOut();
    void AskforLog();
    void UploadOnePhoto(const QString& photopath);
    void AskforBigPhoto(const QString& date, const QString& title);

};

#endif // MYCLIENT_H
