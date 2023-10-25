#include "employes.h"

Employes::Employes()
{
}

Employes::Employes(QString nom, QString prenom, QString Email, QString genre, QString mot_de_passe, int CIN, int age, int num_telephone, int employes_id, float salaire, float heures_de_travail, QDate date_embauche)
{
        this->nom = nom;
        this->prenom = prenom;
        this->Email = Email;
        this->genre = genre;
        this->mot_de_passe = mot_de_passe;
        this->CIN = CIN;
        this->age = age;
        this->num_telephone = num_telephone;
        this->employes_id = employes_id;
        this->salaire = salaire;
        this->heures_de_travail = heures_de_travail;
        this->date_embauche = date_embauche;
}

bool Employes::ajouter()
{
    QSqlQuery query;
    QString ch_id = QString::number(employes_id);
    QString ch_cin = QString::number(CIN);
    QString ch_age = QString::number(age);
    QString ch_num_tel = QString::number(num_telephone);
    QString ch_salaire = QString::number(salaire);
    QString ch_heures_travail = QString::number(heures_de_travail);
    query.prepare("INSERT INTO employes (nom, prenom, email, genre, mot_de_passe, cin, age, num_telephone, employes_id, salaire, heures_de_travail, date_embauche) VALUES (:nom, :prenom, :email, :genre, :mot_de_passe, :cin, :age, :num_telephone, :employes_id, :salaire, :heures_de_travail, :date_embauche)");
    query.bindValue(":employes_id",ch_id);
    query.bindValue(":cin",ch_cin);
    query.bindValue(":age",ch_age);
    query.bindValue(":num_telephone",ch_num_tel);
    query.bindValue(":salaire",ch_salaire);
    query.bindValue(":heures_de_travail",ch_heures_travail );
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",Email);
    query.bindValue(":mot_de_passe",mot_de_passe);
    query.bindValue(":genre",genre);
    query.bindValue(":date_embauche",date_embauche);
    return query.exec();

}


QSqlQueryModel *Employes::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from employes");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("employes_id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("genre"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("mot_de_passe"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("age"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("num_telephone"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("salaire"));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("heures_de_travail"));
    model->setHeaderData(11,Qt::Horizontal,QObject::tr("date_embauche"));
    return model;
}

























