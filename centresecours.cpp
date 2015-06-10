#include "centresecours.h"

CentreSecours::CentreSecours(QString nom, int numero, QString adresse, int effectif)
{
    this->nom = nom;
    this->numero = numero;
    this->adresse = adresse;
    this->effectif = effectif;
}

void CentreSecours::ajouterEngin(Engin engin)
{
    this->listeEngins << engin;
}
