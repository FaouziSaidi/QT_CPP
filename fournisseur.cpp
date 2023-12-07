#include "fournisseur.h"
#include "fournisseurs.h"
#include "ui_fournisseur.h"
#include <vector>
#include <string>
#include <QBuffer>
#include <cstdlib>
#include <ctime>
#include <QSqlError>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextDocument>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrinterInfo>
#include <QPrintDialog>
#include <QGraphicsView>
#include <QTabWidget>
#include <QSqlQuery>

#include"notifications.h"




fournisseur::fournisseur(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::fournisseur)
{
    ui->setupUi(this);
}

fournisseur::~fournisseur()
{
    delete ui;
}



void fournisseur::on_ajouter_clicked()
{
    QString FOURNISSEUR_ID_string = ui->FOURNISSEUR_ID->text();
         bool ok;
         int FOURNISSEUR_ID = FOURNISSEUR_ID_string.toInt(&ok);
         if (!ok) {
             // Display error message for invalid input
             QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer for FOURNISSEUR_ID.");
             return;
         }

         QString NOMFOURNISSEUR = ui->NOMFOURNISSEUR->text();
         QString EMAIL = ui->EMAIL->text();
         QString ADRESSE = ui->ADRESSE->text();
         QString CATEGORIESPRODUITSSERVICES = ui->CATEGORIESPRODUITSSERVICES->text();
         QString MODALITEPAIEMENT = ui->MODALITEPAIEMENT->text();
         QString REPUTATIONFOURNISSEUR = ui->REPUTATIONFOURNISSEUR->text();
         QRegularExpression repRegex("^[1-5]$");
         QRegularExpressionMatch match3 = repRegex.match(REPUTATIONFOURNISSEUR);

         if (!match3.hasMatch()) {
             QMessageBox::warning(this, "Invalid REPUTATIONFOURNISSEUR", "Please enter a valid REPUTATIONFOURNISSEUR 1 to 5 only  ");
             return;
         }




         QString HISTORIQUECOMMANDES = ui->HISTORIQUECOMMANDES->text();
         QString NUMEROTELEPHONE = ui->NUMEROTELEPHONE->text();


         fournisseurs tr( FOURNISSEUR_ID,NOMFOURNISSEUR,EMAIL,ADRESSE,CATEGORIESPRODUITSSERVICES,MODALITEPAIEMENT,REPUTATIONFOURNISSEUR,HISTORIQUECOMMANDES,NUMEROTELEPHONE);
         bool test = tr.ajouter();

         QMessageBox msgBox;
         if (test) {
             notification.notification_ajoutfournisseur();
             msgBox.setText("ajout avec succes");
             msgBox.exec();
             ui->FOURNISSEUR_ID->clear();
             ui->NOMFOURNISSEUR->clear();
             ui->EMAIL->clear();
             ui->ADRESSE->clear();
             ui->CATEGORIESPRODUITSSERVICES->clear();
             ui->MODALITEPAIEMENT->clear();
             ui->REPUTATIONFOURNISSEUR->clear();
             ui->HISTORIQUECOMMANDES->clear();
             ui->NUMEROTELEPHONE->clear();

             QSqlQuery qry;
             QDateTime dateTime=QDateTime::currentDateTime();

             qry.prepare("insert into HISTORIQUE (DATEE,ETAT) values (:dateTime,'en cours')");
             qry.bindValue(":dateTime",dateTime);

             qry.exec();

         } else {
             notification.notification_failed();
             msgBox.setText("echec");
             msgBox.exec();
         }

         ui->tableView->setModel(tr.afficher());



}

void fournisseur::on_modifier_clicked()
{
    int FOURNISSEUR_ID=ui->FOURNISSEUR_ID->text().toInt();
               QString NOMFOURNISSEUR = ui->NOMFOURNISSEUR->text();
               QString EMAIL = ui->EMAIL->text();
               QString ADRESSE = ui->ADRESSE->text();
               QString CATEGORIESPRODUITSSERVICES = ui->CATEGORIESPRODUITSSERVICES->text();
               QString MODALITEPAIEMENT = ui->MODALITEPAIEMENT->text();
               QString REPUTATIONFOURNISSEUR = ui->REPUTATIONFOURNISSEUR->text();
               QString HISTORIQUECOMMANDES = ui->HISTORIQUECOMMANDES->text();
               QString NUMEROTELEPHONE = ui->MODALITEPAIEMENT->text();

                  fournisseurs tr( FOURNISSEUR_ID,NOMFOURNISSEUR,EMAIL,ADRESSE,CATEGORIESPRODUITSSERVICES,MODALITEPAIEMENT,REPUTATIONFOURNISSEUR,HISTORIQUECOMMANDES,NUMEROTELEPHONE);

                     bool test=tr.modifier( FOURNISSEUR_ID,NOMFOURNISSEUR,EMAIL,ADRESSE,CATEGORIESPRODUITSSERVICES,MODALITEPAIEMENT,REPUTATIONFOURNISSEUR,HISTORIQUECOMMANDES,NUMEROTELEPHONE);

                     if(test)

                   {notification.notification_modifierfournisseur();
                         ui->tableView->setModel(tr.afficher());

                   QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),

                                     QObject::tr("invite modifiée.\n"

                                                 "Click ok to exit."), QMessageBox::Ok);


                   }

                     else{
                            notification.notification_failed();
                         QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),

                                     QObject::tr("echec d'ajout !.\n"

                                                 "Click Cancel to exit."), QMessageBox::Cancel);


        }}


