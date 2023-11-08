#include <QString>
#include <QMessageBox>
#include <QApplication>
#include<iostream>
#include <QFileDialog>
#include <QPdfWriter>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QTextTable>
#include <QTextCursor>
#include <QTextTableCell>
#include <QTextFrame>
#include <QTextBlock>
#include <QTextCharFormat>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE
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
      //  int employes_du_mois=emp.employes_du_mois();
        ui->tableView_2->setModel(emp.afficher_employe_du_mois());
        ui->tableView_2->resizeColumnsToContents();
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
    int cin=ui->cin_e->text().toInt();
    int age=ui->age->text().toInt();
    int num_tel=ui->mail_e_2->text().toInt();
    int employes_id=ui->employe_id->text().toInt();
    float salaire=ui->salaire->text().toFloat();
    float heures_de_travail=ui->heures_de_travail->text().toFloat();
    QDate date_embauche=ui->dateEdit->date();

    if (nom.isEmpty() || prenom.isEmpty() || Email.isEmpty() || genre.isEmpty() || mot_de_passe.isEmpty()||ui->cin_e->text().isEmpty()||ui->age->text().isEmpty()||ui->mail_e_2->text().isEmpty()||ui->employe_id->text().isEmpty()||ui->salaire->text().isEmpty()||ui->heures_de_travail->text().isEmpty())
    {
       QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Tous les champs doivent être remplis."));
       return;
    }

    if (salaire <= 0.0)
    {
       QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le salaire doit être supérieur à zéro."));
       return;
    }
    QRegExp regex("^[a-zA-Z0-9]+$");

    if (!regex.exactMatch(mot_de_passe))
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Mot de passe non valide. Utilisez uniquement des lettres et des chiffres."), QMessageBox::Cancel);
        return;
    }
    QRegExp emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$");

    if (!emailRegex.exactMatch(Email)) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Adresse email non valide. Utilisez le format abc@abc.abc."), QMessageBox::Cancel);
        return;
    }

    QRegExp nomPrenomRegex("^[a-zA-Z ]+$");

    if (!nomPrenomRegex.exactMatch(nom) || !nomPrenomRegex.exactMatch(prenom))
    {
      QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le nom et le prénom doivent contenir uniquement des lettres et des espaces."), QMessageBox::Cancel);
      return;
    }
    QDate dateActuelle = QDate::currentDate();
    if (date_embauche > dateActuelle)
    {
      QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("La date d'embauche ne peut pas être ultérieure à la date actuelle."), QMessageBox::Cancel);
      return;
    }
    if (cin <= 10000000)
    {
       QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le CIN est incorrect"), QMessageBox::Cancel);
       return;
    }

    if (num_tel <= 10000000)
    {
       QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le numéro de téléphone est incorrect"), QMessageBox::Cancel);
       return;
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
    int employes_id = ui->employe_id->text().toInt();


       if (employes_id <= 0) {
           QMessageBox::critical(nullptr, QObject::tr("Invalid Input"), QObject::tr("Please enter a valid employee ID."), QMessageBox::Cancel);
           return;
       }

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


       if (nom.isEmpty() || prenom.isEmpty() || Email.isEmpty() || genre.isEmpty() || mot_de_passe.isEmpty()||ui->cin_e->text().isEmpty()||ui->age->text().isEmpty()||ui->mail_e_2->text().isEmpty()||ui->employe_id->text().isEmpty()||ui->salaire->text().isEmpty()||ui->heures_de_travail->text().isEmpty()) {
               QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Tous les champs doivent être remplis."));
               return;
           }

           if (salaire <= 0.0) {
               QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le salaire doit être supérieur à zéro."));
               return;
           }
       QRegExp regex("^[a-zA-Z0-9]+$");

       if (!regex.exactMatch(mot_de_passe))
       {
           QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Mot de passe non valide. Utilisez uniquement des lettres et des chiffres."), QMessageBox::Cancel);
           return;
       }
       QRegExp emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$");

       if (!emailRegex.exactMatch(Email)) {
           QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Adresse email non valide. Utilisez le format abc@abc.abc."), QMessageBox::Cancel);
           return;
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






void gestion_employes::on_tableView_doubleClicked(const QModelIndex &index)
{
    int row = index.row();

    QModelIndex idIndex = ui->tableView->model()->index(row, 0);
    int employes_id = ui->tableView->model()->data(idIndex).toInt();

    Employes E;


    if (E.load(employes_id)) {

        ui->nom_e->setText(E.getNom());
        ui->prenom->setText(E.getPrenom());
        ui->mail_e->setText(E.getEmail());
        if (E.getGenre() == "Homme") {
                    ui->homme->setChecked(true);
                    ui->femme->setChecked(false);
                } else if (E.getGenre() == "Femme") {
                    ui->homme->setChecked(false);
                    ui->femme->setChecked(true);
                }
        ui->mot_de_passe_e->setText(E.getMotDePasse());
        ui->cin_e->setText(QString::number(E.getCIN()));
        ui->age->setText(QString::number(E.getAge()));
        ui->mail_e_2->setText(QString::number(E.getNumeroTelephone()));
        ui->employe_id->setText(QString::number(employes_id));
        ui->salaire->setText(QString::number(E.getSalaire()));
        ui->heures_de_travail->setText(QString::number(E.getHeuresDeTravail()));
        ui->dateEdit->setDate(E.getDateEmbauche());


    } else {

        QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("L'employé n'a pas été trouvé."), QMessageBox::Ok);
    }
}



void gestion_employes::on_recherche_botton_clicked()
{
       QString nomRecherchee = ui->recherche_par_nom->text();

       QSqlQueryModel *results = emp.rechercherParNom(nomRecherchee);

       if (results)
       {
           ui->tableView->setModel(results);
           ui->tableView->resizeColumnsToContents();
       }
       else
       {
           QMessageBox::critical(this, "Erreur", "La recherche a échoué. Veuillez réessayer.");
       }
}


void gestion_employes::on_rafrechir_botton_clicked()
{
    ui->tableView->setModel(emp.afficher());
    ui->tableView->resizeColumnsToContents();
    ui->recherche_par_nom->clear();
}

void gestion_employes::on_pushButton_6_clicked()//tri
{
    QSqlQueryModel *sortedModel=emp.trierParAnneeEmbauche();
    ui->tableView->setModel(sortedModel);
    ui->tableView->resizeColumnsToContents();
}







void gestion_employes::on_generer_pdf_clicked()
{
    Employes e;
    QList<Employes> employees = e.getAllEmployees();
    if (employees.isEmpty()) {
        // Gérer le cas où aucun employé n'est trouvé dans la base de données
        return;
    }

    QFileDialog dialog(this);

    QString filePath = dialog.getSaveFileName(this, "Enregistrer le fichier PDF", "C:/Users/syrin/Desktop/projet/Gestion_des_Employes/employees.pdf", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));

    QPainter painter(&pdfWriter);

    // Définir la mise en page du document PDF et les polices
    QFont font;
    font.setPixelSize(100); // Ajuster la taille de la police
    painter.setFont(font);

    int y = 20; // Position verticale initiale

    // Définir les largeurs des colonnes et leurs étiquettes
    const int colWidth = 900;
    const QStringList colLabels = {"ID employes", "Nom", "Prénom", "Email", "genre", "telephone", "CIN", "age", "mot de passe", "embauche", "Salaire"};

    // Dessiner la première ligne avec les étiquettes de colonnes
    for (int i = 0; i < colLabels.size(); i++) {
        painter.drawText(i * colWidth, y, colWidth, 100, Qt::AlignLeft, colLabels[i]);
    }
    y += 200; // Déplacement vertical pour les données

    for (Employes &employee : employees) {
        // Dessiner une ligne pour chaque employé
        for (int i = 0; i < colLabels.size(); i++) {
            painter.drawText(i * colWidth, y, colWidth, 100, Qt::AlignLeft, getEmployeeField(employee, i));
        }
        y += 200; // Déplacement vertical pour la prochaine ligne
    }

    bool exportSuccess = painter.end();
    if (exportSuccess) {
        QMessageBox::information(this, "Success", "Les informations des employés ont été exportées vers le fichier PDF.");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'exportation des informations des employés vers le fichier PDF.");
    }
}

