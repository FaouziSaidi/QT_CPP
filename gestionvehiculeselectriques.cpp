#include "gestionvehiculeselectriques.h"
#include "ui_gestionvehiculeselectriques.h"
#include "voitureelectrique.h"
#include <QMessageBox>
GestionVehiculesElectriques::GestionVehiculesElectriques(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GestionVehiculesElectriques)
{
    ui->setupUi(this);
    ui->TableVehiculesElectriques->setModel(voiture.afficher());
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

    QString etat=ui->lineEdit_6->text();
    QString charge=ui->lineEdit_7->text();
    QString maintenance=ui->lineEdit_8->text();
    QString disponibilite=ui->lineEdit_9->text();
    int annee_fabrication=ui->lineEdit_5->text().toInt();

    VoitureElectrique V(VIN,plaque_immatriculation,marque,modele,etat,charge,maintenance,disponibilite,annee_fabrication);

    bool test=V.ajouter();

    if(test)
    {
        //Refresh for the sake of the affichage function
        ui->TableVehiculesElectriques->setModel(voiture.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectue\n"
                                             "Click Cancel to exit"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK bro"),
                              QObject::tr("Ajout non effectue.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);



}



void GestionVehiculesElectriques::on_SupprimerVoitureBouton_clicked()
{
    QString VIN = ui->lineEdit->text();
    bool test=voiture.supprimer(VIN);

    if(test)
    {
        //Refresh for the sake of the affichage function
        ui->TableVehiculesElectriques->setModel(voiture.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuee\n"
                                             "Click Cancel to exit"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK bro"),
                              QObject::tr("Suppression non effectuee.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}



void GestionVehiculesElectriques::on_ModifierVoitureBouton_clicked()
{
        // To get the data for modification
        QString VIN = ui->lineEdit->text();
        QString newPlaqueImmatriculation = ui->lineEdit_2->text();
        QString newMarque = ui->lineEdit_3->text();
        QString newModele = ui->lineEdit_4->text();
        QString newEtat = ui->lineEdit_6->text();
        QString newCharge = ui->lineEdit_7->text();
        QString newMaintenance = ui->lineEdit_8->text();
        QString newDisponibilite = ui->lineEdit_9->text();
        int newAnneeFabrication = ui->lineEdit_5->text().toInt();

        bool test = voiture.modifier(VIN, newPlaqueImmatriculation, newMarque, newModele, newEtat, newCharge, newMaintenance, newDisponibilite, newAnneeFabrication);

        if (test)
        {
            // Refresh for the sake of the affichage function
            ui->TableVehiculesElectriques->setModel(voiture.afficher());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Modification effectuee\n"
                            "Click Cancel to exit"), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK bro"),
                QObject::tr("Modification non effectuee.\n"
                "Click Cancel to exit."), QMessageBox::Cancel);
}
