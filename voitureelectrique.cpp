#include "voitureelectrique.h"
#include "gestionvehiculeselectriques.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>

VoitureElectrique::VoitureElectrique(QString VIN,QString plaque_immatriculation,QString marque,QString modele,QString etat,QString charge,QString maintenance,QString disponibilite,int annee_fabrication)
{
    this->VIN=VIN;
    this->plaque_immatriculation=plaque_immatriculation;
    this->marque=marque;
    this->modele=modele;

    this->etat=etat;
    this->charge=charge;
    this->maintenance=maintenance;
    this->disponibilite=disponibilite;
    this->annee_fabrication=annee_fabrication;
}

bool VoitureElectrique::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO VOITUREELECTRIQUE (VIN, PLAQUEIMMATRICULATION, MARQUE, MODELE, ETAT, CHARGE, MAINTENANCE, DISPONIBILITE, ANNEE_FABRICATION) "
                  "VALUES (:VIN, :PLAQUEIMMATRICULATION, :MARQUE, :MODELE, :ETAT, :CHARGE, :MAINTENANCE, :DISPONIBILITE, :ANNEE_FABRICATION)");

    query.bindValue(":VIN", VIN);
    query.bindValue(":PLAQUEIMMATRICULATION", plaque_immatriculation);
    query.bindValue(":MARQUE", marque);
    query.bindValue(":MODELE", modele);

    query.bindValue(":ETAT", etat);
    query.bindValue(":CHARGE", charge);
    query.bindValue(":MAINTENANCE", maintenance);
    query.bindValue(":DISPONIBILITE", disponibilite);
    query.bindValue(":ANNEE_FABRICATION", annee_fabrication);


    return query.exec();

}

QSqlQueryModel * VoitureElectrique::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from VOITUREELECTRIQUE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("VIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PLAQUEIMMATRICULATION"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MARQUE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MODELE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CHARGE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("MAINTENANCE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DISPONIBILITE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ANNEE_FABRICATION"));

        return model;
}

bool VoitureElectrique::supprimer(QString VIN)
{
    QSqlQuery query;
    query.prepare("DELETE FROM VOITUREELECTRIQUE WHERE VIN = :VIN");
    query.bindValue(":VIN", VIN);

    return query.exec();
}

bool VoitureElectrique::modifier(QString VIN, QString newPlaqueImmatriculation, QString newMarque, QString newModele, QString newEtat, QString newCharge, QString newMaintenance, QString newDisponibilite, int newAnneeFabrication)
{
    QSqlQuery query;
    query.prepare("UPDATE VOITUREELECTRIQUE SET PLAQUEIMMATRICULATION=:PLAQUEIMMATRICULATION, MARQUE=:MARQUE, MODELE=:MODELE, ETAT=:ETAT, CHARGE=:CHARGE, MAINTENANCE=:MAINTENANCE, DISPONIBILITE=:DISPONIBILITE, ANNEE_FABRICATION=:ANNEE_FABRICATION WHERE VIN=:VIN");

    query.bindValue(":PLAQUEIMMATRICULATION", newPlaqueImmatriculation);
    query.bindValue(":MARQUE", newMarque);
    query.bindValue(":MODELE", newModele);
    query.bindValue(":ETAT", newEtat);
    query.bindValue(":CHARGE", newCharge);
    query.bindValue(":MAINTENANCE", newMaintenance);
    query.bindValue(":DISPONIBILITE", newDisponibilite);
    query.bindValue(":ANNEE_FABRICATION", newAnneeFabrication);
    query.bindValue(":VIN", VIN);

    return query.exec();
}




