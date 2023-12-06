#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QTableView>


class fournisseurs
{
public:
    fournisseurs();
        fournisseurs(int,QString,QString,QString,QString,QString,QString,QString,QString);
        int getFOURNISSEUR_ID();

           QString getNOMFOURNISSEUR();
           QString getEMAIL();
           QString getADRESSE();
           QString getCATEGORIESPRODUITSSERVICES();
           QString getMODALITEPAIEMENT();
           QString getREPUTATIONFOURNISSEUR();
           QString getHISTORIQUECOMMANDES();
           QString getNUMEROTELEPHONE();


            void setFOURNISSEUR_ID(int);
            void setNOMFOURNISSEUR(QString);
            void setEMAIL(QString);
            void setADRESSE(QString);
            void setCATEGORIESPRODUITSSERVICES(QString);
            void setMODALITEPAIEMENT(QString);
            void setREPUTATIONFOURNISSEUR(QString);
            void setHISTORIQUECOMMANDES(QString);
            void setNUMEROTELEPHONE(QString);

            bool ajouter();
            QSqlQueryModel* afficher();
            bool supprimer(int);
            bool modifier(int ,QString ,QString ,QString ,QString ,QString ,QString ,QString ,QString );
            void recherche(QTableView * affiche_tab, int,QString,QString);
            QSqlQueryModel * trierNom();
            QSqlQueryModel * triercat();
            QSqlQueryModel* trierid();
            QSqlQueryModel * afficherHistorique();
           void pdf();
          private:
           int FOURNISSEUR_ID;
           QString NOMFOURNISSEUR,EMAIL,ADRESSE,CATEGORIESPRODUITSSERVICES,MODALITEPAIEMENT,REPUTATIONFOURNISSEUR,HISTORIQUECOMMANDES,NUMEROTELEPHONE;
};

#endif // FOURNISSEURS_H
