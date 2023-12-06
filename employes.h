#ifndef EMPLOYES_H
#define EMPLOYES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

class Employes
{
    QString nom,prenom,Email,genre,mot_de_passe;
    int employes_id;
    QString CIN,num_telephone;
    float salaire,heures_de_travail;
    QDate date_embauche,date_naissance;
public:
    Employes();
    Employes(QString,QString,QString,QString,QString,QString,QString,int,float,float,QDate,QDate);
    //getters
        QString getNom() const {return nom;}
        QString getPrenom() const {return prenom;}
        QString getEmail() const {return Email;}
        QString getGenre() const {return genre;}
        QString getMotDePasse() const {return mot_de_passe;}
        int getEmployesId() const {return employes_id;}
        QString getCIN() const {return CIN;}
        QString getNumeroTelephone() const {return num_telephone;}
        float getSalaire() const {return salaire;}
        float getHeuresDeTravail() const {return heures_de_travail;}
        QDate getDateEmbauche() const {return date_embauche;}
        QDate getNaissance() const {return date_naissance;}

    //setters
        void setID(int newid){employes_id=newid;}
        void setNom(const QString& newNom) { nom = newNom; }
        void setPrenom(const QString& newPrenom) { prenom = newPrenom; }
        void setEmail(const QString& newEmail) { Email = newEmail; }
        void setGenre(const QString& newGenre) { genre = newGenre; }
        void setMotDePasse(const QString& newMotDePasse) { mot_de_passe = newMotDePasse; }
        void setCIN(const QString& newCIN) { CIN = newCIN; }
        void setNumeroTelephone(const QString& newNumeroTelephone) { num_telephone = newNumeroTelephone; }
        void setSalaire(float newSalaire) { salaire = newSalaire; }
        void setHeuresDeTravail(float newHeuresDeTravail) { heures_de_travail = newHeuresDeTravail; }
        void setDateEmbauche(const QDate& newDateEmbauche) { date_embauche = newDateEmbauche; }
        void setNaissance(const QDate& newDateNaissance) { date_naissance = newDateNaissance; }
    //methode
        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool modifier();
        bool existe();//employes
        bool vin_existe(QString vin);
        bool id_reclamation_existe(int id_reclamation);
        bool load(int employes_id);
        QSqlQueryModel * rechercherParNom(const QString &marque);
        QSqlQueryModel* trierParAnneeEmbauche();
        QList<Employes> getAllEmployees();
        QChartView* statistiques();
        QChartView* statistiquesSalaire();
        int employes_du_mois();
        QSqlQueryModel * afficher_employe_du_mois();

};

#endif // EMPLOYES_H
