#ifndef GESTIONVEHICULESELECTRIQUES_H
#define GESTIONVEHICULESELECTRIQUES_H

#include <QMainWindow>

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

private:
    Ui::GestionVehiculesElectriques *ui;
};
#endif // GESTIONVEHICULESELECTRIQUES_H
