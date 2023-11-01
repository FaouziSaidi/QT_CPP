#include "employes.h"

Employes::Employes()
{
}

Employes::Employes(QString nom, QString prenom, QString Email, QString genre, QString mot_de_passe, double CIN, int age, double num_telephone, int employes_id, float salaire, float heures_de_travail, QDate date_embauche)
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
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("employes_id"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Email"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("genre"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("mot_de_passe"));
    model->setHeaderData(11,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("age"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("num_telephone"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("salaire"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("heures_de_travail"));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("date_embauche"));
    return model;
}

bool Employes::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);

    query.prepare("Delete from employes where employes_id= :id");
    query.bindValue(":id",res);

    //return query.exec();
    if (query.exec()) {
            if (query.numRowsAffected() > 0) {
                // Au moins une ligne a été supprimée, donc la suppression a réussi.
                return true;
            }
        }

return false;
}








bool Employes::existe()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isValid()) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM employes WHERE employes_id = :employes_id");
        query.bindValue(":employes_id", employes_id);

        if (query.exec() && query.next()) {
            int count = query.value(0).toInt();


            return count > 0;
        }
    }

    return false;
}




bool Employes::modifier()
{
        QSqlQuery query;
        QString ch_id = QString::number(employes_id);
        QString ch_cin = QString::number(CIN);
        QString ch_age = QString::number(age);
        QString ch_num_tel = QString::number(num_telephone);
        QString ch_salaire = QString::number(salaire);
        QString ch_heures_travail = QString::number(heures_de_travail);

        query.prepare("UPDATE employes SET nom = :nom, prenom = :prenom, email = :email, genre = :genre, mot_de_passe = :mot_de_passe, cin = :cin, age = :age, num_telephone = :num_telephone, salaire = :salaire, heures_de_travail = :heures_de_travail, date_embauche = :date_embauche WHERE employes_id = :employes_id");

        query.bindValue(":employes_id", ch_id);
        query.bindValue(":cin", ch_cin);
        query.bindValue(":age", ch_age);
        query.bindValue(":num_telephone", ch_num_tel);
        query.bindValue(":salaire", ch_salaire);
        query.bindValue(":heures_de_travail", ch_heures_travail);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":email", Email);
        query.bindValue(":mot_de_passe", mot_de_passe);
        query.bindValue(":genre", genre);
        query.bindValue(":date_embauche", date_embauche);

        return query.exec();
}









/*
bool Employes::modifier()
{
        QSqlQuery query;
        QString ch_id = QString::number(employes_id);
        QString ch_cin = QString::number(CIN);
        QString ch_age = QString::number(age);
        QString ch_num_tel = QString::number(num_telephone);
        QString ch_salaire = QString::number(salaire);
        QString ch_heures_travail = QString::number(heures_de_travail);



        query.bindValue(":employes_id", ch_id);


        if (!nom.isEmpty()) {
            query.prepare("UPDATE employes SET nom = :nom WHERE employes_id = :employes_id");
            query.bindValue(":nom", nom);
        }
        if (!prenom.isEmpty()) {
            query.prepare("UPDATE employes SET prenom = :prenom WHERE employes_id = :employes_id");
            query.bindValue(":prenom", prenom);
        }
        if (!Email.isEmpty()) {
            query.prepare("UPDATE employes SET Email = :email WHERE employes_id = :employes_id");
            query.bindValue(":email", Email);
        }
        if (!mot_de_passe.isEmpty()) {
            query.prepare("UPDATE employes SET  mot_de_passe = :mot_de_passe WHERE employes_id = :employes_id");
            query.bindValue(":mot_de_passe", mot_de_passe);
        }
        if (!genre.isEmpty()) {
            query.bindValue(":genre", genre);
        }
       if (!ch_cin.isEmpty()) {
            query.prepare("UPDATE employes SET  CIN = :cin WHERE employes_id = :employes_id");
            query.bindValue(":cin", ch_cin);
        }
        if (!ch_age.isEmpty()) {
            query.prepare("UPDATE employes SET  age = :age WHERE employes_id = :employes_id");
            query.bindValue(":age", ch_age);
        }
        if (!ch_num_tel.isEmpty()) {
            query.prepare("UPDATE employes SET  num_telephone = :num_telephone WHERE employes_id = :employes_id");
            query.bindValue(":num_telephone", ch_num_tel);
        }
        if (!ch_salaire.isEmpty()) {
            query.prepare("UPDATE employes SET  salaire = :salaire WHERE employes_id = :employes_id");
            query.bindValue(":salaire", ch_salaire);
        }
        if (!ch_heures_travail.isEmpty()) {
            query.prepare("UPDATE employes SET  heures_de_travail = :heures_de_travail WHERE employes_id = :employes_id");
            query.bindValue(":heures_de_travail", ch_heures_travail);
        }
        if (date_embauche.isValid()) {
            query.prepare("UPDATE employes SET  date_embauche = :date_embauche WHERE employes_id = :employes_id");
            query.bindValue(":date_embauche", date_embauche);
        }



        if (query.exec()) {
            return true;
        } else {
            return false;
        }
}*/


/*bool Employes::modifier()
{
    QSqlQuery query;
       QString ch_id = QString::number(employes_id);
       QString ch_cin = QString::number(CIN);
       QString ch_age = QString::number(age);
       QString ch_num_tel = QString::number(num_telephone);
       QString ch_salaire = QString::number(salaire);
       QString ch_heures_travail = QString::number(heures_de_travail);

       query.prepare("UPDATE employes SET nom = :nom, prenom = :prenom, email = :email, genre = :genre, mot_de_passe = :mot_de_passe, cin = :cin, age = :age, num_telephone = :num_telephone, salaire = :salaire, heures_de_travail = :heures_de_travail, date_embauche = :date_embauche WHERE employes_id = :employes_id");

       query.bindValue(":employes_id", ch_id);
       query.bindValue(":cin", ch_cin);
       query.bindValue(":age", ch_age);
       query.bindValue(":num_telephone", ch_num_tel);
       query.bindValue(":salaire", ch_salaire);
       query.bindValue(":heures_de_travail", ch_heures_travail);
       query.bindValue(":nom", nom);
       query.bindValue(":prenom", prenom);
       if (!Email.isEmpty()) {
              query.bindValue(":email", Email);
          }
       query.bindValue(":mot_de_passe", mot_de_passe);
       query.bindValue(":genre", genre);
       query.bindValue(":date_embauche", date_embauche);

       return query.exec();
}

*/





