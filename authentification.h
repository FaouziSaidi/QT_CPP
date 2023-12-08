#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

#include <QDialog>
#include "gestion_employes.h"

namespace Ui {
class Authentification;
}

class Authentification : public QDialog
{
    Q_OBJECT

public:
    explicit Authentification(QWidget *parent = nullptr);
    ~Authentification();

private slots:
    void on_login_clicked();

    bool authenticateEmployee(const QString &email, const QString &password);

    void handleArduinoData();
private:
    Ui::Authentification *ui;
    gestion_employes w;
    Arduino A;
};

#endif // AUTHENTIFICATION_H
