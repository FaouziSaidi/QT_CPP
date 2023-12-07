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

QSqlQueryModel* fournisseurs::trierNom()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from FOURNISSEUR ORDER BY NOMFOURNISSEUR");
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
}
QSqlQueryModel* fournisseurs::triercat()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from FOURNISSEUR ORDER BY CATEGORIESPRODUITSSERVICES");
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
}

QSqlQueryModel* fournisseurs::trierid()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from FOURNISSEUR ORDER BY FOURNISSEUR_ID");
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
}

void fournisseurs::pdf(){
QPdfWriter pdf("C:\\Users\\samia\\Documents\\projet_fournisseur\\import.pdf");
                    QPainter painter(&pdf);
                   int i = 4000;
                        painter.setPen(Qt::blue);
                        painter.setFont(QFont("Arial", 30));
                        painter.drawText(1100,1200,"GESTION FOURNISSEURS");
                        painter.setPen(Qt::black);
                        painter.setFont(QFont("Arial",14));
                        painter.drawRect(100,100,7300,2600);
                        painter.drawRect(0,3000,9600,500);
                        painter.setFont(QFont("Arial",8));
                        painter.drawText(200,3300,"ID");
                        painter.drawText(1200,3300,"NOM");
                        painter.drawText(2200,3300,"EMAIL");
                        painter.drawText(3200,3300,"ADRESSE");
                        painter.drawText(4200,3300,"CATEGORIE");
                        painter.drawText(6200,3300,"PAIEMENT");
                        painter.drawText(7200,3300,"REPUFOURNISSEUR");
                         painter.drawText(8200,3300,"HISTORIQUE");
                          painter.drawText(9200,3300,"NUMERO");



                        QSqlQuery query;
                       // query.prepare("select * from FOURNISSEUR where FOURNISSEUR_ID='"+val+"'");
                        query.prepare("select * from FOURNISSEUR");
                        query.exec();
                        while (query.next())
                        {
                            painter.drawText(200,i,query.value(0).toString());
                            painter.drawText(1200,i,query.value(1).toString());
                            painter.drawText(2200,i,query.value(2).toString());
                            painter.drawText(3200,i,query.value(3).toString());
                            painter.drawText(4200,i,query.value(4).toString());
                            painter.drawText(6200,i,query.value(5).toString());
                            painter.drawText(7200,i,query.value(6).toString());
                            painter.drawText(8200,i,query.value(7).toString());
                            painter.drawText(9300,i,query.value(8).toString());




                           i = i + 500;
                        }}


void fournisseurs::recherche(QTableView * tableView ,int FOURNISSEUR_ID,QString NOMFOURNISSEUR, QString CATEGORIESPRODUITSSERVICES )
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QString id_fournisseur_string=QString::number(FOURNISSEUR_ID);



    QSqlQuery *query=new QSqlQuery;
    query->prepare("select * from FOURNISSEUR where FOURNISSEUR_ID like '%"+id_fournisseur_string+"%' or NOMFOURNISSEUR like '%"+NOMFOURNISSEUR+"%' or CATEGORIESPRODUITSSERVICES like '%"+CATEGORIESPRODUITSSERVICES+"%' ;");


    query->exec();
    model->setQuery(*query);
    tableView->setModel(model);
    tableView->show();




}
QSqlQueryModel * fournisseurs::afficherHistorique()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from HISTORIQUE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("DATEE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ETAT"));

    return model;
}
