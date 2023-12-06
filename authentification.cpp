#include <QMessageBox>
#include <QSqlQuery>
#include "authentification.h"
#include "ui_authentification.h"
#include "gestion_employes.h"
#include "employes.h"

Authentification::Authentification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authentification)
{
    ui->setupUi(this);
}

Authentification::~Authentification()
{
    delete ui;
}

void Authentification::on_login_clicked()
{
    QString email = ui->Email->text();
            QString password = ui->mot_de_passe->text();

            if (authenticateEmployee(email, password))
            {

               w.show();
               this->hide();
            } else {

                QMessageBox::critical(this, "Login Error", "Invalid email or password.");
            }
}

bool Authentification::authenticateEmployee(const QString &email, const QString &password)
{
    // Create a SQL query to fetch the employee with the given email and password
    QSqlQuery query;
    query.prepare("SELECT * FROM employes WHERE email = :email AND mot_de_passe = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        // If a row is fetched, the employee exists and credentials are correct
        return true;
    } else {
        // No matching employee found or incorrect credentials
        return false; //MODIFIE PAR SYRINE BECH NOD5LOU YA BRO MATJICH RETURN TRUE ELSE TRUE
    }
}


