#include <QMessageBox>
#include <QApplication>
#include <QSqlError>
#include "client.h"
#include "gestion_client.h"
#include "ui_gestion_client.h"
#include <QPushButton>
#include <qtableview.h>
#include <QTableView>
#include <QRegExpValidator>
#include <QIntValidator>
#include <QPdfWriter>
#include <QPainter>
#include <QPushButton>
#include <QString>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QVariant>
#include <QObject>
#include <Qt>
#include <QTextCursor>
#include <QPrinter>
#include <QFileDialog>
#include <QBuffer>
#include <QCoreApplication>
#include <QtDebug>
#include <QPixmap>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QObject>
#include <Qt>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QPalette>
#include <QDebug>

#include <QtCharts>
#include <QChartView>

#include "gestion_employes.h"


Gestion_client::Gestion_client(QWidget *parent): QMainWindow(parent), ui(new Ui::Gestion_client)
{
    ui->setupUi(this);
    ui->tableView->setModel(Ctmp.afficher_c());

    chartView=new QtCharts::QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    createAgePieChart();
}
/*
// Modify this in your gestion_client.cpp file
Gestion_client::Gestion_client(QWidget *parent) : QMainWindow(parent), ui(new Ui::Gestion_client)
{
    ui->setupUi(this);
    ui->tableView->setModel(Ctmp.afficher_c());

    chartView = new QtCharts::QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    createAgePieChart();

    // Connect the signal to the slot
    connect(&Ctmp, &Client::agePieChartUpdated, this, &Gestion_client::updatePieChart);
}*/

/*
void Gestion_client::updatePieChart()
{
    // Recreate the pie chart whenever the signal is emitted
    createAgePieChart();
}*/

Gestion_client::~Gestion_client()
{
    delete ui;

}

