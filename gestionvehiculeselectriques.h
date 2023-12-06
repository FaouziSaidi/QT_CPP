#ifndef GESTIONVEHICULESELECTRIQUES_H
#define GESTIONVEHICULESELECTRIQUES_H

#include <QMainWindow>
#include "voitureelectrique.h"
#include "gestion_employes.h"

#include <QPushButton>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>


QT_BEGIN_NAMESPACE
namespace Ui { class GestionVehiculesElectriques; }
QT_END_NAMESPACE

class GestionVehiculesElectriques : public QMainWindow
{
    Q_OBJECT

public:
    GestionVehiculesElectriques(QWidget *parent = nullptr);
    ~GestionVehiculesElectriques();

public slots:

    void on_KMeansClusteringButton_clicked();


private slots:
    void on_AjouterVoitureBouton_clicked();

    void on_SupprimerVoitureBouton_clicked();

    void on_ModifierVoitureBouton_clicked();

    void on_TrierParAnneeBouton_clicked();

    void on_TriVINAlphabetiqueBouton_clicked();

    void on_RechercherParMarqueBouton_clicked();

    void exporterEnPDF();

    void on_ShowMakeStatisticsButton_clicked();

    void on_AfficherDisponiblesButton_clicked();




    //Pour afficher la photo de la voiture




    void on_TableVehiculesElectriques_doubleClicked(const QModelIndex &index);

    QString getCarMakeStatistics();



    void on_gestion_employes_2_clicked();



    void on_gestion_client_3_clicked();

private:
    Ui::GestionVehiculesElectriques *ui;

    VoitureElectrique voiture; //Slide 34 from powerpoint, used to be able to call function supprimer.
    QLabel* ImageVoitureLabel;
public:
    //gestion_employes ww;

};
#endif // GESTIONVEHICULESELECTRIQUES_H
