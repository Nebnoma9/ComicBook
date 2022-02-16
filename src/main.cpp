#include <QQmlApplicationEngine>
#include <QGuiApplication>

#include <iostream>
#include <archive.h>
#include <archive_entry.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include <opencv2/opencv.hpp>

#include "chargerimagecache.h"
#include "TraitementImage.h"
#include "ArchiveExtraction.h"
#include "Archives.h"
#include "cache.hpp"
#include "ParametresChargementImage.h"
#include "FournisseurImage.h"

bool PageActuelleModifiee;
bool CheminArchiveChange;
bool PrechargementEnCours;
int NbrTotalPages;
std::string CheminGlobalArchive;
ParametresPage ParametresChargement;

std::mutex PrechargementMutex;
std::condition_variable EtatPrechargement;
bool SortirProgramme;
bool PathSet;


QCache<int,DonneeImage> CacheImage;
QReadWriteLock VerrouillerCache;



int main(int argc, char *argv[])
{


 QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);


 QGuiApplication app(argc, argv);
 QQmlApplicationEngine engine;

  PathSet = false;
  qRegisterMetaType<ParametresPage>("ImagePreloadParams");

 ImgProvider *imgProvider= new ImgProvider();
 engine.addImageProvider(QStringLiteral("myimg"), imgProvider);


 engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

 if (engine.rootObjects().isEmpty())
     return -1;

imgProvider->setRootObject(engine.rootObjects().first());

QObject* fileDiag_ptr = engine.rootObjects().first()->findChild<QObject*>("FileDialog");
QObject::connect(fileDiag_ptr,SIGNAL(setFilePathSignal(QString)),imgProvider,SLOT(filePathSlot(QString)));


 return app.exec();
}