void Gestion_client::on_pushButton_Ajouter_clicked()
{

    int USER_ID = ui->lineEdit_ID->text().toInt();

        QPixmap originalImage = ui->image_label->pixmap()->copy();
        QPixmap scaledImage = originalImage.scaled(ui->image_label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

        QRegExp rxPhone("^[0-9]{8}$");
        QValidator *phoneValidator = new QRegExpValidator(rxPhone, this);

        ui->lineEdit_NUM->setValidator(phoneValidator);
        QString inputPhone = ui->lineEdit_NUM->text();
        int PHONE_NUMBER;
        bool PHONE_TEST = false;

        if (rxPhone.exactMatch(inputPhone))
            {
                PHONE_NUMBER = inputPhone.toInt();
                PHONE_TEST = true;
            }


        QRegExp rx("^[a-zA-Z ]+$");
        QValidator *stringValidator = new QRegExpValidator(rx, this);
        ui->lineEdit_NOM->setValidator(stringValidator);
        QString NOM;
        QString inputNom = ui->lineEdit_NOM->text();
        bool NOM_TEST = false;

        if (rx.exactMatch(inputNom))
            {
                NOM = inputNom;
                NOM_TEST=true;
            }

        ui->lineEdit_PRENOM->setValidator(stringValidator);
        QString PRENOM;
        QString inputPrenom = ui->lineEdit_PRENOM->text();
        bool PRENOM_TEST = false;

        if (rx.exactMatch(inputPrenom))
            {
                PRENOM = inputPrenom;
                PRENOM_TEST=true;
            }


        QString MAIL=ui->lineEdit_MAIL->text();
        QString RECLAMATION= ui->lineEdit_AVIS->text();
        QDate DATEE=ui->dateEdit->date();
        int AGE=ui->label_Age->text().toInt();


        QString Msg;

        if(!NOM_TEST)
            Msg+="Le Nom ne doit contenir que des lettres et des espaces.\n\n";

        if(!PRENOM_TEST)
            Msg+="Le Prénom ne doit contenir que des lettres et des espaces.\n\n";

        if(!PHONE_TEST)
            Msg+="Le numéro de téléphone doit contenir 8 chiffres.";

        if (!NOM_TEST || !PRENOM_TEST || !PHONE_TEST) {
                QMessageBox::warning(this, "Saisie Invalide", Msg);

                if (!NOM_TEST)
                    ui->lineEdit_NOM->clear();
                if (!PRENOM_TEST)
                    ui->lineEdit_PRENOM->clear();
                if (!PHONE_TEST)
                    ui->lineEdit_NUM->clear();
                ui->image_label->clear();
            } else {
                Client c(USER_ID, PHONE_NUMBER, NOM, PRENOM, RECLAMATION, MAIL, DATEE, AGE, scaledImage); // Use scaled image
                bool test = c.ajouter_c();

                if (NOM_TEST) {
                    if (test) {
                        QMessageBox::information(nullptr, QObject::tr("VERTIG"),
                            QObject::tr("Client created successfully!\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                    } else {
                        QMessageBox::critical(nullptr, QObject::tr("PROBLEM"),
                            QObject::tr("Client wasn't created\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                    }

                    ui->lineEdit_ID->clear();
                    ui->lineEdit_NOM->clear();
                    ui->lineEdit_PRENOM->clear();
                    ui->lineEdit_MAIL->clear();
                    ui->lineEdit_NUM->clear();
                    ui->lineEdit_AVIS->clear();
                    ui->dateEdit->clear();
                    ui->image_label->clear();
                    ui->tableView->setModel(Ctmp.afficher_c());
                    createAgePieChart();
                }
            }
        }





void Gestion_client::on_pushButton_Modifier_clicked() {
    int USER_ID = ui->lineEdit_ID->text().toInt();

    QRegExp rx("^[a-zA-Z ]+$");
    QValidator *stringValidator = new QRegExpValidator(rx, this);
    ui->lineEdit_NOM->setValidator(stringValidator);
    QString NOM;
    QString inputNom = ui->lineEdit_NOM->text();
    bool NOM_TEST = false;

    if (rx.exactMatch(inputNom)) {
        NOM = inputNom;
        NOM_TEST = true;
    }

    ui->lineEdit_PRENOM->setValidator(stringValidator);
    QString PRENOM;
    QString inputPrenom = ui->lineEdit_PRENOM->text();
    bool PRENOM_TEST = false;

    if (rx.exactMatch(inputPrenom)) {
        PRENOM = inputPrenom;
        PRENOM_TEST = true;
    }

    QString MAIL = ui->lineEdit_MAIL->text();

    QRegExp rxPhone("^[0-9]{8}$");
    QValidator *phoneValidator = new QRegExpValidator(rxPhone, this);

    ui->lineEdit_NUM->setValidator(phoneValidator);
    QString inputPhone = ui->lineEdit_NUM->text();
    int PHONE_NUMBER;
    bool PHONE_TEST = false;

    if (rxPhone.exactMatch(inputPhone)) {
        PHONE_NUMBER = inputPhone.toInt();
        PHONE_TEST = true;
    }

    QString RECLAMATION = ui->lineEdit_AVIS->text();
    QDate DATEE = ui->dateEdit->date();
    int AGE = ui->label_Age->text().toInt();
    QPixmap originalImage = ui->image_label->pixmap()->copy();
    QPixmap scaledImage = originalImage.scaled(ui->image_label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QString Msg;

    if (!NOM_TEST || !PRENOM_TEST || !PHONE_TEST) {
        QMessageBox::warning(this, "Saisie Invalide", Msg);

        if (!NOM_TEST)
            ui->lineEdit_NOM->clear();
        if (!PRENOM_TEST)
            ui->lineEdit_PRENOM->clear();
        if (!PHONE_TEST)
            ui->lineEdit_NUM->clear();
    } else {
        bool test = Ctmp.modifier_c(USER_ID, PHONE_NUMBER, NOM, PRENOM, RECLAMATION, MAIL, DATEE, AGE, scaledImage);

        if (test) {
            QMessageBox::information(nullptr, QObject::tr("Modifier avec succès "),
                QObject::tr("Client modifié.\n"
                            "Click OK to exit."), QMessageBox::Ok);

            ui->lineEdit_ID->clear();
            ui->lineEdit_NOM->clear();
            ui->lineEdit_PRENOM->clear();
            ui->lineEdit_MAIL->clear();
            ui->lineEdit_NUM->clear();
            ui->lineEdit_AVIS->clear();
            ui->dateEdit->clear();
            ui->label_Age->setText("Age");
            ui->image_label->clear();
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Modifier a échoué"),
                QObject::tr("Échec de la modification !\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
        }
        ui->tableView->setModel(Ctmp.afficher_c());
        createAgePieChart();
    }
}

   void Gestion_client::on_pushButton_Supprimer_clicked()
   {
          int USER_ID=ui->lineEdit_ID->text().toInt();
          bool test=Ctmp.supprimer_c(USER_ID);
          if (test)
          {
                    QMessageBox :: information(nullptr,QObject :: tr("OK"),
                                     QObject ::tr("Suppression effectue avec succes\n"
                                                  "click cancel to exit .") , QMessageBox :: Cancel );
          }
          else
              QMessageBox :: critical(nullptr, QObject::tr("not ok;("),
                                      QObject ::tr("suppression non effectue.\n"
                                                   "click cancel to exit."), QMessageBox ::Cancel);
          ui->tableView->setModel(Ctmp.afficher_c());
          createAgePieChart();
   }
   void Gestion_client::on_tableView_activated(const QModelIndex &index) {
       QString val = ui->tableView->model()->data(index).toString();
       QSqlQuery qry;
       qry.prepare("select * from CLIENT where USER_ID='" + val + "'");
       if (qry.exec()) {
           while (qry.next()) {
               ui->lineEdit_ID->setText(qry.value(0).toString());
               ui->lineEdit_NOM->setText(qry.value(1).toString());
               ui->lineEdit_PRENOM->setText(qry.value(2).toString());
               ui->dateEdit->setDate(qry.value(3).toDate());
               ui->lineEdit_NUM->setText(qry.value(4).toString());
               ui->lineEdit_MAIL->setText(qry.value(5).toString());
               ui->lineEdit_AVIS->setText(qry.value(6).toString());
               ui->label_Age->setText(qry.value(7).toString());

               // Retrieve the image data as QByteArray
               QByteArray imageData = qry.value(8).toByteArray();

               // Convert the QByteArray back to QPixmap
               QPixmap image;
               image.loadFromData(imageData);

               // Set the scaled pixmap to the QLabel
               ui->image_label->setPixmap(image.scaled(ui->image_label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
           }
       } else {
           QMessageBox::critical(this, tr("error::"), qry.lastError().text());
       }
   }



   void Gestion_client::on_lineEdit_ID_textChanged(const QString &arg1)
   {
       int USER_ID = ui->lineEdit_ID->text().toInt();

       if (ui->lineEdit_ID->text().isEmpty())
       {
           ui->tableView->setModel(Ctmp.afficher_c());
       }
       else
       {
           Ctmp.rechercher(ui->tableView, USER_ID);
       }

       ui->lineEdit_NOM->clear();
       ui->lineEdit_PRENOM->clear();
       ui->lineEdit_AVIS->clear();
       ui->lineEdit_MAIL->clear();
       ui->lineEdit_NUM->clear();
       ui->image_label->clear();

       //ui->lineEdit_ID->clear();
   }

   void Gestion_client::on_pushButton_Browse_clicked() {
       QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
       if (!fileName.isEmpty()) {
           // Load the image
           QPixmap image(fileName);

           // Display the image in your QLabel
           ui->image_label->setPixmap(image);

           // Set the image in your Client object
           Ctmp.setImage(image);
       }
   }

void Gestion_client::on_dateEdit_userDateChanged(const QDate &date)
{
    ui->label_Age->setNum(Ctmp.calculateAge(date));
}

void Gestion_client::on_pushButton_PDF_clicked()
{
    bool test=Ctmp.exportToPDF();
    if (test) {
        QMessageBox :: information(nullptr,QObject :: tr("OK"),
                         QObject ::tr("PDF exported successfuly!\n"
                                      "click cancel to exit .") , QMessageBox :: Cancel );
            qDebug() << "PDF exported successfully.";
        } else {
        QMessageBox :: critical(nullptr, QObject::tr("not ok;("),
                                QObject ::tr("PDF unable to export.\n"
                                             "click cancel to exit."), QMessageBox ::Cancel);
            qDebug() << "PDF export canceled or failed.";
        }

}

void Gestion_client::createAgePieChart()
{
    // Create a new QChart to display the age demographics
    QChart *chart = new QChart();
    chart->setTitle("Client Age Demographics");

    // Find the QChartView widget with the object name "widget"
    QChartView *chartView = findChild<QChartView*>("widget");

    // Check if the QChartView widget is found
    if (!chartView)
    {
        qDebug() << "ChartView not found!";
        return;
    }

    // Create a new QPieSeries to hold the age demographic data
    QPieSeries *series = new QPieSeries();

    // Get age demographic data from the Client class
    QMap<QString, int> ageData = Client::getClientAges();

    // Iterate through the age ranges and add them to the pie chart
    for (const QString &ageRange : ageData.keys())
    {
        int count = ageData.value(ageRange);

        // Create a QPieSlice for each age range and add it to the series
        QPieSlice *slice = new QPieSlice(ageRange, count);
        series->append(slice);
    }

    // Add the series to the chart
    chart->addSeries(series);

    // Configure the chart legend visibility and alignment
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Set the chart to the QChartView widget and enable antialiasing for smoother rendering
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}


void gestion_employes::on_gestion_voitures2_clicked()
{
    this->hide();
    GestionVehiculesElectriques *ww = new GestionVehiculesElectriques();
    ww->show();
}




