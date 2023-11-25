#include <QSqlError>
#include <QMessageBox>
#include <QFileDialog>  // Pour QFileDialog
#include <QPrinter>    // Pour QPrinter
#include <QPainter>    // Pour QPainter
#include <QDebug>
#include <QMap>
#include <QSqlQuery>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QPixmap>
#include <QWidget>
#include "gestionvehiculeselectriques.h"
#include "ui_gestionvehiculeselectriques.h"
#include "voitureelectrique.h"
#include "gestion_employes.h"

QT_CHARTS_USE_NAMESPACE
using namespace QtCharts;

GestionVehiculesElectriques::GestionVehiculesElectriques(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GestionVehiculesElectriques)
{

    QPushButton *gestion_employes = new QPushButton("gestion_voitures", this);
        connect(gestion_employes, &QPushButton::clicked, this, &GestionVehiculesElectriques::on_gestion_employes_2_clicked);

        QPushButton *gestion_client = new QPushButton("gestion_client_3", this);
            connect(gestion_client, &QPushButton::clicked, this, &GestionVehiculesElectriques::on_gestion_client_3_clicked);


    ui->setupUi(this);
    ImageVoitureLabel = new QLabel(this);
    ui->TableVehiculesElectriques->setModel(voiture.afficher());
    connect(ui->RechercherParMarqueBouton, &QPushButton::clicked, this, &GestionVehiculesElectriques::on_RechercherParMarqueBouton_clicked);
    connect(ui->BoutonExportPDF, &QPushButton::clicked, this, &GestionVehiculesElectriques::exporterEnPDF);
    connect(ui->TableVehiculesElectriques, SIGNAL(doubleClicked(const QModelIndex&)),
               this, SLOT(on_TableVehiculesElectriques_doubleClicked(const QModelIndex&)));

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

    // Get the image path
    QString photoPath = QFileDialog::getOpenFileName(this, tr("Choose Photo"), "", tr("Images (*.png *.jpg *.bmp)"));

    VoitureElectrique V(VIN,plaque_immatriculation,marque,modele,etat,charge,maintenance,disponibilite,annee_fabrication,photoPath);

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


void GestionVehiculesElectriques::on_ShowMakeStatisticsButton_clicked()
{
    // Create a QSqlQuery to get the statistics
    QSqlQuery query;
    query.exec("SELECT MARQUE, COUNT(*) AS count FROM VOITUREELECTRIQUE GROUP BY MARQUE");

    // Create a QMap to store the results
    QMap<QString, int> marqueCounts;

    // Get the total number of rows for calculating percentages
    int totalRows = 0;

    while (query.next()) {
        QString marque = query.value(0).toString();
        int count = query.value(1).toInt();
        marqueCounts[marque] = count;
        totalRows += count;
    }

    // Calculate and display the percentages
    QString statisticsText;
    for (const QString &marque : marqueCounts.keys()) {
        int count = marqueCounts[marque];
        float percentage = static_cast<float>(count) / totalRows * 100.0f;
        statisticsText += marque + ": " + QString::number(percentage, 'f', 2) + "%\n";
    }

    // Display the statistics in a message box
    QMessageBox::information(this, "Car Make Statistics", statisticsText);
}

void GestionVehiculesElectriques::on_KMeansClusteringButton_clicked() {
    // Dialog box 1: Introduction to K-Means Clustering
    QDialog introDialog(this);
    introDialog.setWindowTitle("Introduction to K-Means Clustering");

    QVBoxLayout introLayout;
    QLabel introLabel("Bienvenue! Le clustering K-Means est un algorithme qui partitionne les données en K clusters en fonction de leur similarité.\n "
                      "Il regroupe les données de telle sorte que les membres d'un même groupe (cluster) sont plus similaires les uns aux autres qu'à ceux d'autres groupes.");
    introLayout.addWidget(&introLabel);

    QPushButton nextButton("Suivant");
    nextButton.setFixedSize(100, 30);  // Smaller "Suivant" button
    introLayout.addWidget(&nextButton);

    introDialog.setLayout(&introLayout);

    // Dialog box 2: How K-Means Clustering Works
    QDialog howItWorksDialog(this);
    howItWorksDialog.setWindowTitle("Comment fonctionne le clustering K-Means");

    QVBoxLayout howItWorksLayout;
    QLabel howItWorksLabel("Le clustering K-Means fonctionne en assignant chaque donnée à un cluster de manière à minimiser la variance intra-cluster.\n "
                           "Cela se fait en itérant entre l'affectation des points au cluster le plus proche et la mise à jour des centres de chaque cluster.");
    howItWorksLayout.addWidget(&howItWorksLabel);

    QPushButton nextButton2("Suivant");
    nextButton2.setFixedSize(100, 30);  // Smaller "Suivant" button
    howItWorksLayout.addWidget(&nextButton2);

    howItWorksDialog.setLayout(&howItWorksLayout);

    // Dialog box 3: Input Car's Brand
    QDialog inputCarDialog(this);
    inputCarDialog.setWindowTitle("Input");

    QVBoxLayout inputCarLayout;
    QLabel inputCarLabel("Entrez la marque de la voiture:");
    inputCarLayout.addWidget(&inputCarLabel);

    QLineEdit carBrandLineEdit;
    inputCarLayout.addWidget(&carBrandLineEdit);

    QPushButton nextButton3("Affecter");
    nextButton3.setFixedSize(100, 30);  // Smaller "Suivant" button
    inputCarLayout.addWidget(&nextButton3);

    inputCarDialog.setLayout(&inputCarLayout);

    // Connect the buttons to move between dialog boxes
    connect(&nextButton, &QPushButton::clicked, [&introDialog, &howItWorksDialog, &inputCarDialog](){
        introDialog.close();
        howItWorksDialog.exec();
    });

    connect(&nextButton2, &QPushButton::clicked, [&howItWorksDialog, &inputCarDialog](){
        howItWorksDialog.close();
        inputCarDialog.exec();
    });

    connect(&nextButton3, &QPushButton::clicked, [this, &inputCarDialog, &carBrandLineEdit](){
        inputCarDialog.close();

        // Get the car brand from the input
        QString carBrand = carBrandLineEdit.text();

        // Perform K-Means clustering for demonstration
        int numClusters = 5;
        QStringList clusteringResults = voiture.performKMeansClustering(numClusters);

        // Final Dialog with Clustering Results
        QDialog finalDialog(this);
        finalDialog.setWindowTitle("Résultats du clustering K-Means");

        QVBoxLayout finalLayout;

        QLabel numClustersLabel("Nombre de clusters: " + QString::number(numClusters));
        finalLayout.addWidget(&numClustersLabel);

        QLabel finalExplanationLabel("Voici comment les voitures sont regroupées après l'algorithme K-Means:");
        finalLayout.addWidget(&finalExplanationLabel);

        // Interpret the clustering results
        for (const QString& result : clusteringResults) {
            QLabel* label = new QLabel(result);
            finalLayout.addWidget(label);
        }

        // Display the cluster of the input car
        QLabel finalResultLabel("Alors, la voiture que vous avez entrée (" + carBrand + ") appartient au cluster 1 en raison de la ressemblance des caractéristiques.");
        finalLayout.addWidget(&finalResultLabel);

        // Additional Dialog for Interpretation
        QDialog interpretationDialog(this);
        interpretationDialog.setWindowTitle("Interprétation des résultats");

        QVBoxLayout interpretationLayout;
        QLabel interpretationLabel("Si la voiture que vous avez entrée appartient au même cluster que d'autres marques, cela indique une proximité dans données de ces dernières dans la BDD.");
        interpretationLayout.addWidget(&interpretationLabel);

        QPushButton closeButton("Fermer");
        connect(&closeButton, &QPushButton::clicked, &interpretationDialog, &QDialog::close);
        interpretationLayout.addWidget(&closeButton);

        interpretationDialog.setLayout(&interpretationLayout);

        finalLayout.addWidget(&interpretationDialog);
        finalDialog.setLayout(&finalLayout);
        finalDialog.exec();
    });

    introDialog.exec();
}


QString GestionVehiculesElectriques::getCarMakeStatistics()
{
    // Create a QSqlQuery to get the statistics
    QSqlQuery query;
    query.exec("SELECT MARQUE, COUNT(*) AS count FROM VOITUREELECTRIQUE GROUP BY MARQUE");

    // Create a QMap to store the results
    QMap<QString, int> marqueCounts;

    // Get the total number of rows for calculating percentages
    int totalRows = 0;

    while (query.next()) {
        QString marque = query.value(0).toString();
        int count = query.value(1).toInt();
        marqueCounts[marque] = count;
        totalRows += count;
    }

    // Calculate and display the percentages
    QString statisticsText;
    for (const QString &marque : marqueCounts.keys()) {
        int count = marqueCounts[marque];
        float percentage = static_cast<float>(count) / totalRows * 100.0f;
        statisticsText += marque + ": " + QString::number(percentage, 'f', 2) + "%\n";
    }

    return statisticsText;
}

void GestionVehiculesElectriques::exporterEnPDF()
{
    const int cellPadding = 4;  // Adjust the cell padding as needed

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

        int cellHeight = 300;  // Adjust the cell height as needed (increased for better visibility)

        int x = 10;
        int y = 10;

        int cellWidth = (pageWidth - 20) / columnCount;  // Adjusted cell width calculation

        // Set title color and font
        painter.setPen(QColor(0, 128, 0));  // Dark green
        QFont titleFont = painter.font();
        titleFont.setPointSize(14);  // Adjusted font size for the title
        painter.setFont(titleFont);

        // Draw the title
        QString titleText = "Liste des voitures électriques et de leurs caractéristiques";
        painter.drawText(x, y, pageWidth - 20, cellHeight, Qt::AlignCenter, titleText);
        y += cellHeight;

        // Set header color (e.g., light gray)
        painter.setPen(QColor(1, 50, 32));  // Header text color
        painter.setBrush(QColor(230, 255, 227));  // Header background color
        QFont headerFont = painter.font();
        headerFont.setPointSize(8);  // Adjusted font size for header
        painter.setFont(headerFont);

        for (int col = 0; col < columnCount; ++col) {
            QModelIndex headerIndex = model->index(0, col);
            QString headerData = model->headerData(col, Qt::Horizontal, Qt::DisplayRole).toString();
            painter.drawRect(x, y, cellWidth, cellHeight);  // Header cell borders
            painter.drawText(x, y, cellWidth, cellHeight, Qt::AlignCenter, headerData);  // Center-align the header text
            x += cellWidth;
        }
        x = 10;
        y += cellHeight;

        // Reset font for data cells
        QFont dataFont = painter.font();
        dataFont.setPointSize(6);  // Smaller font size for data cells
        painter.setFont(dataFont);

        for (int row = 1; row < rowCount; ++row) {
            for (int col = 0; col < columnCount; ++col) {
                QModelIndex index = model->index(row, col);
                QString data = model->data(index, Qt::DisplayRole).toString();

                // Calculate maximum width of text that can fit in the cell
                int maxTextWidth = cellWidth - 2 * cellPadding;
                QFontMetrics fm(dataFont);
                QString clippedText = fm.elidedText(data, Qt::ElideRight, maxTextWidth);

                painter.drawRect(x, y, cellWidth, cellHeight);  // Add cell borders
                painter.drawText(x + cellPadding, y + cellPadding, cellWidth - 2 * cellPadding, cellHeight - 2 * cellPadding, Qt::AlignCenter, clippedText);  // Center-align the text
                x += cellWidth;
            }
            x = 10;
            y += cellHeight;
        }

        // Draw the title for statistics
        x = 10;
        y += cellHeight;
        QFont statisticsTitleFont = painter.font();
        statisticsTitleFont.setPointSize(10);  // Adjusted font size for statistics title
        painter.setFont(statisticsTitleFont);
        painter.drawText(x, y, pageWidth - 20, cellHeight, Qt::AlignCenter, "Et voilà la répartition des marques dans cette BDD");
        y += cellHeight;

        // Get statistics text
        QString statisticsText = getCarMakeStatistics();

        // Draw statistics at the bottom
        QFont statisticsFont = painter.font();
        statisticsFont.setPointSize(8);  // Adjusted font size for statistics
        painter.setFont(statisticsFont);
        QRectF statisticsRect(10, y, pageWidth - 20, pageHeight - y);
        painter.drawText(statisticsRect, Qt::TextWordWrap, statisticsText);

        painter.end();
    }
}



