#ifndef fournisseur_H
#define fournisseur_H
#include <QDialog>
#include <QMainWindow>
#include <QDialog>
#include <QFileDialog>
#include "statistic.h"
#include "notifications.h"
QT_BEGIN_NAMESPACE
namespace Ui { class fournisseur; }
QT_END_NAMESPACE

class fournisseur : public QMainWindow
{
    Q_OBJECT

public:
    fournisseur(QWidget *parent = nullptr);
    ~fournisseur();
private slots:
    void on_ajouter_clicked();
    void on_afficher_clicked();
    void on_modifier_clicked();
    void on_tableView_activated(const QModelIndex &index);
    void on_suprimer_clicked();

    void on_tri_clicked();

    void on_pdf_clicked();

    void on_chercher_textChanged(const QString &arg1);



    void on_triid_clicked();

    void on_tricat_clicked();
void on_stat_clicked();
void on_historique_clicked();

void on_tableViewHistorique_activated(const QModelIndex &index);

private:
    Ui::fournisseur *ui;
 Statistic *statistic;
notification notification;
};
#endif // MAINWINDOW_H
