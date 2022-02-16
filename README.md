Pour compiler ce programme, il faut utiliser Qt creator sur windows 10(64 bit) basé sur
Qt 6.2.2 avec le compilateur MSVC 2019 64bit.

Une fois que vous avez cet environnement, vous ouvrez alors le fichier .pro :

Nous utilisons dans ce programme la librairie openCV. Assurez vous de l'avoir installé 
et d'inclure dans le ComicBookReader.pro les librairies :
    -libopencv_core454.dll
    -libopencv_imgcodecs454.dll
    -libopencv_imgproc454.dll
    -libopencv_highgui454.dll
    -libopencv_features2d454.dll
    -libopencv_calib3d454.dll

Il faut également copier le fichier archive.dll de la librairie libarchive qui se 
trouve dans le dossier : ../libarchive/bin dans le même dossier que 
l'executable (ComicBookReader.exe) du projet.

Il y'a également quelques mudules qt qu'il faut rajouter dans le dossier qml qui 
se trouve là où vous avez installez qt. Ils se trouvent dans le dossier QTQuick.
Ce sont les modules/dossiers disponible,:
    Controls
    Styles
    Dialogs
Si cela ne marche pas, remplacez votre dossier QtQuick par celui contenu dans le dossier du projet.
