#ifndef RECLAMATION_H
#define RECLAMATION_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QTableView>
#include <QtDebug>
#include <QtSql>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>

class reclamation
{
public:
    reclamation();
    reclamation(int,QString,QString,QString,QString);
    int getid();
    QString getdate();
    QString getstatut();
    QString getnom();
    QString getdescr();

    void setid(int);
    void setdate(QString);
    void setstatu(QString);
    void setnom(QString);
    void setdescr(QString);
    bool ajouter();
           QSqlQueryModel* afficher();
           bool supprimer(int);
           bool modifier(int,QString,QString,QString,QString);
           void recherche(QTableView * tableView,int);
           QSqlQueryModel * trierId_rect();
           void telechargerPDF();
           void on_statistique_clicked();
           QSqlQueryModel * afficherHistorique();


private:
int ID_RECLAMATION;
QString DATEE,NOM_CLIENT,DESCRIPTION_REC,STATUT;

};

#endif // RECLAMATION_H
