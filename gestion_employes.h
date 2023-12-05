#ifndef GESTION_EMPLOYES_H
#define GESTION_EMPLOYES_H


#include "gestionvehiculeselectriques.h"
#include "gestion_client.h"
#include "employes.h"
#include "gestion_station.h"
QT_BEGIN_NAMESPACE

namespace Ui { class gestion_employes; }
QT_END_NAMESPACE

class gestion_employes : public QMainWindow
{
    Q_OBJECT

public:
    gestion_employes(QWidget *parent = nullptr);
    QString getSelectedGender();

    ~gestion_employes();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_next_page1_clicked();

    void on_pred_page2_clicked();

    void on_modifier_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_recherche_botton_clicked();

    void on_rafrechir_botton_clicked();

    void on_pushButton_6_clicked();

    void on_generer_pdf_clicked();

    QString getEmployeeField(const Employes &employee, int columnIndex);

    void on_statistique_clicked();

    void on_gerer_clicked();

//    void on_repondre_clicked();



    void on_rendement_clicked();




    void on_gestion_voitures_clicked();

    void on_gestion_client_clicked();


    void on_pushButton_7_clicked();

private:
    Ui::gestion_employes *ui;
    Employes emp;
    gestion_station *gest;

public:
    //GestionVehiculesElectriques gestion_vehicule;

};
#endif // GESTION_EMPLOYES_H
