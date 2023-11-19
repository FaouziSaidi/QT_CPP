#ifndef VOITUREELECTRIQUE_H
#define VOITUREELECTRIQUE_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class VoitureElectrique
{
    private :
        QString VIN, plaque_immatriculation, marque, modele, etat,charge, maintenance, disponibilite;
        int annee_fabrication;
        QString photoPath;

    public:
        //Constructeurs
        VoitureElectrique(){};//Constructeur classique
        VoitureElectrique(QString,QString,QString,QString,QString,QString,QString,QString,int,QString);//Constructeur parametré
        bool isValidVIN(QString vin);
        bool existe(QString VIN);


        //Getters
        QString getVIN(){return VIN;}
        QString getPlaque_immatriculation(){return plaque_immatriculation;}
        QString getMarque(){return marque;}
        QString getModele(){return modele;}

        QString getEtat(){return etat;}
        QString getCharge(){return charge;}
        QString getMaintenance(){return maintenance;}
        QString getDisponibilite(){return disponibilite;}

        int getAnneeFabrication() {return annee_fabrication;}

        QString getphotoPath(){return photoPath;}
        QString getPhotoPathForVIN(const QString &VIN) const;

        //Setters
        void setVIN(QString v){VIN = v;}
        void setPlaque_immatriculation(QString p_im){plaque_immatriculation = p_im;}
        void setMarque(QString m){marque = m;}
        void setModele(QString mo){modele = mo;}

        void setEtat(QString e){etat = e;}
        void setCharge(QString charge){this->charge=charge;}
        void setMaintenance(QString ma){maintenance = ma;}
        void setDisponibilite(QString d){disponibilite = d;}
        void setAnneeFabrication(int annee) { annee_fabrication = annee; }

        //Les fonctionnalités basiques du CRUD de l'étudiant
        bool ajouter();
        QSqlQueryModel * afficher();
        bool modifier(QString VIN, QString newPlaqueImmatriculation, QString newMarque, QString newModele, QString newEtat, QString newCharge, QString newMaintenance, QString newDisponibilite, int newAnneeFabrication);
        bool supprimer(QString);

        //Métiers supplémentaires
        QSqlQueryModel * trierParAnnee();
        QSqlQueryModel * trierParVIN();
        QSqlQueryModel * trierParCharge();

        QSqlQueryModel *rechercherParMarque (const QString &marque);
        QSqlQueryModel* afficherVoituresDisponibles();
        QSqlQueryModel* afficherVoituresAvecMaintenance();

        // Function to fetch MARQUE data from the database
        QStringList getMarqueData();

        // Function to perform K-Means clustering
        QStringList performKMeansClustering(int numClusters);




};

#endif // VOITUREELECTRIQUE_H
