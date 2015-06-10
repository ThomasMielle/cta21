#ifndef CENTRESECOURS_H
#define CENTRESECOURS_H

#include <QWidget>

#include "engin.h"

class CentreSecours
{

public:
    CentreSecours(QString nom, int numero, QString adresse, int effectif);

    // Attributs
public:
    QString nom;
    int numero;
    QString adresse;
    QList<Engin> listeEngins;
    int effectif;


    // Fonctions
public:
    void ajouterEngin(Engin engin);
    void alerter(Engin engin, int armement);

};

#endif // CENTRESECOURS_H
