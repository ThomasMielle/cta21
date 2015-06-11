#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "formdepart.h"
#include "centresecours.h"
#include "engin.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Création de la google map /////////////////////////
    ui->webView->load(QUrl("http://maps.googleapis.com/maps/api/staticmap?center=Dijon,21000&zoom=12&size=641x289&maptype=roadmap"));

    // Conexion à la BDD /////////////////////////////////
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("../database/base.db");
    database.open();
    QSqlQuery query;

    // Création de tous les CS ///////////////////////////
    query.exec("SELECT nom, numero, adresse, effectif FROM centres ORDER BY numero");
    while (query.next()) {
        QString nom = query.record().value("nom").toString();
        int numero = query.record().value("numero").toInt();
        QString adresse = query.record().value("adresse").toString();
        int effectif = query.record().value("effectif").toInt();
        listeCS << CentreSecours(nom, numero, adresse, effectif);
    }
    ui->listEngins->setRowCount(listeCS.count());

    // Création de tous les engins ///////////////////////
    int nbEnginsMax = 0;
    for (int i = 0; i < listeCS.count(); i++) {
        query.prepare("SELECT e.nom, e.armementMin, e.armementMax FROM engins e, centres c WHERE (c.nom = :nomCentre) AND (c.numero = e.numeroCs) ORDER BY e.immatriculation");
        query.bindValue(":nomCentre",listeCS.at(i).nom);
        query.exec();
        int j = 0;
        while (query.next()) {
            j++;
            if (j > nbEnginsMax) {
                nbEnginsMax = j;
                ui->listEngins->setColumnCount(nbEnginsMax+1);
            }
            QString nom = query.record().value("nom").toString();
            int armementMin = query.record().value("armementMin").toInt();
            int armementMax = query.record().value("armementMax").toInt();
            listeCS.operator [](i).listeEngins << Engin(nom, armementMin, armementMax);
        }
    }

    // Affichage des CS et des engins /////////////////////
    for (int i = 0; i < listeCS.count(); i++) {
        QTableWidgetItem *centre = new QTableWidgetItem(listeCS.at(i).nom);
        centre->setTextAlignment(Qt::AlignCenter);
        ui->listEngins->setItem(i, 0, centre);
        for (int j = 0; j < listeCS.at(i).listeEngins.count(); j++) {
            QTableWidgetItem *engin = new QTableWidgetItem(listeCS.at(i).listeEngins.at(j).nom);
            engin->setTextAlignment(Qt::AlignCenter);
            engin->setBackgroundColor(QColor(65, 169, 46));
            engin->setTextColor(QColor(Qt::white));
            ui->listEngins->setItem(i, j+1, engin);
        }
    }

    // Fermeture de la base //////////////////////////////
    database.close();

    // Lancement d'un nouvel appel
    nouvelAppel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listEngins_itemClicked(QTableWidgetItem *item)
{
    QString nomCs = item->text();
    for (int i = 0; i < listeCS.count(); i++) {
        if (listeCS.at(i).nom == nomCs) {
            ui->webView->load(QUrl("http://maps.googleapis.com/maps/api/staticmap?zoom=14&size=641x289&maptype=roadmap&markers=" + listeCS.at(i).adresse));
            //color:blue|
        }
    }
}

void MainWindow::nouvelAppel()
{
    QIcon icone = QIcon(":/images/images/telAppel.jpg");
    QListWidgetItem *appel = new QListWidgetItem(icone,"Appel entrant...");
    ui->listAppels->insertItem(0, appel);
}

void MainWindow::on_listAppels_itemClicked(QListWidgetItem *item)
{
    if (item->text() == "Appel entrant...") {
        for (int i = 0; i < ui->listAppels->count(); i++) {
            if (ui->listAppels->item(i) == item) {
                ui->listAppels->takeItem(i);
                listeInter << interventionAleatoire();
                QListWidgetItem *intervention = new QListWidgetItem(listeInter.last().desc);
                ui->listAppels->insertItem(i, intervention);
                ui->webView->load(QUrl("http://maps.googleapis.com/maps/api/staticmap?zoom=14&size=641x289&maptype=roadmap&markers=" + listeInter.last().lieu));
            }
        }
    }
    else {

    }
}

Intervention MainWindow::interventionAleatoire()
{
    database.open();
    QSqlQuery query;
    Intervention intervention = Intervention(NULL, NULL, NULL, NULL);
    query.prepare("SELECT numero, type, lieu, description FROM interventions WHERE numero = :numero");
    query.bindValue(":numero", 1);
    query.exec();
    while (query.next()) {
        int numero = query.record().value("numero").toInt();
        QString type = query.record().value("type").toString();
        QString lieu = query.record().value("lieu").toString();
        QString desc = query.record().value("description").toString();
        intervention = Intervention(numero, type, lieu, desc);
    }
    database.close();
    return intervention;
}

void MainWindow::updateInterventions()
{

}

void MainWindow::on_boutonNouveauDepart_clicked()
{
    FormDepart fenetre;
    fenetre.exec();
}
