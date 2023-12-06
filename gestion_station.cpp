#include "gestion_station.h"
#include "ui_gestion_station.h"
#include "station.h"
#include <vector>
#include <string>
#include <QBuffer>
#include <cstdlib>
#include <ctime>
#include <QSqlError>
#include<QDebug>
#include<QImage>
#include <QPixmap>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include<QTextDocument>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrinterInfo>
#include <QPrintDialog>
#include <QGraphicsView>
#include <QTabWidget>
#include <QStandardItemModel>
#include <QSqlQuery>



gestion_station::gestion_station(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestion_station)

{
    station f;
    ui->setupUi(this);
ui->affiche_tab->setModel(f.afficher());


}



gestion_station::~gestion_station()
{
    delete ui;
}
void gestion_station::on_ajouter_clicked(){
    QString ID_string = ui->ID->text();
      bool ok;
      int ID = ID_string.toInt(&ok);

      if (!ok) {

          QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer ID.");
          return;
      }
      QString EMPLACEMENT = ui->EMPLACEMENT->text();

      QString STATUT = ui->STATUT->text();

      QString TYPE = ui->TYPE->text();
      QString COMMENTAIRE = ui->COMMENTAIRE->text();

      station tr(ID,EMPLACEMENT,STATUT,TYPE,COMMENTAIRE);
      bool test = tr.ajouter();

      QMessageBox msgBox;
      if (test) {
          msgBox.setText("ajout avec succes");
          msgBox.exec();
          ui->ID->clear();
          ui->EMPLACEMENT->clear();
          ui->STATUT->clear();
          ui->TYPE->clear();
          ui->COMMENTAIRE->clear();



      } else {
          msgBox.setText("echec");
          msgBox.exec();
      }

      ui->affiche_tab->setModel(tr.afficher());
};
void gestion_station::on_supprimer_clicked() {
    station f;
    int ID= ui->ID->text().toInt();
    bool test = f.supprimer(ID);
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Suppression effectuée.\n"
                                             "Click Ok to exit."), QMessageBox::Ok);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                              QObject::tr("Échec de la suppression.\n"
                                          "Le fournisseur n'existe pas dans la base de données."),
                              QMessageBox::Cancel);
    }
    ui->affiche_tab->setModel(f.afficher());
}


void gestion_station::on_modifier_clicked()
{

        int ID=ui->ID->text().toInt();
           QString EMPLACEMENT = ui->EMPLACEMENT->text();
           QString STATUT = ui->STATUT->text();
           QString TYPE = ui->TYPE->text();
           QString COMMENTAIRE = ui->COMMENTAIRE->text();






              station f(ID,EMPLACEMENT,STATUT,TYPE,COMMENTAIRE);

                 bool test=f.modifier(ID,EMPLACEMENT,STATUT,TYPE,COMMENTAIRE);

                 if(test)

               {ui->affiche_tab->setModel(f.afficher());

               QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),

                                 QObject::tr("invite modifiée.\n"

                                             "Click ok to exit."), QMessageBox::Ok);



               }

                 else

                     QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),

                                 QObject::tr("echec d'ajout !.\n"

                                             "Click Cancel to exit."), QMessageBox::Cancel);


}


void gestion_station::on_afficher_clicked()
{
    station f;
    ui->affiche_tab->setModel(f.afficher());
}


void gestion_station::on_affiche_tab_activated(const QModelIndex &index)
{
    QString val=ui->affiche_tab->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from GESTION_STATION where ID='"+val+"'");
    if(qry.exec())
    {
     while(qry.next())
     {ui->ID->setText(qry.value(0).toString());
      ui->EMPLACEMENT->setText(qry.value(1).toString());
      ui->STATUT->setText(qry.value(2).toString());
      ui->TYPE->setText(qry.value(3).toString());
      ui->COMMENTAIRE->setText(qry.value(4).toString());


     }
    }
    else
    {
     QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}

void gestion_station::on_telechargerPDF_clicked()
{
    station f;
    f.telechargerPDF();

             QMessageBox::information(nullptr,QObject::tr("OK"),
                        QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);
}
void gestion_station::on_trier_clicked()
{
    station f;
     ui->affiche_tab->setModel(f.trierId());
}

void gestion_station::on_chercher_textChanged(const QString &arg1)
{

    station f;
    int ID= ui->chercher->text().toInt();

  f.recherche(ui->affiche_tab,ID);
    if (ui->chercher->text().isEmpty())
    {
        ui->affiche_tab->setModel(f.afficher());
    }
}



void gestion_station::on_stat_clicked()
{
    QLayoutItem* item;
    while((item=ui->horizontalLayout->takeAt(0))!=0)
    {

    delete item->widget();
          delete item;
    }
    station f;
    QChartView *chartView = f.getTypeStatisticsChart();

    // Assuming you have a widget to display the chart (e.g., QFrame named chartFrame)
    ui->horizontalLayout->addWidget(chartView);
}

