#include "formdepart.h"
#include "ui_formdepart.h"

FormDepart::FormDepart(QWidget *parent) : QDialog(parent), ui(new Ui::FormDepart)
{
    ui->setupUi(this);
    on_comboBoxTypeInter1_currentIndexChanged(ui->comboBoxTypeInter1->currentText());
}

FormDepart::~FormDepart()
{
    delete ui;
}

void FormDepart::on_comboBoxTypeInter1_currentIndexChanged(const QString &arg1)
{
    ui->comboBoxTypeInter2->clear();
    if (arg1 == "SECOURS A PERSONNES") {
        ui->comboBoxTypeInter2->addItem("ACCOUCHEMENT A DOMICILE");
        ui->comboBoxTypeInter2->addItem("BLESSE SUITE CHUTE A DOMICILE");
        ui->comboBoxTypeInter2->addItem("PROMPT SECOURS UA");
    }
    else if (arg1 == "ACCIDENT DE CIRCULATION") {
        ui->comboBoxTypeInter2->addItem("ACCIDENT CHUTE DE 2 ROUES");
        ui->comboBoxTypeInter2->addItem("ACCIDENT TC AVEC VOYAGEUR");
        ui->comboBoxTypeInter2->addItem("ACCIDENT VL SEUL");
    }
    else if (arg1 == "OPERATIONS DIVERSES") {
        ui->comboBoxTypeInter2->addItem("APPUI HELICO SMUR");
        ui->comboBoxTypeInter2->addItem("DESTRUCTION D'HYMENOPTERES");
        ui->comboBoxTypeInter2->addItem("INNONDATION S/SOL OU CAVE");
    }
    else if (arg1 == "INCENDIE URBAIN") {
        ui->comboBoxTypeInter2->addItem("FEU DANS PAVILLON");
        ui->comboBoxTypeInter2->addItem("FEU D'ENTREPOT");
        ui->comboBoxTypeInter2->addItem("FEU DE VL");
    }
    else if (arg1 == "FEU DE FORET") {
        ui->comboBoxTypeInter2->addItem("FEU DE FRICHES OU BROUSAILLES");
        ui->comboBoxTypeInter2->addItem("FEU DE RECOLTES SUR PIED");
        ui->comboBoxTypeInter2->addItem("FEU DE FORET OU SOUS BOIS");
    }
    else if (arg1 == "RECONAISSANCE") {
        ui->comboBoxTypeInter2->addItem("ODEUR SUSPECTE");
        ui->comboBoxTypeInter2->addItem("PNRPAA <= R + 2");
        ui->comboBoxTypeInter2->addItem("PNRPAA > R + 2");
    }
}
