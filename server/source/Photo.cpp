//
// Created by ivanium on 2017/5/23.
//

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

}
