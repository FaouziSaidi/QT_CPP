#include <QMessageBox>
#include <QApplication>
#include <QSqlError>
#include "client.h"
#include "gestion_client.h"
#include "ui_gestion_client.h"
#include <QPushButton>
#include <qtableview.h>
#include <QTableView>
#include <QRegExpValidator>
#include <QIntValidator>
#include <QPdfWriter>
#include <QPainter>
#include <QPushButton>
#include <QString>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QVariant>
#include <QObject>
#include <Qt>



Gestion_client::Gestion_client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gestion_client)
{
    ui->setupUi(this);
    ui->tableView->setModel(Ctmp.afficher_c());
}

Gestion_client::~Gestion_client()
{
    delete ui;
}



void Gestion_client::on_pushButton_Ajouter_clicked()
{
    int USER_ID=ui->lineEdit_ID->text().toInt();


    QRegExp rxPhone("^[0-9]{8}$");
        QValidator *phoneValidator = new QRegExpValidator(rxPhone, this);

        ui->lineEdit_NUM->setValidator(phoneValidator);
        QString inputPhone = ui->lineEdit_NUM->text();
        int NUMBER_TELEPHONE;
        bool PHONE_TEST = false;

        if (rxPhone.exactMatch(inputPhone)) {
            NUMBER_TELEPHONE = inputPhone.toInt();
            PHONE_TEST = true;
        }



    QRegExp rx("^[a-zA-Z ]+$");
        QValidator *stringValidator = new QRegExpValidator(rx, this);
        ui->lineEdit_NOM->setValidator(stringValidator);
        QString NOM;
        QString inputNom = ui->lineEdit_NOM->text();
        bool NOM_TEST = false;

        if (rx.exactMatch(inputNom))
        {
            NOM = inputNom;
            NOM_TEST=true;
        }

        ui->lineEdit_PRENOM->setValidator(stringValidator);
        QString PRENOM;
        QString inputPrenom = ui->lineEdit_PRENOM->text();
        bool PRENOM_TEST = false;

        if (rx.exactMatch(inputPrenom))
        {
            PRENOM = inputPrenom;
            PRENOM_TEST=true;
        }


    QString MAIL=ui->lineEdit_MAIL->text();
    QString AVIS_APPLICATION= ui->lineEdit_AVIS->text();
    QDate DATEE=ui->dateEdit->date();

    QString Msg;

        if(!NOM_TEST)
            Msg+="Le Nom ne doit contenir que des lettres et des espaces.\n\n";

        if(!PRENOM_TEST)
            Msg+="Le Prénom ne doit contenir que des lettres et des espaces.\n\n";

        if(!PHONE_TEST)
            Msg+="Le numéro de téléphone doit contenir 8 chiffres.";

    if (!NOM_TEST || !PRENOM_TEST || !PHONE_TEST)
    {
    QMessageBox::warning(this,"Saisie Invalide",Msg);

        if(!NOM_TEST)
        ui->lineEdit_NOM->clear();
        if(!PRENOM_TEST)
        ui->lineEdit_PRENOM->clear();
        if(!PHONE_TEST)
        ui->lineEdit_NUM->clear();

    Client c(USER_ID,NUMBER_TELEPHONE,NOM,PRENOM,AVIS_APPLICATION,MAIL,DATEE);
    bool test=c.ajouter_c();
    if(NOM_TEST){
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("VERTIG"),
                              QObject::tr("Client created successfully!\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

          }
              else
                  QMessageBox::critical(nullptr, QObject::tr("PROBLEM"),
                              QObject::tr("Client wasn't created\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ui->lineEdit_ID->clear();
    ui->lineEdit_NOM->clear();
    ui->lineEdit_PRENOM->clear();
    ui->lineEdit_MAIL->clear();
    ui->lineEdit_NUM->clear();
    ui->lineEdit_AVIS->clear();
    ui->dateEdit->clear();
    ui->tableView->setModel(Ctmp.afficher_c());
}
}

void Gestion_client::verifierBirthday(const QDate& DATEE) {
    QDate currentDate = QDate::currentDate();

    if (currentDate.month() == DATEE.month() && currentDate.day() == DATEE.day()) {
        QMessageBox::information(nullptr, "Happy Birthday!", "Wishing you a Happy Birthday with 15% reduction!");
        //QMessageBox::critical(nullptr, QObject::tr("PROBLEM"),
                    //QObject::tr("Client wasn't created\n"
                               // "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

   void Gestion_client::on_pushButton_Supprimer_clicked()
   {
          int USER_ID=ui->lineEdit_ID->text().toInt();
          bool test=Ctmp.supprimer_c(USER_ID);
          if (test)
          {
                    QMessageBox :: information(nullptr,QObject :: tr("OK"),
                                     QObject ::tr("Suppression effectue avec succes\n"
                                                  "click cancel to exit .") , QMessageBox :: Cancel );
          }
          else
              QMessageBox :: critical(nullptr, QObject::tr("not ok;("),
                                      QObject ::tr("suppression non effectue.\n"
                                                   "click cancel to exit."), QMessageBox ::Cancel);
          ui->tableView->setModel(Ctmp.afficher_c());
   }
   void Gestion_client::on_tableView_activated(const QModelIndex &index)
   {
       QString val=ui->tableView->model()->data(index).toString();
       QSqlQuery qry;
       qry.prepare("select * from CLIENT where USER_ID='"+val+"'");
       if(qry.exec())
       {
        while(qry.next())
        {
         ui->lineEdit_ID->setText(qry.value(0).toString());
         ui->lineEdit_NOM->setText(qry.value(1).toString());
         ui->lineEdit_PRENOM->setText(qry.value(2).toString());
         ui->dateEdit->setDate(qry.value(3).toDate());
         ui->lineEdit_NUM->setText(qry.value(4).toString());
         ui->lineEdit_MAIL->setText(qry.value(5).toString());
         ui->lineEdit_AVIS->setText(qry.value(6).toString());
        }
       }
       else
       {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
       }
   }

   void Gestion_client::on_pushButton_Modifier_clicked()
   {
              int USER_ID=ui->lineEdit_ID->text().toInt();
              QString NOM = ui->lineEdit_NOM->text();
              QString PRENOM = ui->lineEdit_PRENOM->text();
              QString MAIL = ui->lineEdit_MAIL->text();
              int NUMBER_TELEPHONE= ui->lineEdit_NUM->text().toInt();
              QString AVIS_APPLICATION= ui->lineEdit_AVIS->text();
              QDate DATEE=ui->dateEdit->date();

                  bool test=Ctmp.modifier_c(USER_ID, NUMBER_TELEPHONE,NOM, PRENOM,AVIS_APPLICATION, MAIL,DATEE);
                if(test)
                  {
                        QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),

                                    QObject::tr("invite modifiée.\n"

                                                "Click ok to exit."), QMessageBox::Ok);

                          ui->lineEdit_ID->clear();
                          ui->lineEdit_NOM->clear();
                          ui->lineEdit_PRENOM->clear();
                          ui->lineEdit_MAIL->clear();
                          ui->lineEdit_NUM->clear();
                          ui->lineEdit_AVIS->clear();
                          ui->dateEdit->clear();
                  }

                else
                    {
                        QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                                    QObject::tr("echec de modifier !\n"

                                                "Click Cancel to exit."), QMessageBox::Cancel);
                    }
                ui->tableView->setModel(Ctmp.afficher_c());
   }




   void Gestion_client::on_lineEdit_ID_textChanged(const QString &arg1)
   {
       int USER_ID = ui->lineEdit_ID->text().toInt();

       if (ui->lineEdit_ID->text().isEmpty())
       {
           ui->tableView->setModel(Ctmp.afficher_c());
       }
       else
       {
           Ctmp.rechercher(ui->tableView, USER_ID);
       }

       ui->lineEdit_NOM->clear();
       ui->lineEdit_PRENOM->clear();
       ui->lineEdit_AVIS->clear();
       ui->lineEdit_MAIL->clear();
       ui->lineEdit_NUM->clear();

       //ui->lineEdit_ID->clear();
   }


