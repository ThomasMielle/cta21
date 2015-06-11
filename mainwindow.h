#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTableWidgetItem>
#include <QListWidgetItem>

#include "centresecours.h"
#include "intervention.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_listEngins_itemClicked(QTableWidgetItem *item);
    void on_listAppels_itemClicked(QListWidgetItem *item);

    void on_boutonNouveauDepart_clicked();

private:
    Ui::MainWindow *ui;

    // Attributs
private:
    QSqlDatabase database;
    QList<CentreSecours> listeCS;
    QList<Intervention> listeInter;

    // Fonctions
private:
    void nouvelAppel();
    Intervention interventionAleatoire();
    void updateInterventions();

};

#endif // MAINWINDOW_H
