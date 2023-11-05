#include<QDebug>
#include<QSqlError>
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
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("age"));
    model->setHeaderData(11,Qt::Horizontal,QObject::tr("num_telephone"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("salaire"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("heures_de_travail"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("date_embauche"));
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


bool Employes::load(int employes_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM employes WHERE employes_id = :id");
    query.bindValue(":id", employes_id);

    if (query.exec() && query.first()) {
        employes_id = query.value("employes_id").toInt();
        nom = query.value("nom").toString();
        prenom = query.value("prenom").toString();
        Email = query.value("email").toString();
        genre = query.value("genre").toString();
        mot_de_passe = query.value("mot_de_passe").toString();
        CIN = query.value("cin").toInt();
        age = query.value("age").toInt();
        num_telephone = query.value("num_telephone").toInt();
        salaire = query.value("salaire").toFloat();
        heures_de_travail = query.value("heures_de_travail").toFloat();
        date_embauche = query.value("date_embauche").toDate();

        return true;
    }

    return false;
}

QSqlQueryModel *Employes::rechercherParNom(const QString &nom)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM employes WHERE nom = :nom");
    query.bindValue(":nom", nom);

    if (query.exec())
    {
        model->setQuery(query);
        return model;
    }
    else
    {
        qDebug() << "Recherche par nom échouée : " << query.lastError();
        delete model;
        return nullptr;
    }
}

QSqlQueryModel* Employes::trierParAnneeEmbauche()
{
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM employes ORDER BY date_embauche ASC");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("employes_id"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("genre"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("mot_de_passe"));
        model->setHeaderData(10,Qt::Horizontal,QObject::tr("CIN"));
        model->setHeaderData(8,Qt::Horizontal,QObject::tr("age"));
        model->setHeaderData(11,Qt::Horizontal,QObject::tr("num_telephone"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("salaire"));
        model->setHeaderData(8,Qt::Horizontal,QObject::tr("heures_de_travail"));
        model->setHeaderData(9,Qt::Horizontal,QObject::tr("date_embauche"));
        return model;
}


QList<Employes> Employes::getAllEmployees()
{
    QList<Employes> employees;


        QSqlQuery query("SELECT * FROM employes");

        while (query.next()) {
            int employes_id = query.value("employes_id").toInt();
            QString nom = query.value("nom").toString();
            QString prenom = query.value("prenom").toString();
            QString Email = query.value("email").toString();
            QString genre = query.value("genre").toString();
            QString mot_de_passe = query.value("mot_de_passe").toString();
            int cin = query.value("cin").toInt();
            int age = query.value("age").toInt();
            int num_tel = query.value("num_telephone").toInt();
            float salaire = query.value("salaire").toFloat();
            float heures_de_travail = query.value("heures_de_travail").toFloat();
            QDate date_embauche = query.value("date_embauche").toDate();

             Employes E(nom, prenom, Email, genre, mot_de_passe, cin, age, num_tel, employes_id, salaire, heures_de_travail, date_embauche);
            employees.append(E);
        }


    return employees;
}



