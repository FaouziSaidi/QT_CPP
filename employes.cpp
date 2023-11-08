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


// Fonction pour générer un graphique en secteurs (camembert) personnalisé
QChartView* Employes::statistiques()
{



    QSqlQuery query;
    int totalEmployees = 0;
    int maleCount = 0;
    int femaleCount = 0;

    // Query the database to count the total number of employees and separate them by genre
    if (query.exec("SELECT COUNT(*) FROM employes")) {
        if (query.next()) {
            totalEmployees = query.value(0).toInt();
        }
    }

    if (query.exec("SELECT COUNT(*) FROM employes WHERE genre = 'Homme'")) {
        if (query.next()) {
            maleCount = query.value(0).toInt();
        }
    }

    if (query.exec("SELECT COUNT(*) FROM employes WHERE genre = 'Femme'")) {
        if (query.next()) {
            femaleCount = query.value(0).toInt();
        }
    }

    // Calculate the percentages
    double pourc_homme = (static_cast<double>(maleCount) / totalEmployees) * 100;
    double pourc_femme = (static_cast<double>(femaleCount) / totalEmployees) * 100;
    QPieSeries *series = new QPieSeries();
    QPieSlice *slicefemme = new QPieSlice("FEMME",pourc_femme);
    QPieSlice *sliceHomme = new QPieSlice("HOMME",pourc_homme);

    // Définir les couleurs de remplissage et de contour pour chaque secteur
    slicefemme->setBrush(QColor("#F849F1")); // Couleur bleu-vert
    slicefemme->setPen(QPen(QColor("#F849F1"), 2)); // Couleur bleu-vert pour le contour

    sliceHomme->setBrush(QColor("#1EC8DF")); // Couleur rouge orangé
    sliceHomme->setPen(QPen(QColor("#1EC8DF"), 2)); // Couleur rouge orangé pour le contour

    series->append(slicefemme);
    series->append(sliceHomme);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique Hommes/Femme");

    // Calcule les pourcentages
    double total = 0;
    for (QPieSlice *slice : series->slices()) {
        total += slice->value();
    }

    // Itère sur tous les secteurs et effectue les mêmes modifications
    for (QPieSlice *slice : series->slices()) {
        slice->setExploded();
        slice->setLabelVisible();

        // Calcul du pourcentage et mise à jour de l'étiquette
        double percentage = (slice->value() / total) * 100;
        QString label = QString("%1 (%2%)").arg(slice->label()).arg(percentage, 0, 'f', 1);
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
/*
int Employes::employes_du_mois()
{

    QSqlQuery query;
       query.prepare("SELECT employe_id, COUNT(vin) AS cars_count "
                     "FROM gestion "
                     "GROUP BY employe_id "
                     "ORDER BY cars_count DESC "
                     "LIMIT 1");

       if (query.exec() && query.first()) {
           int employeeId = query.value("employe_id").toInt();
           return employeeId;
       }

       return -1;
}
*/


QSqlQueryModel * Employes::afficher_employe_du_mois()
{
    QSqlQuery query;
        query.prepare("SELECT EMPLOYES_ID, COUNT(*) AS repetitions FROM GESTION GROUP BY EMPLOYES_ID");

        if (query.exec()) {
            QSqlQueryModel *model = new QSqlQueryModel();
            model->setQuery(query);
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("employes_id"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("nombre de voitures"));
            return model;
        }

        return nullptr;
}







