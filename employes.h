#ifndef EMPLOYES_H
#define EMPLOYES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Employes
{
    QString nom,prenom,Email,genre,mot_de_passe;
    int age,employes_id;
    int CIN,num_telephone;
    float salaire,heures_de_travail;
    QDate date_embauche;
public:
    Employes();
    Employes(QString,QString,QString,QString,QString,int,int,int,int,float,float,QDate);
    //getters
        QString getNom() const {return nom;}
        QString getPrenom() const {return prenom;}
        QString getEmail() const {return Email;}
        QString getGenre() const {return genre;}
        QString getMotDePasse() const {return mot_de_passe;}
        int getEmployesId() const {return employes_id;}
        int getCIN() const {return CIN;}
        int getAge() const {return age;}
        int getNumeroTelephone() const {return num_telephone;}
        float getSalaire() const {return salaire;}
        float getHeuresDeTravail() const {return heures_de_travail;}
        QDate getDateEmbauche() const {return date_embauche;}

    //setters
        void setID(int newid){employes_id=newid;}
        void setNom(const QString& newNom) { nom = newNom; }
        void setPrenom(const QString& newPrenom) { prenom = newPrenom; }
        void setEmail(const QString& newEmail) { Email = newEmail; }
        void setGenre(const QString& newGenre) { genre = newGenre; }
        void setMotDePasse(const QString& newMotDePasse) { mot_de_passe = newMotDePasse; }
        void setCIN(int newCIN) { CIN = newCIN; }
        void setAge(int newAge) { age = newAge; }
        void setNumeroTelephone(int newNumeroTelephone) { num_telephone = newNumeroTelephone; }
        void setSalaire(float newSalaire) { salaire = newSalaire; }
        void setHeuresDeTravail(float newHeuresDeTravail) { heures_de_travail = newHeuresDeTravail; }
        void setDateEmbauche(const QDate& newDateEmbauche) { date_embauche = newDateEmbauche; }
    //methode
        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool modifier();
        bool existe();
        bool load(int employes_id);
        QSqlQueryModel * rechercherParNom(const QString &marque);
        QSqlQueryModel* trierParAnneeEmbauche();
        QList<Employes> getAllEmployees();
};

#endif // EMPLOYES_H
