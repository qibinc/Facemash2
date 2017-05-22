//
// Created by ivanium on 2017/5/21.
//

#ifndef FACEMASH2_PHOTOSYSTEM_H
#define FACEMASH2_PHOTOSYSTEM_H

#include <string>
#include <QImage>
#include <vector>

#define minPhotoWidth 90
#define minPhotoHeight 160
#define defaultWidth 720
#define defaultHeight 1280

namespace Server {

    class Photo {
    private:
        std::string _fileName;
        std::string _fileLocation;
        int _PhotoID;
        int _totalScore;
        QImage *_image;

    public:
        Photo(std::string fileName, QImage *image, int PhotoID);

        std::string getFileName() const {
            return _fileName;
        }
        std::string getFileLocation() const {
            return _fileLocation;
        }
        int getPhotoID() const {
            return _PhotoID;
        }
        int getTotalScore() const {
            return _totalScore;
        }
        QImage* getImage() const {
            return _image;
        }
        void setTotalScore(int totalScore);
        void addScore(int score);

        QImage resize(int width = minPhotoWidth, int height = minPhotoHeight);
    };

    Photo::Photo(std::string fileName, QImage *image = NULL, int PhotoID = -1) :
            _fileName(fileName), _fileLocation(".\\" + _fileName), _PhotoID(PhotoID), _totalScore(0), _image(image){};

    void Photo::setTotalScore(int totalScore) {
        _totalScore = totalScore;
    }
    void Photo::addScore(int score) {
        _totalScore += score;
    }
    QImage Photo::resize(int width, int height) {
//        QImage newImage(_image->scaled(width, height));
//        return newImage;
        return _image->scaled(width, height);
    }

    class PhotoManager {
    public:
//    private:
        std::vector<Photo> _album;
        PhotoManager(){};
//        void updatePhoto(info clientInfo){};

        void addPhoto(Photo& photo) {
            _album.push_back(photo);
        };
        Photo PhotoResize(Photo &HDPhoto, int width = minPhotoWidth, int height = minPhotoHeight);
    };
    Photo PhotoManager::PhotoResize(Photo &HDPhoto, int width, int height) {
        std::string resizedPhotoName = "resized" + HDPhoto.getFileName();
        QImage resizedImage(HDPhoto.resize(width, height));
        Photo resizedPhoto(resizedPhotoName, &resizedImage);
        return resizedPhoto;
    }

}
#endif //FACEMASH2_PHOTOSYSTEM_H
