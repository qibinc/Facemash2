#ifndef MYSERVER_H
#define MYSERVER_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include "data.h"
#include <QFile>

class MyServer : public QObject
{
    Q_OBJECT

private:
    QTcpServer* _server;
    QTcpSocket* _readwritesocket;

    QString KeepPath;
    QFile* LocalFile;

    qint64 totalBytes;
    qint64 BytesReceived;

    QByteArray inArray;

signals:
    GetMessageFromClient();//保存到缓存文件中后发出信号


private slots:
    void GetConnection();
    void KeepMessage();
    void SendMessage();
    void SendPoints();

public:
    explicit MyServer(QObject *parent = 0);
    ~MyServer();

    void PassAllPhotos(qint32 groupnum, const QList<qint32>& photonums, const QList<QString>& dates,
                       const QList<QString>& filepaths, const QList<QString>& titles,
                       const QList<QString>& uploaders, const QList<double>& points);   //传照片（可单张也可多张）
    //void PassOnePhoto(const QString& date, const QString& filepath, const QString& title,
                      //const QString& uploader, const double& points);  //传某张照片
    void PassUserLog(const QString& username, const QString& log);  //传用户日志

    void UpdatePoints(qint32 groupnum, const QList<qint32>& photonums, const QList<QString>& dates,
                      const QList<QString>& titles, const QList<double>& points);//更新分数

    void SetPath(const QString& path);//设置缓存文件保存路径
};

#endif // MYSERVER_H
