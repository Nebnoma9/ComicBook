#include "chargerimagecache.h"
#include"cache.hpp"
#include <QMutexLocker>

ChargerImageCache::ChargerImageCache()
{
    PageActuelleModifiee = false;
    PrechargementEnCours = false;
}
//---------------------------------------------------------------------------------------------------
ChargerImageCache::ChargerImageCache(Images& imageT)
{
    imageTraitement=&imageT;
    PageActuelleModifiee = false;
    PrechargementEnCours = false;
}
//-----------------------------------------------------------------------------------------------
Images* ChargerImageCache:: GetTraitementImg(){

    return imageTraitement;

}
//-----------------------------------------------------------------------------------------------
void ChargerImageCache::SetTraitementImg(Images& imageT)
 {
     imageTraitement=&imageT;
 }

//----------------------------------------------------------------------------------------------------

void ChargerImageCache::MettreImageDansCache(const int NumPage, const int TypePage)
{
    DonneeImage* ImagePointeur;

    VerrouillerCache.lockForRead();
    //Vérifier que l'image n'existe pas dans le cache
    if(CacheImage.contains(NumPage))
    {
        ImagePointeur = CacheImage.object(NumPage);
        if(ImagePointeur->TypeImage!=TypePage)
        {
            VerrouillerCache.unlock();
            VerrouillerCache.lockForWrite();
            CacheImage.remove(NumPage);
            VerrouillerCache.unlock();
        }
       else{
         VerrouillerCache.unlock();
        }

    }
    else {//Si l'image n'existe pas dans le cache
        VerrouillerCache.unlock();
        ImagePointeur = new DonneeImage;
         imageTraitement->TraiterImage(NumPage, TypePage,*(ImagePointeur->PointeurImage));
         ImagePointeur->TypeImage = TypePage;
          VerrouillerCache.lockForWrite();
          CacheImage.insert(NumPage,ImagePointeur);
         VerrouillerCache.unlock();
}
}

//----------------------------------------------------------------------------------
void ChargerImageCache::ChagerParalleleImage()
{

    while (1)
    {

        std::unique_lock <std::mutex> lck(PrechargementMutex);
        EtatPrechargement.wait(lck);

        if(SortirProgramme == true)
        {
            return;
        }
        if (CheminArchiveChange == true) {
            imageTraitement->ChargerArchive(CheminGlobalArchive,0);
            CheminArchiveChange = false;
        }
        PrechargementEnCours = true;

        bool GaucheDepasser = false;
        bool DroiteDepasser = false;
        int TypeImg = ParametresChargement.TypePage;
        int NumeroPageActuelle = ParametresChargement.NumPageActuelle;
        int NbrPagesGauche = ParametresChargement.NombrePagesGauches;
        int NbrPagesDroite = ParametresChargement.NombrePagesDroites;


        for (int i = 1; i <= qMax<int>(NbrPagesGauche, NbrPagesDroite); i++)
        {


            if (NumeroPageActuelle + i <= NbrTotalPages && i <= NbrPagesDroite)
            {
                MettreImageDansCache(NumeroPageActuelle + i, TypeImg);
            }
            else DroiteDepasser = true;

            if (NumeroPageActuelle - i >= 1 && i <= NbrPagesGauche)
            {
                MettreImageDansCache(NumeroPageActuelle - i, TypeImg);
            }
            else GaucheDepasser = true;

            if (GaucheDepasser == true && DroiteDepasser == true)
            {

                break;
            }

        }
        PrechargementEnCours = false;
    }
    return;


}

