#include "FournisseurImage.h"



ImgProvider::ImgProvider(): QQuickImageProvider(QQuickImageProvider::Image)
{//constructeur avec iniatilisation du thread pour préchargement en parallèle des pages
    PathSet = false;
    CheminArchiveChange = false;
    NbrTotalPages = 0;
    ThreadChargement = std::thread(&ChargerImageCache::ChagerParalleleImage, &ChargerDansCache);
    CacheImage.setMaxCost(100);
}
//------------------------------------------------------------------------------------------
ImgProvider::~ImgProvider(){
    SortirProgramme = true;
    CacheImage.clear();
    EtatPrechargement.notify_all();
    ThreadChargement.join();
}
//---------------------------------------------------------
void ImgProvider::preChargerImage(int NumPage1)
{//initaliser les paramètres de précharchement
    ParametresChargement.NumPageActuelle=NumPage1;
    ParametresChargement.NombrePagesGauches=3;
    ParametresChargement.NombrePagesDroites=3;
    ParametresChargement.TypePage=1;
    EtatPrechargement.notify_all();
}
//------------------------------------------------------------------------
QObject* ImgProvider::getRootObject()
{
    return rootObjectPointeur;
}
//------------------------------------------------------------
QImage ImgProvider::ConvertirCvMatEnQimage(const cv::Mat* image)
{
    return QImage((uchar*)image->data, image->cols, image->rows, image->step, QImage::Format_RGB888) ;
}
//-----------------------------------------------------------
QImage ImgProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    //fournir une nouvelle image au qml

    QStringList shape = id.split("/");
    int NumPage = shape[0].toInt();
    if(PathSet==false)
    {
        return QImage();
    }

    DonneeImage* imagePtr;
    VerrouillerCache.lockForRead();
    if(CacheImage.contains(NumPage))
    {
        imagePtr=CacheImage.object(NumPage);
        VerrouillerCache.unlock();
        preChargerImage(NumPage);
        return ConvertirCvMatEnQimage(imagePtr->PointeurImage);
    }
    else
    {
        VerrouillerCache.unlock();
        imagePtr= new DonneeImage;
        TraitementImg.TraiterImage(NumPage,1,*(imagePtr->PointeurImage));
        imagePtr->TypeImage=1;
        VerrouillerCache.lockForWrite();
        CacheImage.insert(NumPage,imagePtr);
        VerrouillerCache.unlock();
        preChargerImage(NumPage);
        return ConvertirCvMatEnQimage(imagePtr->PointeurImage);
    }


}
//-------------------------------------------------------------
void ImgProvider::filePathSlot(const QString &p)
{
    //recuperation du chemin de l'archive choisi
    QStringList listeChemin = p.split("///");
    CheminGlobalArchive = listeChemin[1].toStdString();

    //chargement
    TraitementImg.ChargerArchive(CheminGlobalArchive,0);
    TraitementImg.GetArchive()->LireArchive(CheminGlobalArchive);
    ChargerDansCache.SetTraitementImg(TraitementImg);

    VerrouillerCache.lockForWrite();
    CacheImage.clear();
    VerrouillerCache.unlock();

    PathSet = true;

    NbrTotalPages = TraitementImg.GetArchive()->GetNombreTotalePage();
    QObject* slidbar_ptr = rootObjectPointeur->findChild<QObject*>("SlideBar");
    slidbar_ptr->setProperty("to", NbrTotalPages-1);

    QObject* show_image_ptr = rootObjectPointeur->findChild<QObject*>("ShowImage");
    show_image_ptr->setProperty("pageNum", 0);

}


//------------------------------------------
void ImgProvider::setRootObject(QObject* Pointeur)
{
    //
    rootObjectPointeur = Pointeur;

    QObject* slidbar_ptr = rootObjectPointeur->findChild<QObject*>("SlideBar");
    slidbar_ptr->setProperty("to",0);
}