QString gestion_employes::getEmployeeField(const Employes &employee, int columnIndex)
{
    switch (columnIndex) {
        case 0: return QString::number(employee.getEmployesId());
        case 1: return employee.getNom();
        case 2: return employee.getPrenom();
        case 3: return employee.getEmail();
        case 4: return employee.getGenre();
        case 5: return QString::number(employee.getNumeroTelephone());
        case 6: return QString::number(employee.getCIN());
        case 7: return QString::number(employee.getAge());
        case 8: return employee.getMotDePasse();
        case 9: return employee.getDateEmbauche().toString("yyyy-MM-dd");
        case 10: return QString::number(employee.getSalaire());
        case 11: return employee.getMotDePasse();

        default: return QString();
    }
}

void gestion_employes::on_statistique_clicked()
{
    // Appel de la fonction statistiques
      QWidget*  View = emp.statistiques();

      // Vous pouvez faire d'autres opérations avec le QChartView si nécessaire
      View->resize(800, 600);
      // Exemple de code pour afficher la fenêtre
      View->show();
}

void gestion_employes::on_gerer_clicked()
{
    int id_employe=ui->id_emp_voiture->text().toInt();
    QString vin=ui->vin->text();
    emp.setID(id_employe);
    if (!emp.existe()) {
            QMessageBox::critical(this, "Erreur", "ID de l'employé n'existe pas dans la table employes.");
        }


        if (!emp.vin_existe(vin)) {
            QMessageBox::critical(this, "Erreur", "VIN n'existe pas dans la table voiture.");
        }
        QSqlQuery query;
        query.prepare("INSERT INTO GESTION (EMPLOYES_ID, VIN) VALUES (:id_employe, :vin)");
        query.bindValue(":id_employe", id_employe);
        query.bindValue(":vin", vin);

        bool success = query.exec();

        if (success) {

            QMessageBox::information(this, "Succès", "Données ajoutées avec succès.");
        }


}

/*void gestion_employes::on_repondre_clicked()
{
    Employes e;
    int id_employe=ui->id_emp_reclamation->text().toInt();
    int id_reclamation=ui->reclamation->text().toInt();
    e.setID(id_employe);
    if (!e.existe()) {
            QMessageBox::critical(this, "Erreur", "ID de l'employé n'existe pas dans la table employes.");
        }


        if (!e.id_reclamation_existe(id_reclamation)) {
            QMessageBox::critical(this, "Erreur", "Id_reclamation n'existe pas dans la table reclamation.");
        }
        QSqlQuery query;
        query.prepare("INSERT INTO REPONSE (EMPLOYES_ID, RECLAMATION_ID) VALUES (:id_employe, :id_reclamation)");
        query.bindValue(":id_employe", id_employe);
        query.bindValue(":id_reclamation", id_reclamation);

        bool success = query.exec();

        if (success) {

            QMessageBox::information(this, "Succès", "Données ajoutées avec succès.");
        }

}
*/



















