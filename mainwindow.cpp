#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->webView->load(QUrl("http://maps.googleapis.com/maps/api/staticmap?zoom=15&size=558x288&maptype=roadmap&markers=color:blue|47.335147,5.067991"));

    // Gestion de la liste des engins du SDIS
    ui->listEngins->setRowCount(1);
    ui->listEngins->setColumnCount(10);

    QTableWidgetItem *CS = new QTableWidgetItem("CIS IS/TILLE");
    QTableWidgetItem *vsav = new QTableWidgetItem("VSAV");
    QTableWidgetItem *fptsr = new QTableWidgetItem("FPTSR");
    QTableWidgetItem *epc = new QTableWidgetItem("EPC");
    ui->listEngins->setItem(0, 0, CS);
    vsav->setTextAlignment(Qt::AlignCenter);
    ui->listEngins->setItem(0, 1, vsav);
    fptsr->setTextAlignment(Qt::AlignCenter);
    ui->listEngins->setItem(0, 2, fptsr);
    epc->setTextAlignment(Qt::AlignCenter);
    ui->listEngins->setItem(0, 3, epc);

    // Conexion à la BDD
    database = new QSqlDatabase;
    database->addDatabase("QSQLITE");
    database->setDatabaseName("database/database.db");

    database->open();
    QSqlQuery query;
    query.exec("SELECT * FROM centres");

    QList<QTableWidgetItem> listeCentres;

    while (query.next()) {
        QString nomCentre = query.record().value("nom").toString();
        QTableWidgetItem *centre = new QTableWidgetItem(nomCentre);
        ui->listEngins->setItem(0, 0, centre);
    }

    database->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
