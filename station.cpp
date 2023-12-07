#include "station.h"
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlError>
#include <string>
#include <QPdfWriter>
#include <QPainter>
//constrecteur pardefaut
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QValueAxis>
#include<QChartView>
#include<QChart>
#include <QBarSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts>

station::station()
{


     ID=0;
     EMPLACEMENT="";
     STATUT="";
     TYPE="";
     COMMENTAIRE="";



}
//constrecteur parametre
station::station(int ID,QString EMPLACEMENT,QString STATUT,QString TYPE,QString COMMENTAIRE)
{
     this->ID=ID;
     this->EMPLACEMENT=EMPLACEMENT;
     this->STATUT=STATUT;
     this->TYPE=TYPE;
     this->COMMENTAIRE=COMMENTAIRE;




}

void station::setID(int ID){this->ID=ID;}
void station::setEMPLACEMENT(QString EMPLACEMENT){this->EMPLACEMENT=EMPLACEMENT;}
void station::setSTATUT(QString STATUT){this->STATUT=STATUT;}
void station::setTYPE( QString TYPE){this->TYPE=TYPE;}
void station::setCOMMENTAIRE( QString COMMENTAIRE){this->COMMENTAIRE=COMMENTAIRE;}

bool station::ajouter()
{
    QSqlQuery query;
    QString ID_string=QString::number(ID);


         query.prepare("INSERT INTO GESTION_STATION (ID,EMPLACEMENT,STATUT,TYPE,COMMENTAIRE) "
                       "VALUES (:ID,:EMPLACEMENT,:STATUT,:TYPE,:COMMENTAIRE)");
         query.bindValue(":ID",ID_string);
         query.bindValue(":EMPLACEMENT",EMPLACEMENT);
         query.bindValue(":STATUT",STATUT);
         query.bindValue(":TYPE",TYPE);
         query.bindValue(":COMMENTAIRE",COMMENTAIRE);



         return query.exec();

}
QSqlQueryModel* station::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


          model->setQuery("SELECT* FROM GESTION_STATION");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("EMPLACEMENT"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("STATUT"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("COMMENTAIRE"));






    return model;
};
bool station::supprimer(int ID){
    QSqlQuery query;
    QString res = QString::number(ID);
    query.prepare("DELETE FROM GESTION_STATION WHERE ID=:ID");
    query.bindValue(":ID", res);
    if (!query.exec()) {
        return false;  // Failed to execute the query
    }
    if (query.numRowsAffected() == 0) {
        return false;  // No rows were affected
    }
    return true;
}


bool station::modifier(int ID,QString EMPLACEMENT,QString STATUT,QString TYPE,QString COMMENTAIRE)
{
    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM GESTION_STATION WHERE ID = :ID");
         query.bindValue(":ID", ID);
         query.exec();
         query.next();
         int count = query.value(0).toInt();
         if (count == 0) {
             return false;
         }

         QString ID_string = QString::number(ID);
         query.prepare("UPDATE GESTION_STATION SET EMPLACEMENT = COALESCE(:EMPLACEMENT, EMPLACEMENT), STATUT = COALESCE(:STATUT, STATUT),TYPE = COALESCE(:TYPE, TYPE),,COMMENTAIRE= COALESCE(:COMMENTAIRE, COMMENTAIRE) WHERE ID = :ID");
         query.bindValue(":ID", ID_string);
         query.bindValue(":EMPLACEMENT", EMPLACEMENT.isEmpty() ? QVariant(QVariant::String) : EMPLACEMENT);
         query.bindValue(":STATUT", STATUT.isEmpty() ? QVariant(QVariant::String) : STATUT);
         query.bindValue(":TYPE", TYPE.isEmpty() ? QVariant(QVariant::String) : TYPE);
         query.bindValue(":COMMENTAIRE",COMMENTAIRE.isEmpty() ? QVariant(QVariant::String) : COMMENTAIRE);





         return query.exec();
}
QSqlQueryModel* station::trierId()
{
    // Crée un nouveau modèle de requête SQL
    QSqlQueryModel * model=new QSqlQueryModel();

    // Exécute une requête SQL pour sélectionner tous les enregistrements de la table GESTION_STATION, triés par ID
    model->setQuery("select * from GESTION_STATION ORDER BY ID");

    // Définit les en-têtes des colonnes dans le modèle
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("EMPLACEMENT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("STATUT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("COMMENTAIRE"));


    return model;
}

void station::recherche(QTableView * affiche_tab ,int ID)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QString ID_string=QString::number(ID);



    QSqlQuery *query=new QSqlQuery;
    query->prepare("select * from GESTION_STATION where ID like '%"+ID_string+"%';");


    query->exec();
    model->setQuery(*query);
    affiche_tab->setModel(model);
    affiche_tab->show();

}


void  station::telechargerPDF(){

                     QPdfWriter pdf("C:\\Users\\KINZA\\Documents\\tache\\import.pdf");
                     QPainter painter(&pdf);
                    int i = 4000;
                         painter.setPen(Qt::blue);
                         painter.setFont(QFont("Arial", 30));
                         painter.drawText(1100,1200,"GESTION GESTION_STATION");
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Arial",14));
                         painter.drawRect(100,100,7300,2600);
                         painter.drawRect(0,3000,9600,500);
                         painter.setFont(QFont("Arial",8));
                         painter.drawText(300,3300,"ID");
                         painter.drawText(1300,3300,"EMPLACEMENT");
                         painter.drawText(2200,3300,"STATUT");
                         painter.drawText(3200,3300,"TYPE");
                         painter.drawText(4200,3300,"COMMENTAIRE");






                         QSqlQuery query;
                        // query.prepare("select * from GESTION_STATION where ID='"+val+"'");
                         query.prepare("select * from GESTION_STATION");
                         query.exec();
                         while (query.next())
                         {
                             painter.drawText(300,i,query.value(0).toString());
                             painter.drawText(1300,i,query.value(1).toString());
                             painter.drawText(2300,i,query.value(2).toString());
                             painter.drawText(3300,i,query.value(3).toString());
                             painter.drawText(4300,i,query.value(4).toString());




                            i = i + 500;
                         }}




QChartView* station::getTypeStatisticsChart()
{

    QChart *chart = new QChart();
    QBarSeries *series = new QBarSeries();

    QSqlQuery query;
    query.prepare("SELECT TYPE, COUNT(*) FROM GESTION_STATION GROUP BY TYPE");
    query.exec();

    while (query.next()) {
        QString type = query.value(0).toString();
        int count = query.value(1).toInt();

        QBarSet *set = new QBarSet(type);
        *set << count;
        series->append(set);
    }

    chart->addSeries(series);
    chart->setTitle("Station Types Statistics");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Types";  // You can add more categories if needed
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}


