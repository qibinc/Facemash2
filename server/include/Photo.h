//
// Created by ivanium on 2017/5/23.
//

#ifndef FACEMASH2_PHOTO_H
#define FACEMASH2_PHOTO_H

#include <QImage>

namespace server {

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

    const QImage *getFullImage() const { return &_fullImage; }
    const QImage *getThumbnail() const { return &_thumbnail; }

//    void setTotalScore (int totalScore);
    void addScore (int score , bool isJudging);

    void setImage (const QImage &image);
};

}


#endif //FACEMASH2_PHOTO_H
