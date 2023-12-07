#include "voitureelectrique.h"
#include "gestionvehiculeselectriques.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QMap>

VoitureElectrique::VoitureElectrique(QString VIN,QString plaque_immatriculation,QString marque,QString modele,QString etat,QString charge,QString maintenance,QString disponibilite,int annee_fabrication, QString photoPath, int CODE)
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
    this->photoPath=photoPath;
    this->CODE=CODE;
}

QString VoitureElectrique::getPhotoPathForVIN(const QString &VIN) const
{
    // Assuming you have a QSqlQueryModel named "model" for handling queries

    // Prepare the SQL query to retrieve the photo path based on VIN
    QString queryStr = "SELECT PHOTO_PATH FROM VOITUREELECTRIQUE WHERE VIN = :vin";
    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":vin", VIN);

    // Execute the query
    if (query.exec() && query.next()) {
        // Retrieve the photo path from the query result
        QString photoPath = query.value("PHOTO_PATH").toString();

        // Debug statement
        qDebug() << "Photo Path:" << photoPath;

        // You may want to check if the photo path is not empty or null before returning
        // For example, if (photoPath.isEmpty()) { /* handle empty path */ }

        return photoPath;
    } else {
        // Handle the case when the query fails or no result is found
        qDebug() << "Error executing query or no result for VIN:" << VIN;
        qDebug() << "SQL Error:" << query.lastError().text();
        return QString();  // Return an empty string or handle accordingly
    }
}




bool VoitureElectrique::isValidVIN(QString vin) {
    // Le standard international mta3 l VIN 17 Characters nbr+chiffres
    if (vin.length() != 17) {
        return false;
    }

    // Check for invalid characters (chiffres lettres)
    QRegExp rx("^[a-zA-Z0-9]*$");
    if (!rx.exactMatch(vin)) {
        return false;
    }
    else
    return true;
}

bool VoitureElectrique::existe(QString VIN) {
    QSqlQuery query;
    query.prepare("SELECT VIN FROM VOITUREELECTRIQUE WHERE VIN = :VIN");
    query.bindValue(":VIN", VIN);
    query.exec();

    return query.next(); // Returns true si une ligne avec ce VIN a ete trouvee
}

bool VoitureElectrique::ajouter()
{

    QString VIN = this->VIN;
    // Check if the VIN is valid
    if (!isValidVIN(VIN)) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur d'ajout"),
            QObject::tr("Ajout non effectué. Le VIN est invalide. Assurez-vous que le VIN comporte 17 caractères alphanumériques."),
            QMessageBox::Cancel);
        return false; // Invalid VIN, return false
    }


    if (existe(VIN)) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur d'ajout"),
            QObject::tr("Ajout non effectué. Ce VIN existe déjà."),
            QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO VOITUREELECTRIQUE (VIN, PLAQUEIMMATRICULATION, MARQUE, MODELE, ETAT, CHARGE, MAINTENANCE, DISPONIBILITE, ANNEE_FABRICATION, PHOTO_PATH) "
                  "VALUES (:VIN, :PLAQUEIMMATRICULATION, :MARQUE, :MODELE, :ETAT, :CHARGE, :MAINTENANCE, :DISPONIBILITE, :ANNEE_FABRICATION, :PHOTO_PATH)");

    query.bindValue(":VIN", VIN);
    query.bindValue(":PLAQUEIMMATRICULATION", plaque_immatriculation);
    query.bindValue(":MARQUE", marque);
    query.bindValue(":MODELE", modele);

    query.bindValue(":ETAT", etat);
    query.bindValue(":CHARGE", charge);
    query.bindValue(":MAINTENANCE", maintenance);
    query.bindValue(":DISPONIBILITE", disponibilite);
    query.bindValue(":ANNEE_FABRICATION", annee_fabrication);
    query.bindValue(":PHOTO_PATH", photoPath);


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
    /*if (!existe(VIN)) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur d'ajout"),
            QObject::tr("On ne peut pas supprimer un VIN qui n'existe pas ! Vérifiez que vous avez entré un VIN de la BDD (vérifier espaces à la fin)."),
            QMessageBox::Cancel);
        return false;
    }*/

    QSqlQuery query;
    query.prepare("DELETE FROM VOITUREELECTRIQUE WHERE VIN = :VIN");
    query.bindValue(":VIN", VIN);

    return query.exec();
}

