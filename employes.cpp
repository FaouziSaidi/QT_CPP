#include<QDebug>
#include<QSqlError>
#include "employes.h"

Employes::Employes()
{
}

Employes::Employes(QString nom, QString prenom, QString Email, QString genre, QString mot_de_passe, int CIN, int num_telephone, int employes_id, float salaire, float heures_de_travail, QDate date_embauche,QDate date_naisaance)
{

        this->nom = nom;
        this->prenom = prenom;
        this->Email = Email;
        this->genre = genre;
        this->mot_de_passe = mot_de_passe;
        this->CIN = CIN;
        this->num_telephone = num_telephone;
        this->employes_id = employes_id;
        this->salaire = salaire;
        this->heures_de_travail = heures_de_travail;
        this->date_embauche = date_embauche;
        this->date_naissance=date_naisaance;
}

bool Employes::ajouter()
{
    QSqlQuery query;
    QString ch_id = QString::number(employes_id);
    QString ch_cin = QString::number(CIN);
    QString ch_num_tel = QString::number(num_telephone);
    QString ch_salaire = QString::number(salaire);
    QString ch_heures_travail = QString::number(heures_de_travail);

    query.prepare("INSERT INTO employes (nom, prenom, email, genre, mot_de_passe, cin, num_telephone, employes_id, salaire, heures_de_travail, date_embauche, date_naissance) VALUES (:nom, :prenom, :email, :genre, :mot_de_passe, :cin,:num_telephone, :employes_id, :salaire, :heures_de_travail, :date_embauche,:date_naissance)");
    query.bindValue(":employes_id",ch_id);
    query.bindValue(":cin",ch_cin);
    query.bindValue(":num_telephone",ch_num_tel);
    query.bindValue(":salaire",ch_salaire);
    query.bindValue(":heures_de_travail",ch_heures_travail );
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",Email);
    query.bindValue(":mot_de_passe",mot_de_passe);
    query.bindValue(":genre",genre);
    query.bindValue(":date_embauche",date_embauche);
    query.bindValue(":date_naissance",date_naissance);
    return query.exec();

}


QSqlQueryModel *Employes::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT employes_id, nom, prenom, Email, genre, CONCAT('****', SUBSTR(mot_de_passe, -4)) AS mot_de_passe, salaire, heures_de_travail,  date_embauche,CIN, num_telephone, date_naissance FROM employes");
    if (model->lastError().isValid()) {
        qDebug() << "Erreur SQL : " << model->lastError().text();
    }
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("employes_id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("genre"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("mot_de_passe"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("num_telephone"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("salaire"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("heures_de_travail"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("date_embauche"));
    model->setHeaderData(11,Qt::Horizontal,QObject::tr("date_naissance"));
    return model;
}







bool Employes::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);

    query.prepare("DELETE FROM gestion WHERE employes_id = :id");
       query.bindValue(":id", res);
       if (!query.exec()) {
           // Gestion de l'erreur si la suppression échoue
           qDebug() << "Erreur lors de la suppression dans la table gestion:" << query.lastError().text();
           return false;
       }
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
        QString ch_num_tel = QString::number(num_telephone);
        QString ch_salaire = QString::number(salaire);
        QString ch_heures_travail = QString::number(heures_de_travail);

        query.prepare("UPDATE employes SET nom = :nom, prenom = :prenom, email = :email, genre = :genre, mot_de_passe = :mot_de_passe, cin = :cin, num_telephone = :num_telephone, salaire = :salaire, heures_de_travail = :heures_de_travail, date_embauche = :date_embauche, date_naissance = :date_naissance WHERE employes_id = :employes_id");

        query.bindValue(":employes_id", ch_id);
        query.bindValue(":cin", ch_cin);
        query.bindValue(":num_telephone", ch_num_tel);
        query.bindValue(":salaire", ch_salaire);
        query.bindValue(":heures_de_travail", ch_heures_travail);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":email", Email);
        query.bindValue(":mot_de_passe", mot_de_passe);
        query.bindValue(":genre", genre);
        query.bindValue(":date_embauche", date_embauche);
        query.bindValue(":date_naissance", date_naissance);
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
        num_telephone = query.value("num_telephone").toInt();
        salaire = query.value("salaire").toFloat();
        heures_de_travail = query.value("heures_de_travail").toFloat();


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
        model->setHeaderData(9,Qt::Horizontal,QObject::tr("CIN"));
        model->setHeaderData(10,Qt::Horizontal,QObject::tr("num_telephone"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("salaire"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("heures_de_travail"));
        model->setHeaderData(8,Qt::Horizontal,QObject::tr("date_embauche"));
        model->setHeaderData(11,Qt::Horizontal,QObject::tr("date_naissance"));
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
            int num_tel = query.value("num_telephone").toInt();
            float salaire = query.value("salaire").toFloat();
            float heures_de_travail = query.value("heures_de_travail").toFloat();
            QDate date_embauche = query.value("date_embauche").toDate();
            QDate date_naissance = query.value("date_naissance").toDate();
             Employes E(nom, prenom, Email, genre, mot_de_passe, cin, num_tel, employes_id, salaire, heures_de_travail, date_embauche,date_naissance);
            employees.append(E);
        }


    return employees;
}





