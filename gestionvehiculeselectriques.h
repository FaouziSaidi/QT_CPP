#ifndef GESTIONVEHICULESELECTRIQUES_H
#define GESTIONVEHICULESELECTRIQUES_H

#include <QMainWindow>
#include "voitureelectrique.h"

class QChartView;
class QBarSet;
class QBarSeries;
class QBarCategoryAxis;
class QValueAxis;
class QChart;

QT_BEGIN_NAMESPACE
namespace Ui { class GestionVehiculesElectriques; }
QT_END_NAMESPACE

class GestionVehiculesElectriques : public QMainWindow
{
    Q_OBJECT

public:
    GestionVehiculesElectriques(QWidget *parent = nullptr);
    ~GestionVehiculesElectriques();

private slots:
    void on_AjouterVoitureBouton_clicked();

    void on_SupprimerVoitureBouton_clicked();

    void on_ModifierVoitureBouton_clicked();

    void on_TrierParAnneeBouton_clicked();

    void on_TriVINAlphabetiqueBouton_clicked();

    void on_RechercherParMarqueBouton_clicked();

    void exporterEnPDF();



private:
    Ui::GestionVehiculesElectriques *ui;

    VoitureElectrique voiture; //Slide 34 from powerpoint, used to be able to call function supprimer.

};
#endif // GESTIONVEHICULESELECTRIQUES_H
