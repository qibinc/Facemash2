#ifndef MYSERVER_H
#define MYSERVER_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include "data.h"
#include <QFile>

namespace dyh
{
class MyServer : public QObject
{
    Q_OBJECT

private:
    QTcpServer* _server;
    //QTcpSocket* _readwritesocket;
    //QList<QTcpSocket*> _readwritesockets;
    //QList<qintptr> _socketdescriptors;
    //QList<QString> _UserNames;
    QMap<QString,QTcpSocket*> _map;

    //QString KeepPath;
    //QFile* LocalFile;

    qint64 totalBytes;
    qint64 BytesReceived;
    QByteArray inArray;

signals:
    void GetMessageFromClient(dyh::User*);


private slots:
    void GetConnection();
    void KeepMessage();
    //void SendMessage();
    //void SendPoints();

public:
    explicit MyServer(QObject *parent = 0);
    ~MyServer();

    void PassAllPhotos(const QString& username, qint32 groupnum, const QList<qint32>& photonums, const QList<QString>& dates,
                       const QList<QImage>& images, const QList<QSize>& sizes, const QList<QString>& titles,
                       const QList<double>& points);   //传照片（可单张也可多张）
    //void PassOnePhoto(const QString& date, const QString& filepath, const QString& title,
                      //const QString& uploader, const double& points);  //传某张照片
    void PassUserLog(const QString& username, const QString& log);  //传用户日志

    void UpdatePoints(const QString& username, qint32 groupnum, const QList<qint32>& photonums, const QList<QString>& dates,
                      const QList<QString>& titles, const QList<double>& points);//更新分数

    //void SetPath(const QString& path);//设置缓存文件保存路径
};
}
#endif // MYSERVER_H