QChartView* Employes::statistiquesSalaire()
{
    QSqlQuery query;
    int totalEmployees = 0;

    // Définir les tranches de salaire
    int basSalaireCount = 0;
    int moyenSalaireCount = 0;
    int hautSalaireCount = 0;

    // Query the database to count the total number of employees and separate them by salary group
    if (query.exec("SELECT COUNT(*) FROM employes")) {
        if (query.next()) {
            totalEmployees = query.value(0).toInt();
        }
    }

    // Comptage des employés dans chaque tranche de salaire
    if (query.exec("SELECT COUNT(*) FROM employes WHERE salaire < 3000")) {
        if (query.next()) {
            basSalaireCount = query.value(0).toInt();
        }
    }

    if (query.exec("SELECT COUNT(*) FROM employes WHERE (salaire >= 3000 AND salaire < 5000)")) {
        if (query.next()) {
            moyenSalaireCount = query.value(0).toInt();
        }
    }

    if (query.exec("SELECT COUNT(*) FROM employes WHERE salaire >= 5000")) {
        if (query.next()) {
            hautSalaireCount = query.value(0).toInt();
        }
    }

    // Calculate the percentages
    double pourc_basSalaire = (static_cast<double>(basSalaireCount) / totalEmployees) * 100;
    double pourc_moyenSalaire = (static_cast<double>(moyenSalaireCount) / totalEmployees) * 100;
    double pourc_hautSalaire = (static_cast<double>(hautSalaireCount) / totalEmployees) * 100;

    QPieSeries *series = new QPieSeries();

    QPieSlice *sliceMoyenSalaire = new QPieSlice("entre 3000 et 5000", pourc_moyenSalaire);
    QPieSlice *sliceHautSalaire = new QPieSlice("superieur 5000", pourc_hautSalaire);
     QPieSlice *sliceBasSalaire = new QPieSlice("inferieur 3000 ", pourc_basSalaire);
    // Définir les couleurs de remplissage et de contour pour chaque secteur
    sliceBasSalaire->setBrush(QColor("#F849F1"));
    sliceBasSalaire->setPen(QPen(QColor("#F849F1"), 2));

    sliceMoyenSalaire->setBrush(QColor("#1EC8DF"));
    sliceMoyenSalaire->setPen(QPen(QColor("#1EC8DF"), 2));

    sliceHautSalaire->setBrush(QColor("#FFD700"));
    sliceHautSalaire->setPen(QPen(QColor("#FFD700"), 2));

    series->append(sliceBasSalaire);
    series->append(sliceMoyenSalaire);
    series->append(sliceHautSalaire);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique de salaire des employés");




    // Itère sur tous les secteurs et effectue les mêmes modifications
    for (QPieSlice *slice : series->slices()) {
        slice->setExploded();
        slice->setLabelVisible();

        // Calcul du pourcentage et mise à jour de l'étiquette
        double percentage = slice->percentage();
        QString label = QString("%1 (%2%)").arg(slice->label()).arg(percentage * 100, 0, 'f', 1);
        slice->setLabel(label);

    }

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}













bool Employes::vin_existe(QString vin)
{
        QSqlQuery query;
        query.prepare("SELECT vin FROM VOITUREELECTRIQUE WHERE vin = :vin");
        query.bindValue(":vin", vin);
        return query.exec() && query.first();
}



bool Employes::id_reclamation_existe(int id_reclamation)
{
    QSqlQuery query;
    query.prepare("SELECT RECLAMATION_ID FROM RECLAMATION WHERE RECLAMATION_ID = :id_reclamation");
    query.bindValue(":id_reclamation", id_reclamation);
    return query.exec() && query.first();
}


QSqlQueryModel * Employes::afficher_employe_du_mois()
{
    QSqlQuery query;
        query.prepare("SELECT EMPLOYES_ID, COUNT(*) AS repetitions FROM GESTION GROUP BY EMPLOYES_ID ORDER BY COUNT(*) DESC");

        if (query.exec()) {
            QSqlQueryModel *model = new QSqlQueryModel();
            model->setQuery(query);
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("employes_id"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("nombre de voitures"));
            return model;
        }

        return nullptr;
}







