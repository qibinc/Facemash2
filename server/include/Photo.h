//
// Created by ivanium on 2017/5/23.
//

#ifndef FACEMASH2_PHOTO_H
#define FACEMASH2_PHOTO_H

#include <QImage>
#include <QString>

namespace server {

enum ImageType{
    FullImage,
    Thumbnail
};

class Photo {
private:
    QString _fileName;
    QString _fileLocation;

    int judgeTime;
    int totalScore;
    QImage _fullImage, _thumbnail;

    void resize();
public:

    Photo(QString fileName, QImage *image = NULL);

    const QString &getFileName() const { return _fileName; }
    const QString &getFileLocation() const { return _fileLocation; }
    const int getTotalScore() const { return totalScore; }
    const int getTotalJudge() const { return judgeTime;  }
    const QImage *getFullImage() const { return &_fullImage; }
    const QImage *getThumbnail() const { return &_thumbnail; }

    void addScore (int score , bool isJudging);

    void setImage (const QImage &image);
};

class Group{
private:
    QString _groupName;
    QList<server::Photo> _album;
public:
    Group(QString groupname, QList<server::Photo> *album):
            _groupName(groupname), _album(*album){};
    const QString &getGroupName () const { return _groupName; }
    const int getPhotosNum() const { return _album.length(); }
//    void setGroupName (const QString &_groupName) { Group::_groupName = _groupName; }

    QList<server::Photo> &getAlbum() { return _album; };
    const QList<QImage> getImages(ImageType type) const;
    const QList<QSize> getSizes() const;
    const QList<QString> getNames() const;
    const QList<double> getScores() const;
    QList<Photo>::iterator search(QString filename);

    void sortPhoto(bool (*compare)(Photo &, Photo &));
};

class SimplePhoto{
private:
    QString _filename;
    QImage _image;
    QSize _size;
    double _score;
public:
    double getScore () const { return _score; }
    const QString &getFilename () const { return _filename; }
    const QImage &getImage () const { return _image; }
    const QSize &getSize() const { return  _size; }
    SimplePhoto(QString filename, const QImage *image, QSize size, double score):
            _filename(filename), _image(*image), _size(size), _score(score){}
};

class SimpleGroup{
private:
    QString _groupname;
    QList<SimplePhoto> _album;
public:
    SimpleGroup(QString groupname, QList<SimplePhoto> *album):
    _groupname(groupname), _album(*album){}
    const QString &getGroupName () const { return _groupname; }
    const int getPhotosNum() const { return _album.length(); }
    const QList<QImage> getImages() const;
    const QList<QSize> getSizes() const;
    const QList<QString> getNames() const;
    const QList<double> getScores() const;
};
}


#endif //FACEMASH2_PHOTO_H
