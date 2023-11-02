#include "fournisseurs.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlError>
#include <string>
#include <QPdfWriter>
#include <QPainter>


fournisseurs::fournisseurs()
    {
        FOURNISSEUR_ID=0;
        NOMFOURNISSEUR="";
        EMAIL="";
        ADRESSE="";
        CATEGORIESPRODUITSSERVICES="";
        MODALITEPAIEMENT="";
        REPUTATIONFOURNISSEUR="";
        HISTORIQUECOMMANDES="";
        NUMEROTELEPHONE="";
    }
fournisseurs::fournisseurs(int FOURNISSEUR_ID,QString NOMFOURNISSEUR,QString EMAIL,QString ADRESSE,QString CATEGORIESPRODUITSSERVICES,QString MODALITEPAIEMENT,QString REPUTATIONFOURNISSEUR,QString HISTORIQUECOMMANDES,QString NUMEROTELEPHONE)
{this->FOURNISSEUR_ID=FOURNISSEUR_ID;this->NOMFOURNISSEUR=NOMFOURNISSEUR;this->EMAIL=EMAIL;this->ADRESSE=ADRESSE;this->CATEGORIESPRODUITSSERVICES=CATEGORIESPRODUITSSERVICES;this->MODALITEPAIEMENT=MODALITEPAIEMENT;this->REPUTATIONFOURNISSEUR=REPUTATIONFOURNISSEUR;this->HISTORIQUECOMMANDES=HISTORIQUECOMMANDES;this->NUMEROTELEPHONE=NUMEROTELEPHONE;}
int fournisseurs::getFOURNISSEUR_ID(){return FOURNISSEUR_ID;}
QString fournisseurs::getNOMFOURNISSEUR(){return NOMFOURNISSEUR;}
QString fournisseurs::getEMAIL(){return EMAIL;}
QString fournisseurs::getADRESSE(){return ADRESSE;}
QString fournisseurs::getCATEGORIESPRODUITSSERVICES(){return CATEGORIESPRODUITSSERVICES;}
QString fournisseurs::getMODALITEPAIEMENT(){return MODALITEPAIEMENT;}
QString fournisseurs::getREPUTATIONFOURNISSEUR(){return REPUTATIONFOURNISSEUR;}
QString fournisseurs::getHISTORIQUECOMMANDES(){return HISTORIQUECOMMANDES;}
QString fournisseurs::getNUMEROTELEPHONE(){return NUMEROTELEPHONE;}


void fournisseurs::setFOURNISSEUR_ID(int FOURNISSEUR_ID){this->FOURNISSEUR_ID=FOURNISSEUR_ID;}
void fournisseurs::setNOMFOURNISSEUR(QString NOMFOURNISSEUR){this->NOMFOURNISSEUR=NOMFOURNISSEUR;}
void fournisseurs::setEMAIL(QString EMAIL){this->EMAIL=EMAIL;}
void fournisseurs::setADRESSE(QString ADRESSE){this->ADRESSE=ADRESSE;}
void fournisseurs::setCATEGORIESPRODUITSSERVICES(QString CATEGORIESPRODUITSSERVICES){this->CATEGORIESPRODUITSSERVICES=CATEGORIESPRODUITSSERVICES;}
void fournisseurs::setMODALITEPAIEMENT(QString MODALITEPAIEMENT){this->MODALITEPAIEMENT=MODALITEPAIEMENT;}
void fournisseurs::setREPUTATIONFOURNISSEUR(QString REPUTATIONFOURNISSEUR){this->REPUTATIONFOURNISSEUR=REPUTATIONFOURNISSEUR;}
void fournisseurs::setHISTORIQUECOMMANDES(QString HISTORIQUECOMMANDES){this->HISTORIQUECOMMANDES=HISTORIQUECOMMANDES;}
void fournisseurs::setNUMEROTELEPHONE(QString NUMEROTELEPHONE){this->NUMEROTELEPHONE=NUMEROTELEPHONE;}


