#ifndef PARAMETRESCHARGEMENTIMAGE_H
#define PARAMETRESCHARGEMENTIMAGE_H
#include <QMetaType>
class ParametresPage
{

public:
    int NumPageActuelle;
    int NombrePagesGauches;
    int NombrePagesDroites;
    int TypePage;

    ParametresPage(int np, int npg, int npd, int tp){
        NumPageActuelle = np;
        NombrePagesGauches = npg;
        NombrePagesDroites = npd;
        TypePage = tp;
    }
    ParametresPage(){
        NumPageActuelle = 0;
        NombrePagesGauches = 0;
        NombrePagesDroites = 0;
        TypePage = 0;
    }
};
Q_DECLARE_METATYPE(ParametresPage);

#endif // PARAMETRESCHARGEMENTIMAGE_H
