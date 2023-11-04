#include "gestionvehiculeselectriques.h"
#include "ui_gestionvehiculeselectriques.h"
#include "voitureelectrique.h"

#include <QMessageBox>
#include <QFileDialog>  // Pour QFileDialog
#include <QPrinter>    // Pour QPrinter
#include <QPainter>    // Pour QPainter
#include <QDebug>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>


GestionVehiculesElectriques::GestionVehiculesElectriques(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GestionVehiculesElectriques)
{
    ui->setupUi(this);

    ui->TableVehiculesElectriques->setModel(voiture.afficher());
    connect(ui->RechercherParMarqueBouton, &QPushButton::clicked, this, &GestionVehiculesElectriques::on_RechercherParMarqueBouton_clicked);
    connect(ui->BoutonExportPDF, &QPushButton::clicked, this, &GestionVehiculesElectriques::exporterEnPDF);




}

GestionVehiculesElectriques::~GestionVehiculesElectriques()
{
    delete ui;
}


void GestionVehiculesElectriques::on_AjouterVoitureBouton_clicked()
{
    //To get the data from the all the fiels on the left of the addbutton
    QString VIN=ui->lineEdit->text();
    QString plaque_immatriculation=ui->lineEdit_2->text();
    QString marque=ui->lineEdit_3->text();
    QString modele=ui->lineEdit_4->text();

    QString etat=ui->lineEdit_6->text();
    QString charge=ui->lineEdit_7->text();
    QString maintenance=ui->lineEdit_8->text();
    QString disponibilite=ui->lineEdit_9->text();
    int annee_fabrication=ui->lineEdit_5->text().toInt();

    VoitureElectrique V(VIN,plaque_immatriculation,marque,modele,etat,charge,maintenance,disponibilite,annee_fabrication);

    bool test=V.ajouter();

    if(test)
    {
        //Refresh for the sake of the affichage function
        ui->TableVehiculesElectriques->setModel(voiture.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectue\n"
                                             "Click Cancel to exit"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK bro"),
                              QObject::tr("Ajout non effectue.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);



}



void GestionVehiculesElectriques::on_SupprimerVoitureBouton_clicked()
{
    QString VIN = ui->lineEdit->text();
    bool test=voiture.supprimer(VIN);

    if(test)
    {
        //Refresh for the sake of the affichage function
        ui->TableVehiculesElectriques->setModel(voiture.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuee\n"
                                             "Click Cancel to exit"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK bro"),
                              QObject::tr("Suppression non effectuee.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}



void GestionVehiculesElectriques::on_ModifierVoitureBouton_clicked()
{
        // To get the data for modification
        QString VIN = ui->lineEdit->text();
        QString newPlaqueImmatriculation = ui->lineEdit_2->text();
        QString newMarque = ui->lineEdit_3->text();
        QString newModele = ui->lineEdit_4->text();
        QString newEtat = ui->lineEdit_6->text();
        QString newCharge = ui->lineEdit_7->text();
        QString newMaintenance = ui->lineEdit_8->text();
        QString newDisponibilite = ui->lineEdit_9->text();
        int newAnneeFabrication = ui->lineEdit_5->text().toInt();

        bool test = voiture.modifier(VIN, newPlaqueImmatriculation, newMarque, newModele, newEtat, newCharge, newMaintenance, newDisponibilite, newAnneeFabrication);

        if (test)
        {
            // Refresh for the sake of the affichage function
            ui->TableVehiculesElectriques->setModel(voiture.afficher());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Modification effectuee\n"
                            "Click Cancel to exit"), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK bro"),
                QObject::tr("Modification non effectuee.\n"
                "Click Cancel to exit."), QMessageBox::Cancel);
}

void GestionVehiculesElectriques::on_TrierParAnneeBouton_clicked()
{
    // Utilisez la fonction de tri que vous avez définie dans VoitureElectrique
    QSqlQueryModel *sortedModel = voiture.trierParAnnee();

    // Rafraîchissez la vue pour afficher les données triées
    ui->TableVehiculesElectriques->setModel(sortedModel);
}

void GestionVehiculesElectriques::on_TriVINAlphabetiqueBouton_clicked()
{
    // Utilisez la fonction trierParVIN de votre objet voiture
    QSqlQueryModel* sortedModel = voiture.trierParVIN();

    // Assurez-vous que la vue de la table est mise à jour avec le modèle trié
    ui->TableVehiculesElectriques->setModel(sortedModel);

    // Rafraîchir l'affichage
    ui->TableVehiculesElectriques->show();
}

// Dans gestionvehiculeselectriques.cpp
void GestionVehiculesElectriques::on_RechercherParMarqueBouton_clicked()
{
    QString marqueRecherchee = ui->lineEditRechercheMarque->text();

    QSqlQueryModel *results = voiture.rechercherParMarque(marqueRecherchee);

    if (results)
    {
        ui->TableVehiculesElectriques->setModel(results);
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "La recherche a échoué. Veuillez réessayer.");
    }
}

void GestionVehiculesElectriques::exporterEnPDF()
{
    QString nomFichierPDF = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");
    if (!nomFichierPDF.isEmpty()) {
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(nomFichierPDF);

        QAbstractItemModel *model = ui->TableVehiculesElectriques->model();
        QPainter painter(&printer);

        int rowCount = model->rowCount();
        int columnCount = model->columnCount();

        int pageWidth = printer.pageRect().width();
        int pageHeight = printer.pageRect().height();

        int cellWidth = pageWidth / columnCount;  // Divide the page width by the number of columns
        int cellHeight = 500;  // Adjust the cell height as needed (increased for better visibility)

        QFont font = painter.font();
        font.setPointSize(6);  // Make the font size smaller for VIN column
        painter.setFont(font);

        int x = 10;
        int y = 10;

        // Set header color (e.g., light gray)
        painter.setPen(QColor(1, 50, 32));  // Header text color
        painter.setBrush(QColor(230, 255, 227));  // Header background color
        for (int col = 0; col < columnCount; ++col) {
            QModelIndex headerIndex = model->index(0, col);
            QString headerData = model->headerData(col, Qt::Horizontal, Qt::DisplayRole).toString();
            painter.drawRect(x, y, cellWidth, cellHeight);  // Header cell borders
            painter.drawText(x, y, cellWidth, cellHeight, Qt::AlignCenter, headerData);  // Center-align the header text
            x += cellWidth;
        }
        x = 10;
        y += cellHeight;

        // Reset color to black for data cells
        painter.setPen(QColor(0, 0, 0));  // Data text color

        for (int row = 1; row < rowCount; ++row) {
            for (int col = 0; col < columnCount; ++col) {
                QModelIndex index = model->index(row, col);
                QString data = model->data(index, Qt::DisplayRole).toString();
                painter.drawRect(x, y, cellWidth, cellHeight);  // Add cell borders
                painter.drawText(x, y, cellWidth, cellHeight, Qt::AlignCenter, data);  // Center-align the text
                x += cellWidth;
            }
            x = 10;
            y += cellHeight;
        }

        painter.end();
    }
}