bool VoitureElectrique::modifier(QString VIN, QString newPlaqueImmatriculation, QString newMarque, QString newModele, QString newEtat, QString newCharge, QString newMaintenance, QString newDisponibilite, int newAnneeFabrication, int newCODE)
{
    QSqlQuery query;
    query.prepare("UPDATE VOITUREELECTRIQUE SET PLAQUEIMMATRICULATION=:PLAQUEIMMATRICULATION, MARQUE=:MARQUE, MODELE=:MODELE, ETAT=:ETAT, CHARGE=:CHARGE, MAINTENANCE=:MAINTENANCE, DISPONIBILITE=:DISPONIBILITE, ANNEE_FABRICATION=:ANNEE_FABRICATION, CODE=:CODE WHERE VIN=:VIN");

    query.bindValue(":PLAQUEIMMATRICULATION", newPlaqueImmatriculation);
    query.bindValue(":MARQUE", newMarque);
    query.bindValue(":MODELE", newModele);
    query.bindValue(":ETAT", newEtat);
    query.bindValue(":CHARGE", newCharge);
    query.bindValue(":MAINTENANCE", newMaintenance);
    query.bindValue(":DISPONIBILITE", newDisponibilite);
    query.bindValue(":ANNEE_FABRICATION", newAnneeFabrication);
    query.bindValue(":VIN", VIN);
    query.bindValue(":CODE", newCODE);

    return query.exec();
}

QSqlQueryModel* VoitureElectrique::trierParAnnee()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM VOITUREELECTRIQUE ORDER BY ANNEE_FABRICATION ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("VIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PLAQUEIMMATRICULATION"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MARQUE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MODELE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CHARGE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("MAINTENANCE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DISPONIBILITE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ANNEE_FABRICATION"));

    // Retourner le modèle trié
    return model;
}

QSqlQueryModel* VoitureElectrique::trierParVIN()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM VOITUREELECTRIQUE ORDER BY VIN ASC");
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

QSqlQueryModel* VoitureElectrique::trierParCharge() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM VOITUREELECTRIQUE ORDER BY CHARGE ASC");
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



QSqlQueryModel *VoitureElectrique::rechercherParMarque(const QString &marque)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM VOITUREELECTRIQUE WHERE MARQUE = :marque");
    query.bindValue(":marque", marque);

    if (query.exec())
    {
        model->setQuery(query);
        return model;
    }
    else
    {
        qDebug() << "Recherche par marque échouée : " << query.lastError();
        delete model;
        return nullptr;
    }
}

QSqlQueryModel* VoitureElectrique::afficherVoituresDisponibles() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM VOITUREELECTRIQUE WHERE DISPONIBILITE = 'Disponible'");
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

QSqlQueryModel* VoitureElectrique::afficherVoituresAvecMaintenance() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM VOITUREELECTRIQUE WHERE MAINTENANCE = 'Effectuee'");
    model->setQuery("SELECT * FROM VOITUREELECTRIQUE WHERE DISPONIBILITE = 'Disponible'");
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


QStringList VoitureElectrique::getMarqueData() {
    QStringList marqueData;
    QSqlQuery query;
    query.prepare("SELECT MARQUE FROM VOITUREELECTRIQUE");
    if (query.exec()) {
        while (query.next()) {
            marqueData << query.value(0).toString();
        }
    }
    return marqueData;
}


// Implement K-Means clustering here

// For this example, let's simulate some clustering results
// Replace this with actual K-Means clustering code


QStringList VoitureElectrique::performKMeansClustering(int numClusters) {
    QStringList clusteringResults;
    QStringList data = getMarqueData();



    for (int i = 0; i < data.size(); ++i) {
        clusteringResults << "MARQUE: " + data[i] + " is in Cluster: " + QString::number(i % numClusters);
    }

    return clusteringResults;
}

bool VoitureElectrique::rechercherCODE(int CODE)
{
    QSqlQuery *query=new QSqlQuery;
    query->prepare("SELECT 1 FROM VOITUREELECTRIQUE WHERE CODE = :CODE");
    query->bindValue(":CODE",CODE);

    if (query->exec() && query->next())
    {
            // The ID exists in the database
            return true;
        } else {
            // The ID does not exist in the database
            return false;
        }
}





