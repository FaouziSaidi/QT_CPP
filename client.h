#ifndef CLIENT_H
#define CLIENT_H
#include <QDate>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QTableView>
#include<QString>
#include <QPdfWriter>
#include <QPainter>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QVariant>
#include <QObject>
#include <Qt>


class Client
{
private:
    int USER_ID,NUMBER_TELEPHONE;
    QString NOM,PRENOM,AVIS_APPLICATION,MAIL;
    QDate DATEE;

public:
    Client();
    Client (int USER_ID, int NUMBER_TELEPHONE,QString NOM, QString PRENOM,QString AVIS_APPLICATION,QString MAIL,QDate DATEE);


    //METHODS

        bool ajouter_c();
        bool supprimer_c(int USER_ID);
        QSqlQueryModel * afficher_c();
        bool modifier_c(int USER_ID, int NUMBER_TELEPHONE,QString NOM, QString PRENOM,QString AVIS_APPLICATION, QString MAIL,QDate DATEE);
        void rechercher(QTableView * tableView, int);
        //void birthdayCheck (QDate, INT);


    //getters
       int getUSER_ID();
       int getNUMBER_TELEPHONE();
       QDate getDATE();
       QString getNOM();
       QString getPRENOM();
       QString getMAIL();
       QString getAVIS_APPLICATION();

    //setters
       void setUSER_ID(int USER_ID);
       void setNUMBER_PHONE(int NUMBER_TELEPHONE);
       void setNOM (QString NOM);
       void setPRENOM (QString PRENOM);
       void setAVIS_APPLICATION(QString AVIS_APPLICATION );
       void setMAIL (QString MAIL);
       void setDATE (QDate DATEE);

};

#endif // CLIENT_H
