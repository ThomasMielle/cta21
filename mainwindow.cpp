#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "centresecours.h"
#include "engin.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Variables locales /////////////////////////////////
    QList<CentreSecours> listeCS;

    // Création de la google map /////////////////////////
    ui->webView->load(QUrl("https://www.google.fr/maps"));
    //http://maps.googleapis.com/maps/api/staticmap?
    //center=Dijon,21000
    //zoom=12
    //size=641x289
    //maptype=roadmap
    //markers=color:blue|47.335147,5.067991

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
}

MainWindow::~MainWindow()
{
    delete ui;
}
