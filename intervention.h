#ifndef INTERVENTION_H
#define INTERVENTION_H

#include <QWidget>

class Intervention
{
public:
    Intervention(int numero, QString type, QString lieu, QString desc);

    // Attributs
public:
    int numero;
    QString type;
    QString lieu;
    QString desc;

    // Fonctions
public:

};

#endif // INTERVENTION_H
