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
         QString HISTORIQUECOMMANDES = ui->HISTORIQUECOMMANDES->text();
         QString NUMEROTELEPHONE = ui->NUMEROTELEPHONE->text();


         fournisseurs tr( FOURNISSEUR_ID,NOMFOURNISSEUR,EMAIL,ADRESSE,CATEGORIESPRODUITSSERVICES,MODALITEPAIEMENT,REPUTATIONFOURNISSEUR,HISTORIQUECOMMANDES,NUMEROTELEPHONE);
         bool test = tr.ajouter();

         QMessageBox msgBox;
         if (test) {
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

         } else {
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

                   {ui->tableView->setModel(tr.afficher());

                   QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),

                                     QObject::tr("invite modifiée.\n"

                                                 "Click ok to exit."), QMessageBox::Ok);


                   }

                     else

                         QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),

                                     QObject::tr("echec d'ajout !.\n"

                                                 "Click Cancel to exit."), QMessageBox::Cancel);


        }


void fournisseur::on_suprimer_clicked()
{
    fournisseurs f;
        int FOURNISSEUR_ID = ui->FOURNISSEUR_ID->text().toInt();
        bool test = f.supprimer(FOURNISSEUR_ID);
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
        ui->tableView->setModel(f.afficher());
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
