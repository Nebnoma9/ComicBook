#ifndef FOURNISSEURIMAGE_H
#define FOURNISSEURIMAGE_H
#include<QQuickImageProvider>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string.h>
#include <filesystem>
#include <QObject>
#include <QString>
#include <iostream>
#include <QCache>
#include "cache.hpp"
#include "ParametresChargementImage.h"

#include "TraitementImage.h"
#include "chargerimagecache.h"

extern bool PathSet;

class ImgProvider : public QQuickImageProvider
{
    Q_OBJECT
private:

    QObject *rootObjectPointeur;
    TraitementImage TraitementImg;
    std::thread ThreadChargement;
    ChargerImageCache ChargerDansCache;

public:
    ImgProvider();
    ~ImgProvider();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
    void setRootObject(QObject* Pointeur);
    QObject* getRootObject();
    void preChargerImage(int NumPage1);
    QImage ConvertirCvMatEnQimage(const cv::Mat * image1);
public slots:
    void filePathSlot(const QString &p);
};

#endif // FOURNISSEURIMAGE_H
