#ifndef STATION_H
#define STATION_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QTableView>
#include <QtCharts/QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
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

class station
{
public:
    station();
    station(int,QString,QString,QString,QString);
    int getID(){return ID ;}
    QString getEMPLACEMENT(){return EMPLACEMENT ;}
         QString getSTATUT(){return STATUT ;}
         QString getTYPE(){return TYPE ;}
         QString getCOMMENTAIRE(){return COMMENTAIRE;}




         void setID(int);
         void setEMPLACEMENT(QString);
         void setSTATUT(QString);
         void setTYPE(QString);
         void setCOMMENTAIRE(QString);



         bool ajouter();
         QSqlQueryModel* afficher();
         bool supprimer(int);
         bool modifier(int,QString,QString,QString,QString);
         void recherche(QTableView * affiche_tab, int);

                 QSqlQueryModel * trierId();
void telechargerPDF();
double calculerMoyenneID();
QMap<QString, int> getquantiteStatistics();
QMap<QString, int> getTypeStatistics();
void displayTypeStatisticsGraph();
QChartView* getTypeStatisticsChart();




private:
         int ID;
         QString EMPLACEMENT,STATUT,TYPE,COMMENTAIRE;


};

#endif // station_H
