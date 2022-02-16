#ifndef CHARGERIMAGECACHE_H
#define CHARGERIMAGECACHE_H
#include "TraitementImage.h"
#include "cache.hpp"
#include "ParametresChargementImage.h"
#include <mutex>
#include <thread>
#include<condition_variable>

extern bool PageActuelleModifiee;
extern bool CheminArchiveChange;
extern bool  PrechargementEnCours;
extern int NbrTotalPages;
extern std::string CheminGlobalArchive;
extern ParametresPage ParametresChargement;

extern std::mutex PrechargementMutex;
extern std::condition_variable EtatPrechargement;

extern bool SortirProgramme;


class ChargerImageCache
{
    Images* imageTraitement;
public:
    ChargerImageCache();
    ChargerImageCache(Images& imageT);
    void MettreImageDansCache(const int page_num, const int page_type);
    void ChagerParalleleImage();
    Images* GetTraitementImg();

    void SetTraitementImg(Images& imageT);

};

#endif // CHARGERIMAGECACHE_H
