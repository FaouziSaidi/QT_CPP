#include <QString>
#include <QMessageBox>
#include<iostream>
#include "employes.h"
#include "gestion_employes.h"
#include "ui_gestion_employes.h"

gestion_employes::gestion_employes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestion_employes)
{
    ui->setupUi(this);
    ui->tableView->setModel(emp.afficher());
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setColumnWidth(7, 100);
    ui->cin_e->setValidator(new QIntValidator(0,99999999,this));
    ui->mail_e_2->setValidator(new QIntValidator(0,99999999,this));
    ui->age->setValidator(new QIntValidator(0,99,this));
}

gestion_employes::~gestion_employes()
{
    delete ui;
}

QString gestion_employes::getSelectedGender()
{
    QButtonGroup genderButtonGroup;
    genderButtonGroup.addButton(ui->homme);
    genderButtonGroup.addButton(ui->femme);

    QAbstractButton* selectedButton = genderButtonGroup.checkedButton();

    if (selectedButton == ui->homme) {
        return "Homme";
    } else if (selectedButton == ui->femme) {
        return "Femme";
    } else {
        return "Non spécifié";
    }
}



void gestion_employes::on_pushButton_clicked()//ajouter
{
    QString nom=ui->nom_e->text();
    QString prenom=ui->prenom->text();
    QString Email=ui->mail_e->text();
    QString genre = getSelectedGender();
    QString mot_de_passe=ui->mot_de_passe_e->text();
    double cin=ui->cin_e->text().toDouble();
    int age=ui->age->text().toInt();
    double num_tel=ui->mail_e_2->text().toDouble();
    int employes_id=ui->employe_id->text().toInt();
    float salaire=ui->salaire->text().toFloat();
    float heures_de_travail=ui->heures_de_travail->text().toFloat();
    QDate date_embauche=ui->dateEdit->date();

    if (nom.isEmpty() || prenom.isEmpty() || Email.isEmpty() || genre.isEmpty() || mot_de_passe.isEmpty()||ui->cin_e->text().isEmpty()||ui->age->text().isEmpty()||ui->mail_e_2->text().isEmpty()||ui->employe_id->text().isEmpty()||ui->salaire->text().isEmpty()||ui->heures_de_travail->text().isEmpty()) {
            QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Tous les champs doivent être remplis."));
            return; // Arrêtez l'exécution si les données sont invalides.
        }

        if (salaire <= 0.0) {
            QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le salaire doit être supérieur à zéro."));
            return;
        }
    QRegExp regex("^[a-zA-Z0-9]+$");  // Mot de passe composé de lettres et de chiffres seulement

    if (!regex.exactMatch(mot_de_passe))
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Mot de passe non valide. Utilisez uniquement des lettres et des chiffres."), QMessageBox::Cancel);
        return;  // Sortez de la fonction si la vérification échoue
    }
    QRegExp emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$");

    if (!emailRegex.exactMatch(Email)) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Adresse email non valide. Utilisez le format abc@abc.abc."), QMessageBox::Cancel);
        return;  // Sortez de la fonction si la vérification échoue
    }
    Employes E(nom,prenom,Email,genre, mot_de_passe,cin,age,num_tel,employes_id,salaire,heures_de_travail,date_embauche);
    bool test=E.ajouter();
    if(test)
    {
        ui->nom_e->setText("");
        ui->prenom->setText("");
        ui->mail_e->setText("");
        ui->mot_de_passe_e->setText("");
        ui->cin_e->setText("");
        ui->age->setText("");
        ui->mail_e_2->setText("");
        ui->employe_id->setText("");
        ui->salaire->setText("");
        ui->heures_de_travail->setText("");
        ui->dateEdit->setDate(QDate::currentDate());
        ui->tableView->setModel(emp.afficher());
        ui->tableView->resizeColumnsToContents();
        QMessageBox::information(nullptr,QObject::tr("ok"),
                QObject::tr("ajout effectué.\n ""click Cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not Ok"),QObject::tr("ajout non effectué.\n""click Cancel to exit."),QMessageBox::Cancel);


}

void gestion_employes::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void gestion_employes::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void gestion_employes::on_pushButton_4_clicked()//supprimer
{
    Employes e;
    int id=ui->supprimer->text().toInt();
    e.setID(id);
    if (e.existe()) {
    bool test = e.supprimer(id);

        if (test) {
            ui->tableView->setModel(emp.afficher());
            ui->tableView->resizeColumnsToContents();
            QMessageBox::information(nullptr, QObject::tr("Ok"), QObject::tr("suppression effectuée. Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("suppression non effectuée. Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("L'employé n'existe pas. suppression non effectuée. Cliquez sur Cancel pour quitter."), QMessageBox::Cancel);
    }
}

void gestion_employes::on_next_page1_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
}

void gestion_employes::on_pred_page2_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
}







