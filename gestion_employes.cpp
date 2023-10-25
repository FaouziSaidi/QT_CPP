#include <QString>
#include <QMessageBox>
#include "employes.h"
#include "gestion_employes.h"
#include "ui_gestion_employes.h"

gestion_employes::gestion_employes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestion_employes)
{
    ui->setupUi(this);
    ui->tableView->setModel(emp.afficher());
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



void gestion_employes::on_pushButton_clicked()
{
    QString nom=ui->nom_e->text();
    QString prenom=ui->prenom->text();
    QString Email=ui->mail_e->text();
    QString genre = getSelectedGender();
    QString mot_de_passe=ui->mot_de_passe_e->text();
    int cin=ui->cin_e->text().toInt();
    int age=ui->age->text().toInt();
    int num_tel=ui->mail_e_2->text().toInt();
    int employes_id=ui->employe_id->text().toInt();
    float salaire=ui->salaire->text().toFloat();
    float heures_de_travail=ui->heures_de_travail->text().toFloat();
    QDate date_embauche=ui->dateEdit->date();
    Employes E(nom,prenom,Email,genre, mot_de_passe,cin,age,num_tel,employes_id,salaire,heures_de_travail,date_embauche);
    bool test=E.ajouter();
    if(test)
    {
        ui->tableView->setModel(emp.afficher());
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



