//
// Created by ivanium on 2017/5/23.
//

#include <QSettings>
#include "PhotoManager.h"
#include "Photo.h"

#define minPhotoWidth 100
#define minPhotoHeight 100

namespace server {

Photo::Photo (QString fileName , QImage *image) :
        _fileName(fileName) , _fileLocation(".\\" + fileName),
        totalScore(0) , judgeTime(0), _fullImage(*image) {
    resize();
};
//
//void Photo::setTotalScore(int totalScore) {
//    _totalScore = totalScore;
//}

void Photo::addScore (int score , bool isJudging) {
    totalScore += score;
    judgeTime += (isJudging ? 1:-1);
}

void Photo::resize () {
//    if(_fullImage){
    _thumbnail = QImage(_fullImage.scaled(minPhotoWidth , minPhotoHeight, Qt::KeepAspectRatio));
//    }
}

void Photo::setImage (const QImage &image) {
    _fullImage = image;
    resize();
}


void Group::sortPhoto(bool (*compare)(server::Photo &, server::Photo &)) {
    std::sort(_album.begin(), _album.end(), compare);
}

QList<Photo>::iterator Group::search (QString filename) {
    for (QList<Photo>::iterator i = _album.begin(); i != _album.end(); ++i) {
        if((*i).getFileName() == filename){
            return i;
        }
    }
    return _album.end();
}

const QList<QImage> Group::getImages (ImageType type) const {
    QList<QImage> images;
    if(type == FullImage) {
        for (QList<Photo>::const_iterator iter = _album.begin(); iter != _album.end(); ++iter) {
            images.append(*((*iter).getFullImage()));
        }
    }
    else if(type == Thumbnail) {
        for (QList<Photo>::const_iterator iter = _album.begin(); iter != _album.end(); ++iter) {
            images.append(*((*iter).getThumbnail()));
        }
    }
    return images;
}

const QList<QString> Group::getNames () const {
    QList<QString> names;
    for (QList<Photo>::const_iterator iter = _album.begin(); iter != _album.end(); ++iter) {
        names.append((*iter).getFileName());
    }
    return names;
}

const QList<double> Group::getScores () const {
    QList<double> scores;
    for (QList<Photo>::const_iterator iter = _album.begin(); iter != _album.end(); ++iter) {
        scores.append((double)(*iter).getTotalScore()/(*iter).getTotalJudge());
    }
    return scores;
}

const QList<QSize> Group::getSizes () const {
    QList<QSize> sizes;
    for (QList<Photo>::const_iterator iter = _album.begin(); iter != _album.end(); ++iter) {
        sizes.append(iter->getFullImage()->size());
    }
    return sizes;
}


const QList<QImage> SimpleGroup::getImages () const {
    QList<QImage> images;
    for (QList<SimplePhoto>::const_iterator iter = _album.begin(); iter != _album.end(); ++iter) {
        images.append((*iter).getImage());
    }
    return images;
}

const QList<QSize> SimpleGroup::getSizes () const {
    QList<QSize> sizes;
    for (QList<SimplePhoto>::const_iterator iter = _album.begin(); iter != _album.end(); ++iter) {
        sizes.append(iter->getImage().size());
    }
    return sizes;
}

const QList<QString> SimpleGroup::getNames () const {
    QList<QString> names;
    for (QList<SimplePhoto>::const_iterator iter = _album.begin(); iter != _album.end(); ++iter) {
        names.append(iter->getFilename());
    }
    return names;
}

const QList<double> SimpleGroup::getScores () const {
    QList<double> scores;
    for (QList<SimplePhoto>::const_iterator iter = _album.begin(); iter != _album.end(); ++iter) {
        scores.append(iter->getScore());
    }
    return scores;
}
}