void gestion_employes::on_modifier_clicked()
{
    int employes_id = ui->employe_id->text().toInt(); // Get the employee ID to identify the employee to modify

       // Check if the employee ID is valid
       if (employes_id <= 0) {
           QMessageBox::critical(nullptr, QObject::tr("Invalid Input"), QObject::tr("Please enter a valid employee ID."), QMessageBox::Cancel);
           return;
       }

       QString nom = ui->nom_e->text();
       QString prenom = ui->prenom->text();
       QString Email = ui->mail_e->text();
       QString genre = getSelectedGender();
       QString mot_de_passe = ui->mot_de_passe_e->text();
       double cin = ui->cin_e->text().toDouble();
       int age = ui->age->text().toInt();
       double num_tel = ui->mail_e_2->text().toDouble();
       float salaire = ui->salaire->text().toFloat();
       float heures_de_travail = ui->heures_de_travail->text().toFloat();
       QDate date_embauche = ui->dateEdit->date();


       if (nom.isEmpty() || prenom.isEmpty() || Email.isEmpty() || genre.isEmpty() || mot_de_passe.isEmpty()||ui->cin_e->text().isEmpty()||ui->age->text().isEmpty()||ui->mail_e_2->text().isEmpty()||ui->employe_id->text().isEmpty()||ui->salaire->text().isEmpty()||ui->heures_de_travail->text().isEmpty()) {
               QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Tous les champs doivent être remplis."));
               return; // Arrêtez l'exécution si les données sont invalides.
           }

           if (salaire <= 0.0) {
               QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le salaire doit être supérieur à zéro."));
               return;
           }
       QRegExp regex("^[a-zA-Z0-9]+$");  // Mot de passe composé de lettres et de chiffres seulement

       if (!regex.exactMatch(mot_de_passe))
       {
           QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Mot de passe non valide. Utilisez uniquement des lettres et des chiffres."), QMessageBox::Cancel);
           return;  // Sortez de la fonction si la vérification échoue
       }
       QRegExp emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$");

       if (!emailRegex.exactMatch(Email)) {
           QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Adresse email non valide. Utilisez le format abc@abc.abc."), QMessageBox::Cancel);
           return;  // Sortez de la fonction si la vérification échoue
       }



       Employes E(nom, prenom, Email, genre, mot_de_passe, cin, age, num_tel, employes_id, salaire, heures_de_travail, date_embauche);

       if (E.existe()) {

           bool test = E.modifier();
           if (test) {
               ui->nom_e->setText("");
               ui->prenom->setText("");
               ui->mail_e->setText("");
               ui->mot_de_passe_e->setText("");
               ui->cin_e->setText("");
               ui->age->setText("");
               ui->mail_e_2->setText("");
               ui->employe_id->setText("");
               ui->salaire->setText("");
               ui->heures_de_travail->setText("");
               ui->dateEdit->setDate(QDate::currentDate());
               ui->tableView->setModel(emp.afficher());
               ui->tableView->resizeColumnsToContents();
               QMessageBox::information(nullptr, QObject::tr("Ok"), QObject::tr("Modification effectuée. Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
           } else {
               QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Modification non effectuée. Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
           }
       } else {
           QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("L'employé n'existe pas. Modification non effectuée. Cliquez sur Cancel pour quitter."), QMessageBox::Cancel);
       }
}




/*void gestion_employes::on_modifier_clicked()
{
       QString nom = ui->nom_e->text();
       QString prenom = ui->prenom->text();
       QString Email = ui->mail_e->text();
       QString genre = getSelectedGender();
       QString mot_de_passe = ui->mot_de_passe_e->text();
       int cin = ui->cin_e->text().toInt();
       int age = ui->age->text().toInt();
       int num_tel = ui->mail_e_2->text().toInt();
       int employes_id = ui->employe_id->text().toInt();
       float salaire = ui->salaire->text().toFloat();
       float heures_de_travail = ui->heures_de_travail->text().toFloat();
       QDate date_embauche = ui->dateEdit->date();


       Employes E(nom, prenom, Email, genre, mot_de_passe, cin, age, num_tel, employes_id, salaire, heures_de_travail, date_embauche);


       if (E.existe()) {

           bool test = E.modifier();
           if (test) {
               ui->tableView->setModel(emp.afficher());
               QMessageBox::information(nullptr, QObject::tr("Ok"), QObject::tr("Modification effectuée. Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
           } else {
               QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Modification non effectuée. Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
           }
       } else {
           QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("L'employé n'existe pas. Modification non effectuée. Cliquez sur Cancel pour quitter."), QMessageBox::Cancel);
       }
}
*/
/*
void gestion_employes::on_modifier_clicked()
{
    int employes_id = ui->employe_id->text().toInt();
        Employes E;
           E.setID(employes_id);
        // Charger les données actuelles de l'employé depuis la base de données
        if (E.existe()) {
            QString nom = ui->nom_e->text();
            QString prenom = ui->prenom->text();
            QString Email = ui->mail_e->text();
            QString genre = getSelectedGender();
            QString mot_de_passe = ui->mot_de_passe_e->text();
            int cin = ui->cin_e->text().toInt();
            int age = ui->age->text().toInt();
            int num_tel = ui->mail_e_2->text().toInt();
            float salaire = ui->salaire->text().toFloat();
            float heures_de_travail = ui->heures_de_travail->text().toFloat();
            QDate date_embauche = ui->dateEdit->date();

            // Mettre à jour les champs non vides
            if (!nom.isEmpty()) {
                E.setNom(nom);
            }
            if (!prenom.isEmpty()) {
                E.setPrenom(prenom);
            }
            if (!Email.isEmpty()) {
                E.setEmail(Email);
            }

            if (!mot_de_passe.isEmpty()) {
                E.setMotDePasse(mot_de_passe);
            }
            if (cin != 0) {
                E.setCIN(cin);
            }
            if (age != 0) {
                E.setAge(age);
            }
            if (num_tel != 0) {
                E.setNumeroTelephone(num_tel);
            }
            if (salaire != 0.0) {
                E.setSalaire(salaire);
            }
            if (heures_de_travail != 0.0) {
                E.setHeuresDeTravail(heures_de_travail);
            }
            if (!date_embauche.isNull()) {
                E.setDateEmbauche(date_embauche);
            }

            // Effectuer la mise à jour dans la base de données
            if (E.modifier()) {
                ui->tableView->setModel(emp.afficher());
                QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Modification effectuée.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            } else {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("La modification n'a pas pu être effectuée.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            }
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("L'employé n'a pas été trouvé.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        }
}*/
