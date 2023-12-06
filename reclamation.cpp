
#include "reclamation.h"
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlError>
#include <string>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>

#include <QtDebug>
#include <QtSql>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include <QVBoxLayout>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
QT_CHARTS_USE_NAMESPACE



reclamation::reclamation()
{
    ID_RECLAMATION=0;DATEE="";NOM_CLIENT="" ;DESCRIPTION_REC="";STATUT="";

}

reclamation::reclamation(int ID_RECLAMATION,QString DATEE,QString DATEE_CLIENT,QString STATUT,QString DESCRIPTION_REC)
{this ->ID_RECLAMATION=ID_RECLAMATION;this->DATEE=DATEE;this->NOM_CLIENT=DATEE_CLIENT;this->STATUT=STATUT;this->DESCRIPTION_REC=DESCRIPTION_REC;}
int reclamation::getid(){return ID_RECLAMATION;}
QString reclamation::getdate(){return DATEE;}
QString reclamation::getstatut(){return STATUT;}
QString reclamation::getnom(){return NOM_CLIENT;}
QString reclamation::getdescr(){return DESCRIPTION_REC;}

void reclamation::setid(int ID_RECLAMATION){this ->ID_RECLAMATION=ID_RECLAMATION;}
void reclamation::setdate(QString DATEE){this->DATEE=DATEE;}
void reclamation::setstatu(QString STATUT){this->STATUT=STATUT;}
void reclamation::setnom(QString NOM_CLIENT){this->NOM_CLIENT=NOM_CLIENT;}
void reclamation::setdescr(QString DESCRIPTION_REC){this->DESCRIPTION_REC=DESCRIPTION_REC;}


bool reclamation::ajouter()
{
    QSqlQuery query;
    QString ID_RECLAMATION_string=QString::number(ID_RECLAMATION);


         query.prepare("INSERT INTO TABLE1 (ID_RECLAMATION, DATEE,NOM_CLIENT,DESCRIPTION_REC,STATUT) "
                       "VALUES (:ID_RECLAMATION,:DATEE,:NOM_CLIENT,:DESCRIPTION_REC,:STATUT)");
         query.bindValue(":ID_RECLAMATION",ID_RECLAMATION_string);
         query.bindValue(":DATEE",DATEE);
         query.bindValue(":NOM_CLIENT",NOM_CLIENT);
         query.bindValue(":DESCRIPTION_REC",DESCRIPTION_REC);
         query.bindValue(":STATUT",STATUT);

         return query.exec();

}
QSqlQueryModel* reclamation::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


          model->setQuery("SELECT* FROM TABLE1");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RECLAMATION"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATEE"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM_CLIENT"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESCRIPTION_REC"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUT"));





    return model;
};
bool reclamation::supprimer(int ID_RECLAMATION){
    QSqlQuery query;
    QString res = QString::number(ID_RECLAMATION);
    query.prepare("DELETE FROM TABLE1 WHERE ID_RECLAMATION=:ID_RECLAMATION");
    query.bindValue(":ID_RECLAMATION", res);
    if (!query.exec()) {
        return false;  // Failed to execute the query
    }
    if (query.numRowsAffected() == 0) {
        return false;  // No rows were affected
    }
    return true;
}





bool reclamation::modifier(int ID_RECLAMATION,QString DATEE,QString NOM_CLIENT,QString DESCRIPTION_REC,QString STATUT)
{
    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM TABLE1 WHERE ID_RECLAMATION = :ID_RECLAMATION");
         query.bindValue(":ID_RECLAMATION", ID_RECLAMATION);
         query.exec();
         query.next();
         int count = query.value(0).toInt();
         if (count == 0) {
             return false;
         }
         QString id_c_string = QString::number(ID_RECLAMATION);
         query.prepare("UPDATE TABLE1 SET DATEE = COALESCE(:DATEE, DATEE), NOM_CLIENT = COALESCE(:NOM_CLIENT, NOM_CLIENT), STATUT = COALESCE(:STATUT, STATUT), DESCRIPTION_REC = COALESCE(:DESCRIPTION_REC, DESCRIPTION_REC) WHERE ID_RECLAMATION = :ID_RECLAMATION");
         query.bindValue(":ID_RECLAMATION", id_c_string);
         query.bindValue(":DATEE", DATEE.isEmpty() ? QVariant(QVariant::String) : DATEE);
         query.bindValue(":NOM_CLIENT", NOM_CLIENT.isEmpty() ? QVariant(QVariant::String) : NOM_CLIENT);
         query.bindValue(":DESCRIPTION_REC", DESCRIPTION_REC.isEmpty() ? QVariant(QVariant::String) : DESCRIPTION_REC);
         query.bindValue(":STATUT", STATUT.isEmpty() ? QVariant(QVariant::String) : STATUT);

         return query.exec();
}

void reclamation::recherche(QTableView * tableView ,int ID_RECLAMATION )
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QString ID_RECLAMATION_string=QString::number(ID_RECLAMATION);


    QSqlQuery *query=new QSqlQuery;
    query->prepare("select * from TABLE1 where ID_RECLAMATION like '%"+ID_RECLAMATION_string+"%';");
    query->exec();
    model->setQuery(*query);
    tableView->setModel(model);
    tableView->show();
}

QSqlQueryModel* reclamation::trierId_rect()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from TABLE1 ORDER BY ID_RECLAMATION");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID_RECLAMATION"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("DATEE"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("NOM_CLIENT"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("DESCRIPTION_REC"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("STATUT"));


    return model;
}
void  reclamation::telechargerPDF(){

                     QPdfWriter pdf("C:\\Users\\21653\\Documents\\gestion_recla\\base.pdf");
                     QPainter painter(&pdf);
                    int i = 4000;
                         painter.setPen(Qt::blue);
                         painter.setFont(QFont("Arial", 30));
                         painter.drawText(1100,1200,"GESTION reclamation");
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Arial",14));
                         painter.drawRect(100, 100, 7300, 2600);
                         painter.drawRect(0, 3000, 9600, 500);
                         painter.setFont(QFont("Arial",8));
                         painter.drawText(150, 3250, "ID_RECLAMATION");
                         painter.drawText(1400, 3250, "DATEE");
                         painter.drawText(2300, 3250, "NOM_CLIENT");
                         painter.drawText(3300, 3250, "DESCRIPTION_REC");
                         painter.drawText(4300, 3250, "STATUT");

                         QSqlQuery query;
                         query.prepare("select * from TABLE1");
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


QSqlQueryModel * reclamation::afficherHistorique()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from HISTORIQUE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("DATEE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ETATRECLAMATION"));

    return model;
}
