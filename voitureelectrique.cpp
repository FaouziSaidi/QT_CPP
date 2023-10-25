#include "voitureelectrique.h"

VoitureElectrique::VoitureElectrique(QString VIN,QString plaque_immatriculation,QString marque,QString modele,int date_fabrication,QString etat,float charge,QString maintenance,QString disponibilite)
{
    this->VIN=VIN;
    this->plaque_immatriculation=plaque_immatriculation;
    this->marque=marque;
    this->modele=modele;
    this->date_fabrication=date_fabrication;
    this->etat=etat;
    this->charge=charge;
    this->maintenance=maintenance;
    this->disponibilite=disponibilite;
}

bool VoitureElectrique::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO VOITUREELECTRIQUE (VIN, plaqueimmatriculation, marque, modele, anneefabrication, etat, charge, maintenance, disponibilite)" "values (:VIN, :plaqueimmatriculation, :marque, :modele, :anneefabrication, :etat, :charge, :maintenance, :disponibilite)");
    query.bindValue(":VIN",VIN);
    query.bindValue(":plaqueimmatriculation",plaque_immatriculation);
    query.bindValue(":marque",marque);
    query.bindValue(":modele",modele);
    query.bindValue(":anneefabrication",date_fabrication);
    query.bindValue(":etat",etat);
    query.bindValue(":charge",charge);
    query.bindValue(":maintenance",maintenance);
    query.bindValue(":disponibilite",disponibilite);
    return query.exec();
}



QSqlQueryModel * VoitureElectrique::afficher()
{

}

bool VoitureElectrique::supprimer(QString)
{

}
