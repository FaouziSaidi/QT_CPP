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
#include <QBarSeries>
#include <QBarSet>
#include <QDebug>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QFont>

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

    int num_tel=ui->mail_e_2->text().toInt();
    int employes_id=ui->employe_id->text().toInt();
    float salaire=ui->salaire->text().toFloat();
    float heures_de_travail=ui->heures_de_travail->text().toFloat();
    QDate date_embauche=ui->dateEdit->date();
    QDate date_naissance=ui->dateEdit_2->date();

    if (nom.isEmpty() || prenom.isEmpty() || Email.isEmpty() || genre.isEmpty() || mot_de_passe.isEmpty()||ui->cin_e->text().isEmpty()||ui->mail_e_2->text().isEmpty()||ui->employe_id->text().isEmpty()||ui->salaire->text().isEmpty()||ui->heures_de_travail->text().isEmpty())
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
    Employes E(nom,prenom,Email,genre, mot_de_passe,cin,num_tel,employes_id,salaire,heures_de_travail,date_embauche,date_naissance);
    bool test=E.ajouter();
    if(test)
    {
        ui->nom_e->setText("");
        ui->prenom->setText("");
        ui->mail_e->setText("");
        ui->mot_de_passe_e->setText("");
        ui->cin_e->setText("");
        ui->mail_e_2->setText("");
        ui->employe_id->setText("");
        ui->salaire->setText("");
        ui->heures_de_travail->setText("");
        ui->dateEdit->setDate(QDate::currentDate());
        ui->dateEdit_2->setDate(QDate::currentDate());
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
            ui->supprimer->setText("");
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
       int num_tel = ui->mail_e_2->text().toInt();
       float salaire = ui->salaire->text().toFloat();
       float heures_de_travail = ui->heures_de_travail->text().toFloat();
       QDate date_embauche = ui->dateEdit->date();
       QDate date_naissance=ui->dateEdit_2->date();

       if (nom.isEmpty() || prenom.isEmpty() || Email.isEmpty() || genre.isEmpty() || mot_de_passe.isEmpty()||ui->cin_e->text().isEmpty()||ui->mail_e_2->text().isEmpty()||ui->employe_id->text().isEmpty()||ui->salaire->text().isEmpty()||ui->heures_de_travail->text().isEmpty()) {
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
       Employes E(nom, prenom, Email, genre, mot_de_passe, cin, num_tel, employes_id, salaire, heures_de_travail, date_embauche,date_naissance);

       if (E.existe()) {

           bool test = E.modifier();
           if (test) {
               ui->nom_e->setText("");
               ui->prenom->setText("");
               ui->mail_e->setText("");
               ui->mot_de_passe_e->setText("");
               ui->cin_e->setText("");
               ui->mail_e_2->setText("");
               ui->employe_id->setText("");
               ui->salaire->setText("");
               ui->heures_de_travail->setText("");
               ui->dateEdit->setDate(QDate::currentDate());
               ui->dateEdit_2->setDate(QDate::currentDate());
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
        ui->mail_e_2->setText(QString::number(E.getNumeroTelephone()));
        ui->employe_id->setText(QString::number(employes_id));
        ui->salaire->setText(QString::number(E.getSalaire()));
        ui->heures_de_travail->setText(QString::number(E.getHeuresDeTravail()));
        ui->dateEdit->setDate(E.getDateEmbauche());
        ui->dateEdit_2->setDate(E.getNaissance());

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





void gestion_employes::on_generer_pdf_clicked() {
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


    int y = 30; // Position verticale initiale

    // Ajouter le titre
    QString title = "Liste des Employés";

    QFont titleFont;
    titleFont.setPixelSize(150);
    titleFont.setBold(true); // Rendre le titre en gras
    titleFont.setItalic(true); // Rendre le titre en italique
    titleFont.setUnderline(true); // Souligner le titre

    // Dessiner le titre
    painter.setFont(titleFont);
    QColor customColor (8, 150, 124);
    painter.setPen(customColor);
    painter.drawText(0, y, pdfWriter.width(), 200, Qt::AlignCenter, title);
    y += 350; // Déplacer vers le bas après le titre

    // Réinitialiser la couleur du texte à la valeur par défaut (noir)
    painter.setPen(Qt::black);
    QFont font1;
    font1.setPixelSize(100); // Ajuster la taille de la police
    painter.setFont(font1);

    // Définir les largeurs des colonnes et leurs étiquettes
    const int colWidth = 900;
    const QStringList colLabels = {"ID employes", "Nom", "Prénom", "Email", "genre", "telephone", "CIN", "date d'embauche", "date de naissance","Salaire"};

    // Dessiner la première ligne avec les étiquettes de colonnes
    for (int i = 0; i < colLabels.size(); i++) {
        QFont font1;
        QColor customColor (17, 178, 149);
        painter.setPen(customColor);
        font1.setPixelSize(100); // Ajuster la taille de la police
        painter.setFont(font1);
        painter.drawText(i * colWidth+350, y, colWidth, 100, Qt::AlignLeft, colLabels[i]);
    }
    y += 250; // Déplacement vertical pour les données

    for (Employes &employee : employees) {
        // Dessiner une ligne pour chaque employé
        painter.setPen(Qt::black);
        font1.setPixelSize(100); // Ajuster la taille de la police
        painter.setFont(font1);
        for (int i = 0; i < colLabels.size(); i++) {
            painter.drawText(i * colWidth+350, y, colWidth, 100, Qt::AlignLeft, getEmployeeField(employee, i));
        }
        y += 200; // Déplacement vertical pour la prochaine ligne
    }

    // Ajouter la date en haut à droite
    QFont dateFont;
    dateFont.setPixelSize(90);
    painter.setFont(dateFont);
    painter.setPen(Qt::black); // Définir la couleur de la date en noir
    QString currentDate = QDate::currentDate().toString("dd-MM-yy");
    painter.drawText(pdfWriter.width() - 600, 10, 400, 100, Qt::AlignRight, currentDate);

    // Ajouter le numéro de la page en bas
    int pageNumber = 1; // Vous devrez mettre à jour cela si vous avez plusieurs pages
    QFont pageFont;
    pageFont.setPixelSize(90);
    painter.setFont(pageFont);
    painter.setPen(Qt::black); // Définir la couleur du numéro de page en noir
    painter.drawText(0, pdfWriter.height() - 300, pdfWriter.width(), 100, Qt::AlignRight, QString("Page %1").arg(pageNumber));

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
        case 7: return employee.getDateEmbauche().toString("yyyy-MM-dd");
        case 9: return QString::number(employee.getSalaire());
        case 8: return employee.getNaissance().toString("yyyy-MM-dd");

        default: return QString();
    }
}

void gestion_employes::on_statistique_clicked()
{
    // Appel de la fonction statistiques
      QWidget*  View = emp.statistiquesSalaire();

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
            ui->tableView_2->setModel(emp.afficher_employe_du_mois());
            ui->tableView_2->resizeColumnsToContents();
            QMessageBox::information(this, "Succès", "Données ajoutées avec succès.");
        }


}






QStringList reverseStringList(const QStringList &list) {
    QStringList reversedList = list;
    std::reverse(reversedList.begin(), reversedList.end());
    return reversedList;
}

void gestion_employes::on_rendement_clicked()
{
    QChart *chart = new QChart();
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QBarCategoryAxis *axisY = new QBarCategoryAxis(); // Utilisez QBarCategoryAxis pour l'axe Y
    QChartView *chartView = new QChartView(this);

    QSqlQuery query;
    query.prepare("SELECT EMPLOYES_ID, COUNT(*) AS repetitions FROM GESTION GROUP BY EMPLOYES_ID ORDER BY COUNT(*) DESC");

    if (query.exec()) {
        QBarSeries *series = new QBarSeries();

        int maximumValue = 0; // Initialisez la valeur maximale à zéro

        while (query.next()) {
            int nombreVoitures = query.value("repetitions").toInt();

            // Obtenez le nombre maximum de voitures
            maximumValue = std::max(maximumValue, nombreVoitures);
        }

        // Créez une liste de nombres de 1 au nombre maximal de voitures
        QStringList yAxisCategories;
        for (int i = 1; i <= maximumValue; ++i) {
            yAxisCategories.append(QString::number(i));
        }

        axisY->append(yAxisCategories);

        query.exec(); // Réinitialisez la requête pour récupérer les données
        while (query.next()) {
            int employeId = query.value("EMPLOYES_ID").toInt();
            int nombreVoitures = query.value("repetitions").toInt();

            QSqlQuery employeQuery;
            employeQuery.prepare("SELECT nom FROM employes WHERE EMPLOYES_ID = :employeId");
            employeQuery.bindValue(":employeId", employeId);

            if (employeQuery.exec() && employeQuery.next()) {
                QString nom = employeQuery.value("nom").toString();
                QBarSet *barSet = new QBarSet(QString("%1").arg(nom));
                *barSet << nombreVoitures;

                series->append(barSet);
               // axisX->append(QString("%1").arg(nom));
            }
        }

        chart->addSeries(series);
        chart->setAxisX(axisX, series);
        chart->setAxisY(axisY); // Définir l'axe Y pour afficher le nombre de voitures
        chart->setTitle("Statistiques des voitures gérées par employé");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        chartView->setChart(chart);

        QMainWindow *chartWindow = new QMainWindow(this);
        chartWindow->setCentralWidget(chartView);
        chartWindow->resize(800, 600);
        chartWindow->show();
    } else {
        qDebug() << "Failed to execute query or retrieve data.";
        return;
    }
}






