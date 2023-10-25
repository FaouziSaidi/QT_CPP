#include "gestionvehiculeselectriques.h"
#include "ui_gestionvehiculeselectriques.h"
#include "voitureelectrique.h"
#include <QMessageBox>
GestionVehiculesElectriques::GestionVehiculesElectriques(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GestionVehiculesElectriques)
{
    ui->setupUi(this);
}

GestionVehiculesElectriques::~GestionVehiculesElectriques()
{
    delete ui;
}


void GestionVehiculesElectriques::on_AjouterVoitureBouton_clicked()
{
    //To get the data from the all the fiels on the left of the addbutton
    QString VIN=ui->lineEdit->text();
    QString plaque_immatriculation=ui->lineEdit_2->text();
    QString marque=ui->lineEdit_3->text();
    QString modele=ui->lineEdit_4->text();
    int date_fabrication=ui->lineEdit_5->text().toInt();
    QString etat=ui->lineEdit_6->text();
    float charge=ui->lineEdit_7->text().toFloat();
    QString maintenance=ui->lineEdit_8->text();
    QString disponibilite=ui->lineEdit_9->text();

    VoitureElectrique V(VIN,plaque_immatriculation,marque,modele,date_fabrication,etat,charge,maintenance,disponibilite);

    bool test=V.ajouter();

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectue\n"
                                             "Click Cancel to exit"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK bro"),
                              QObject::tr("Ajout non effectue.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);



}