void fournisseur::on_suprimer_clicked()
{
    fournisseurs f;
        int FOURNISSEUR_ID = ui->FOURNISSEUR_ID->text().toInt();
        bool test = f.supprimer(FOURNISSEUR_ID);
        if (test) {
            notification.notification_supprimerfournisseur();
            QMessageBox::information(nullptr, QObject::tr("Ok"),
                                     QObject::tr("Suppression effectuée.\n"
                                                 "Click Ok to exit."), QMessageBox::Ok);
        } else {
             notification.notification_failed();
            QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                                  QObject::tr("Échec de la suppression.\n"
                                              "Le fournisseur n'existe pas dans la base de données."),
                                  QMessageBox::Cancel);
        }
        ui->tableView->setModel(f.afficher());

        QSqlQuery qry;
        QDateTime dateTime=QDateTime::currentDateTime();



        qry.prepare("insert into HISTORIQUE (DATEE,ETAT) values (:dateTime,'livree')");
        qry.bindValue(":dateTime",dateTime);

        qry.exec();





}

void fournisseur::on_afficher_clicked()
{
    fournisseurs f;
        ui->tableView->setModel(f.afficher());
}

void fournisseur::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();
       QSqlQuery qry;
       qry.prepare("select * from FOURNISSEUR where FOURNISSEUR_ID='"+val+"'");
       if(qry.exec())
       {
        while(qry.next())
        {ui->FOURNISSEUR_ID->setText(qry.value(0).toString());
         ui->NOMFOURNISSEUR->setText(qry.value(1).toString());
         ui->EMAIL->setText(qry.value(2).toString());
         ui->ADRESSE->setText(qry.value(3).toString());
          ui->CATEGORIESPRODUITSSERVICES->setText(qry.value(4).toString());
         ui->MODALITEPAIEMENT->setText(qry.value(5).toString());
         ui->REPUTATIONFOURNISSEUR->setText(qry.value(6).toString());
          ui->HISTORIQUECOMMANDES->setText(qry.value(7).toString());
           ui->NUMEROTELEPHONE->setText(qry.value(8).toString());
}
       }
       }

void fournisseur::on_tri_clicked()
{
    fournisseurs f;
         ui->tableView->setModel(f.trierNom());
}

void fournisseur::on_pdf_clicked()
{
    fournisseurs f;
       f.pdf();
       QMessageBox::information(nullptr, QObject::tr("Ok"),
                                QObject::tr("telechargement effectuer.\n"
                                            "Click Ok to exit."), QMessageBox::Ok);

}
 void fournisseur::on_stat_clicked()
 {
     statistic = new class Statistic(this);

         statistic->setWindowTitle(" meme team | Statistiques");
         statistic->show();
 }

void fournisseur::on_chercher_textChanged(const QString &arg1)
{
    fournisseurs f;
       int FOURNISSEUR_ID= ui->chercher->text().toInt();
        QString NOMFOURNISSEUR = ui->chercher->text();
       QString CATEGORIESPRODUITSSERVICES = ui->chercher->text();
     f.recherche(ui->tableView,FOURNISSEUR_ID,NOMFOURNISSEUR,CATEGORIESPRODUITSSERVICES);
       if (ui->chercher->text().isEmpty())
       {
           ui->tableView->setModel(f.afficher());
       }
}

void fournisseur::on_triid_clicked()
{
    fournisseurs f;
         ui->tableView->setModel(f.trierid());
}

void fournisseur::on_tricat_clicked()
{
    fournisseurs f;
         ui->tableView->setModel(f.triercat());
}

void fournisseur::on_historique_clicked()
{ fournisseurs p;
    ui->tableViewHistorique->setModel(p.afficherHistorique());
}

void fournisseur::on_tableViewHistorique_activated(const QModelIndex &index)
{
    QString val=ui->tableViewHistorique->model()->data(index).toString();
       QSqlQuery qry;
       qry.prepare("select * from HISTORIQUE where ETAT ='"+val+"'");
       if(qry.exec())
       {
        while(qry.next())
        {
            if(val=="livree")

                QMessageBox::information(nullptr, QObject::tr("Ok"),
                                         QObject::tr("livree.\n"
                                                     "vous avez recu votre commande ."), QMessageBox::Ok);
            else

            QMessageBox::information(nullptr, QObject::tr("Ok"),
                                     QObject::tr("en cours.\n"
                                                 "votre commande arrive apres 24h."), QMessageBox::Ok);





}}}
