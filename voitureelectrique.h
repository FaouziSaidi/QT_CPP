#ifndef VOITUREELECTRIQUE_H
#define VOITUREELECTRIQUE_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class VoitureElectrique
{
    private :
        QString VIN, plaque_immatriculation, marque, modele, etat, maintenance, disponibilite;
        float charge;
        int date_fabrication;
    public:
        //Constructeurs
        VoitureElectrique(){};//Constructeur classique
        VoitureElectrique(QString,QString,QString,QString,int,QString,float,QString,QString);//Constructeur parametré

        //Getters
        QString getVIN(){return VIN;}
        QString getPlaque_immatriculation(){return plaque_immatriculation;}
        QString getMarque(){return marque;}
        QString getModele(){return modele;}
        int getAnneeFabrication(){return date_fabrication;}
        QString getEtat(){return etat;}
        float getCharge(){return charge;}
        QString getMaintenance(){return maintenance;}
        QString getDisponibilite(){return disponibilite;}

        //Setters
        void setVIN(QString v){VIN = v;}
        void setPlaque_immatriculation(QString p_im){plaque_immatriculation = p_im;}
        void setMarque(QString m){marque = m;}
        void setModele(QString mo){modele = mo;}
        void setAnneeFabrication(int date_fabrication){this->date_fabrication=date_fabrication;}
        void setEtat(QString e){etat = e;}
        void setCharge(float charge){this->charge=charge;}
        void setMaintenance(QString ma){maintenance = ma;}
        void setDisponibilite(QString d){disponibilite = d;}

        //Les fonctionnalités basiques du CRUD de l'étudiant
        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(QString);





};

#endif // VOITUREELECTRIQUE_H
