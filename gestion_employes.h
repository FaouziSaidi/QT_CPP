#ifndef GESTION_EMPLOYES_H
#define GESTION_EMPLOYES_H

#include <QMainWindow>
#include"employes.h"
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

private:
    Ui::gestion_employes *ui;
    Employes emp;

};
#endif // GESTION_EMPLOYES_H
