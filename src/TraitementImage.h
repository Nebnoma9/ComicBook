#ifndef TRAITEMENTIMAGE_H
#define TRAITEMENTIMAGE_H
#include "Image.h"
#include "ArchiveExtraction.h"
class TraitementImage: public Images
{
private:

    int nbrTotalePage;

public:
    TraitementImage();
    TraitementImage(Archives  & ar1);
    bool TraiterImage(int NumPage, int TypeImage, cv::Mat& Image);
    bool RedimensionnerImage(cv::Mat& ImageEntree, cv::Mat& ImageSortie, int TypeImage);
    bool ChargerArchive(std::string path,int Numeropage);
    int getNbrTotalPage(){return nbrTotalePage;}
    void SetArchiveParent(std::string path);
    TraitementImage &operator = (const TraitementImage &imageT );

};
#endif // TRAITEMENTIMAGE_H
