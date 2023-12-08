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

            int connectionResult = A.connect_arduino();

            if (connectionResult == 0) {

            } else {
                // Erreur de connexion à l'Arduino
                QMessageBox::critical(this, "Erreur", "Impossible de se connecter à l'Arduino.");
            }
            QObject::connect(A.getserial(), SIGNAL(readyRead()) ,this, SLOT(handleArduinoData()));
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
        return false;
    }
}


void Authentification::handleArduinoData() {

    QByteArray data;
    QString password;

    data = A.read_from_arduino();
    password = QString::fromUtf8(data); // Conversion QByteArray en QString
    qDebug() << "DATA2 : " << data;

    QSqlQuery query;
    query.prepare("SELECT NOM FROM employes WHERE MOT_DE_PASSE = ?");
    query.addBindValue(password); // Conversion QString en QByteArray

    if (query.exec() && query.next()) {
        // Employee exists in the database
        w.show();
        this->hide();
        QMessageBox::information(this, "ok", "Connected successfully.");
        A.close_arduino();

    }
    else if (data=="") {

               // QMessageBox::warning(this, "Erreur", "nothing");

            }
    else {

            QMessageBox::warning(this, "Erreur", "Employe introuvable");

        }


}

