#ifndef GESTION_RECLA_H
#define GESTION_RECLA_H

#include <QMainWindow>
#include <QtDebug>
#include <QtSql>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
QT_BEGIN_NAMESPACE
namespace Ui { class gestion_recla; }
QT_END_NAMESPACE

class gestion_recla : public QMainWindow
{
    Q_OBJECT

public:
    gestion_recla(QWidget *parent = nullptr);
    ~gestion_recla();
    QWidget *mainWidget;
        QWidget *statsWidget;

private slots:
    void on_pushButton_5_clicked();
    void on_le_chercher_textChanged(const QString &arg1);
    void on_trier_clicked();
    void on_telecharger_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_statistique_clicked();

    void on_historique_clicked();

private:
    Ui::gestion_recla *ui;
};
#endif // GESTION_RECLA_H
