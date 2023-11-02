#ifndef fournisseur_H
#define fournisseur_H
#include <QDialog>
#include <QMainWindow>
#include <QDialog>
#include <QFileDialog>


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

private:
    Ui::fournisseur *ui;


};
#endif // MAINWINDOW_H
