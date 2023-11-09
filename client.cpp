#include "client.h"
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlError>
#include <string>
#include <QPdfWriter>
#include <QPainter>
#include <QPushButton>
#include <QString>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QVariant>
#include <QObject>
#include <Qt>

Client::Client()
{

}

Client::Client(int USER_ID, int NUMBER_TELEPHONE,QString NOM, QString PRENOM,QString AVIS_APPLICATION,QString MAIL, QDate DATEE)
{
    this->USER_ID=USER_ID;
    this->NUMBER_TELEPHONE=NUMBER_TELEPHONE;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->AVIS_APPLICATION=AVIS_APPLICATION;
    this->MAIL=MAIL;
    this->DATEE=DATEE;
}

bool Client::supprimer_c (int USER_ID)
{
        QSqlQuery query;
         query.prepare("Delete from Client where USER_ID= :USER_ID");
         query.bindValue(":USER_ID",USER_ID);
         return query.exec();
}



bool Client::ajouter_c(){

    QSqlQuery query;

    QString res= QString::number(USER_ID);

    query.prepare("insert into Client (USER_ID,NOM,PRENOM,DATEE,NUMBER_TELEPHONE,MAIL,AVIS_APPLICATION)" "values(:USER_ID,:NOM,:PRENOM,:DATEE,:NUMBER_TELEPHONE,:MAIL,:AVIS_APPLICATION)");

    query.bindValue(":USER_ID", res);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM",PRENOM);
    query.bindValue(":DATEE", DATEE);
    query.bindValue(":NUMBER_TELEPHONE", NUMBER_TELEPHONE);
    query.bindValue(":MAIL", MAIL);
    query.bindValue(":AVIS_APPLICATION", AVIS_APPLICATION);

    return query.exec(); //envoyer la requete pour executer
}

QSqlQueryModel * Client :: afficher_c()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from Client ORDER BY NOM");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("USER_ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATEE"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("TELEPHONE_NUMBER"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("MAIL"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("AVIS_APPLICATION"));
return model;

}



bool Client:: modifier_c(int USER_ID, int NUMBER_TELEPHONE,QString NOM, QString PRENOM,QString AVIS_APPLICATION, QString MAIL, QDate DATEE)
 {
         QSqlQuery query;

         query.prepare("UPDATE CLIENT SET USER_ID=:USER_ID , NOM=:NOM, PRENOM=:PRENOM,  DATEE=:DATEE , NUMBER_TELEPHONE=:NUMBER_TELEPHONE, MAIL =:MAIL, AVIS_APPLICATION =:AVIS_APPLICATION  WHERE USER_ID =:USER_ID");
         query.bindValue(":NOM",NOM);
         query.bindValue(":PRENOM", PRENOM);
         query.bindValue(":USER_ID", USER_ID);
         query.bindValue(":MAIL", MAIL);
         query.bindValue(":NUMBER_TELEPHONE", NUMBER_TELEPHONE);
         query.bindValue(":AVIS_APPLICATION", AVIS_APPLICATION);
         query.bindValue(":DATEE", DATEE);

         return    query.exec();
}

void Client::rechercher(QTableView * tableView, int USER_ID)
{
        QSqlQueryModel *model= new QSqlQueryModel();
        QString USER_ID_string=QString::number(USER_ID);

        QSqlQuery *query=new QSqlQuery;
        query->prepare("select * from CLIENT where USER_ID like '%"+USER_ID_string+"%' ;");

        query->exec();
        model->setQuery(*query);
        tableView->setModel(model);
        tableView->show();
}




int Client::getUSER_ID(){return USER_ID;}
int Client::getNUMBER_TELEPHONE(){return NUMBER_TELEPHONE;}
QDate Client::getDATE(){return DATEE;}
QString Client::getNOM(){return NOM;}
QString Client::getPRENOM(){return PRENOM;}
QString Client::getMAIL(){return MAIL;}
QString Client::getAVIS_APPLICATION(){return AVIS_APPLICATION;}




void Client::setUSER_ID(int USER_ID){
    this->USER_ID=USER_ID;
}
void Client::setNUMBER_PHONE(int NUMBER_TELEPHONE){
    this->NUMBER_TELEPHONE=NUMBER_TELEPHONE;
}
void Client::setNOM (QString NOM){
    this->NOM=NOM;
}
void Client::setPRENOM (QString PRENOM){
    this->PRENOM=PRENOM;
}
void Client::setAVIS_APPLICATION(QString AVIS_APPLICATION ){
    this->AVIS_APPLICATION=AVIS_APPLICATION;
}

void Client::setMAIL (QString MAIL){
    this->MAIL=MAIL;
}
void Client::setDATE (QDate DATEE){
    this->DATEE=DATEE;
}
