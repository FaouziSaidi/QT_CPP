#ifndef GESTIONVEHICULESELECTRIQUES_H
#define GESTIONVEHICULESELECTRIQUES_H

#include <QMainWindow>
#include "voitureelectrique.h"

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

private:
    Ui::GestionVehiculesElectriques *ui;

    VoitureElectrique voiture; //Slide 34 from powerpoint, used to be able to call function supprimer.
};
#endif // GESTIONVEHICULESELECTRIQUES_H