bool fournisseurs::ajouter()
{
    QSqlQuery query;
    QString FOURNISSEUR_ID_string=QString::number(FOURNISSEUR_ID);


         query.prepare("INSERT INTO FOURNISSEUR (FOURNISSEUR_ID, NOMFOURNISSEUR,EMAIL,ADRESSE,CATEGORIESPRODUITSSERVICES,MODALITEPAIEMENT,REPUTATIONFOURNISSEUR,HISTORIQUECOMMANDES,NUMEROTELEPHONE) "
                       "VALUES (:FOURNISSEUR_ID,:NOMFOURNISSEUR,:EMAIL,:ADRESSE,:CATEGORIESPRODUITSSERVICES,:MODALITEPAIEMENT,:REPUTATIONFOURNISSEUR,:HISTORIQUECOMMANDES,:NUMEROTELEPHONE)");
         query.bindValue(":FOURNISSEUR_ID",FOURNISSEUR_ID_string);
         query.bindValue(":NOMFOURNISSEUR",NOMFOURNISSEUR);
         query.bindValue(":EMAIL",EMAIL);
         query.bindValue(":ADRESSE",ADRESSE);
         query.bindValue(":CATEGORIESPRODUITSSERVICES",CATEGORIESPRODUITSSERVICES);
         query.bindValue(":MODALITEPAIEMENT",MODALITEPAIEMENT);
         query.bindValue(":REPUTATIONFOURNISSEUR",REPUTATIONFOURNISSEUR);
          query.bindValue(":HISTORIQUECOMMANDES",HISTORIQUECOMMANDES);
           query.bindValue(":NUMEROTELEPHONE",NUMEROTELEPHONE);

         return query.exec();

}
QSqlQueryModel* fournisseurs::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


          model->setQuery("SELECT* FROM FOURNISSEUR");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("FOURNISSEUR_ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMFOURNISSEUR"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("EMAIL"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("CATEGORIESPRODUITSSERVICES"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("MODALITEPAIEMENT"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("REPUTATIONFOURNISSEUR"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("HISTORIQUECOMMANDES"));
          model->setHeaderData(8, Qt::Horizontal, QObject::tr("NUMEROTELEPHONE"));




    return model;
};


bool fournisseurs::supprimer(int FOURNISSEUR_ID){
    QSqlQuery query;
    QString res = QString::number(FOURNISSEUR_ID);
    query.prepare("DELETE FROM FOURNISSEUR WHERE FOURNISSEUR_ID=:FOURNISSEUR_ID");
    query.bindValue(":FOURNISSEUR_ID", res);
    if (!query.exec()) {
        return false;  // Failed to execute the query
    }
    if (query.numRowsAffected() == 0) {
        return false;  // No rows were affected
    }
    return true;
}





bool fournisseurs::modifier(int FOURNISSEUR_ID,QString NOMFOURNISSEUR,QString EMAIL,QString ADRESSE,QString CATEGORIESPRODUITSSERVICES,QString MODALITEPAIEMENT,QString REPUTATIONFOURNISSEUR,QString HISTORIQUECOMMANDES,QString NUMEROTELEPHONE)
{
    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM FOURNISSEUR WHERE FOURNISSEUR_ID = :FOURNISSEUR_ID");
         query.bindValue(":FOURNISSEUR_ID", FOURNISSEUR_ID);
         query.exec();
         query.next();
         int count = query.value(0).toInt();
         if (count == 0) {
             // ID_C does not exist in the database, return false
             return false;
         }

         // ID_C exists, execute the update query
         QString FOURNISSEUR_ID_string = QString::number(FOURNISSEUR_ID);
         query.prepare("UPDATE FOURNISSEUR SET NOMFOURNISSEUR = COALESCE(:NOMFOURNISSEUR, NOMFOURNISSEUR), EMAIL = COALESCE(:EMAIL, EMAIL), ADRESSE = COALESCE(:ADRESSE, ADRESSE), CATEGORIESPRODUITSSERVICES = COALESCE(:CATEGORIESPRODUITSSERVICES, CATEGORIESPRODUITSSERVICES), MODALITEPAIEMENT = COALESCE(:MODALITEPAIEMENT, MODALITEPAIEMENT),REPUTATIONFOURNISSEUR = COALESCE(:REPUTATIONFOURNISSEUR, REPUTATIONFOURNISSEUR),HISTORIQUECOMMANDES = COALESCE(:HISTORIQUECOMMANDES, HISTORIQUECOMMANDES),NUMEROTELEPHONE = COALESCE(:NUMEROTELEPHONE, NUMEROTELEPHONE) WHERE FOURNISSEUR_ID = :FOURNISSEUR_ID");
         query.bindValue(":FOURNISSEUR_ID", FOURNISSEUR_ID_string);
         query.bindValue(":NOMFOURNISSEUR", NOMFOURNISSEUR.isEmpty() ? QVariant(QVariant::String) : NOMFOURNISSEUR);
         query.bindValue(":EMAIL", EMAIL.isEmpty() ? QVariant(QVariant::String) : EMAIL);
         query.bindValue(":ADRESSE", ADRESSE.isEmpty() ? QVariant(QVariant::String) : ADRESSE);
         query.bindValue(":CATEGORIESPRODUITSSERVICES", CATEGORIESPRODUITSSERVICES.isEmpty() ? QVariant(QVariant::String) : CATEGORIESPRODUITSSERVICES);
         query.bindValue(":MODALITEPAIEMENT", MODALITEPAIEMENT.isEmpty() ? QVariant(QVariant::String) : MODALITEPAIEMENT);
         query.bindValue(":REPUTATIONFOURNISSEUR", REPUTATIONFOURNISSEUR.isEmpty() ? QVariant(QVariant::String) : REPUTATIONFOURNISSEUR);
          query.bindValue(":HISTORIQUECOMMANDES", HISTORIQUECOMMANDES.isEmpty() ? QVariant(QVariant::String) : HISTORIQUECOMMANDES);
           query.bindValue(":NUMEROTELEPHONE", NUMEROTELEPHONE.isEmpty() ? QVariant(QVariant::String) : NUMEROTELEPHONE);

         return query.exec();
}
