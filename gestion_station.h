#ifndef GESTION_STATION_H
#define GESTION_STATION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class gestion_station; }
QT_END_NAMESPACE

class gestion_station : public QMainWindow
{
    Q_OBJECT

public:
    gestion_station(QWidget *parent = nullptr);
    ~gestion_station();
private slots:
    void on_ajouter_clicked();
    void on_afficher_clicked();
    void on_supprimer_clicked();
    void on_modifier_clicked();
    void on_affiche_tab_activated(const QModelIndex &index);

    void on_chercher_textChanged(const QString &arg1);
       void on_trier_clicked();
       void on_telechargerPDF_clicked();
       void on_stat_clicked();







private:
    Ui::gestion_station *ui;

};
#endif // GESTION_STATION_H
