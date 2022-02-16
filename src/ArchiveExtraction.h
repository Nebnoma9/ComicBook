#ifndef ARCHIVEEXTRACTION_H
#define ARCHIVEEXTRACTION_H
#include "Archives.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string.h>
#include <vector>


class ArchiveExtraction: public Archives
{
public:
    ArchiveExtraction():Archives(){};

    ~ArchiveExtraction();
    ArchiveExtraction( ArchiveExtraction& ar1);
    ArchiveExtraction(std::string path1);
    void SetNombreTotalPages(int nombre);

    bool ChargerImage(int numeroPage,cv::Mat& image);
    void Extract(const char *filename, int do_extract, int flags,int numPage);
    void LireArchive(std::string path);
    bool DecompresserArchive(int numPage,std::string ArchivePathName1);

};
#endif // ARCHIVEEXTRACTION_H