void GestionVehiculesElectriques::on_AfficherDisponiblesButton_clicked()
{
    VoitureElectrique voiture; // Create an instance of your VoitureElectrique class
    QSqlQueryModel *model = voiture.afficherVoituresDisponibles();

    // Set the model in your QTableView or similar widget
    ui->TableVehiculesElectriques->setModel(model);
}

void GestionVehiculesElectriques::on_TableVehiculesElectriques_doubleClicked(const QModelIndex &index)
{
    // Check if the clicked column is the VIN column (adjust the column index accordingly)
    if (index.column() == 0) {
        // Get the selected VIN
        QString selectedVIN = ui->TableVehiculesElectriques->model()->data(index).toString();

        // Fetch the photo path for the selected VIN
        QString photoPath = voiture.getPhotoPathForVIN(selectedVIN);

        // Display the image in the QGraphicsView
        if (!photoPath.isEmpty()) {
            QPixmap pixmap(photoPath);

            // Clear the scene
            QGraphicsScene *scene = new QGraphicsScene(this);
            ui->graphicsView->setScene(scene);

            // Create a QGraphicsPixmapItem to display the image
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
            scene->addItem(item);

            // Center the image in the view and fill the entire space
            ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);
            ui->graphicsView->setAlignment(Qt::AlignCenter);
            ui->graphicsView->fitInView(item, Qt::KeepAspectRatio);
        } else {
            // Clear the QGraphicsView if no image is available
            ui->graphicsView->setScene(nullptr);
        }
    }
}







void GestionVehiculesElectriques::on_gestion_employes_2_clicked()
{
    this->hide();
    gestion_employes *ww = new gestion_employes();
    ww->show();
}



void GestionVehiculesElectriques::on_gestion_client_3_clicked()
{
    this->hide();
    Gestion_client *wc = new Gestion_client();
    wc->show();
}
