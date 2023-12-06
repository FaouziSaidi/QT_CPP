#include "gestion_recla.h"
#include "ui_gestion_recla.h"
#include "reclamation.h"
#include <vector>
#include <string>
#include <QBuffer>
#include <cstdlib>
#include <ctime>
#include <QSqlError>
#include<QDebug>
#include<QImage>
#include <QPixmap>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include<QTextDocument>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrinterInfo>
#include <QPrintDialog>
#include <QGraphicsView>
#include <QTabWidget>
#include <QMediaPlayer>
#include <QSqlQuery>
#include <QVBoxLayout>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrinterInfo>
#include <QPrintDialog>
#include <QGraphicsView>
#include <QTabWidget>
#include <QBarSet>
#include <QSqlQuery>
#include <QComboBox>
#include <QChart>
#include <QBarCategoryAxis>
#include <QValueAxis>
QT_CHARTS_USE_NAMESPACE

gestion_recla::gestion_recla(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestion_recla)
{
    ui->setupUi(this);
}

gestion_recla::~gestion_recla()
{
    delete ui;
}


void gestion_recla::on_pushButton_8_clicked()
{
    QString ID_RECLAMATION_string = ui->lineEdit->text();
          bool ok;
          int ID_RECLAMATION = ID_RECLAMATION_string.toInt(&ok);
          if (!ok) {

              QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer for ID.");
              return;
          }

          QString DATEE = ui->lineEdit_2->text();

          QString NOM_CLIENT = ui->lineEdit_3->text();

          QRegularExpression Regex1("^[A-Za-z]+$");
                       QRegularExpressionMatch match = Regex1.match(NOM_CLIENT);

                       if (!match.hasMatch()) {
                           QMessageBox::warning(this, "Invalid genre", "Please enter a valid NOM_CLIENT");
                           return;
                       }
          QString DESCRIPTION_REC = ui->lineEdit_4->text();
          QRegularExpression Regex11("^[A-Za-z]+$");
                       QRegularExpressionMatch match1 = Regex11.match(DESCRIPTION_REC);

                       if (!match1.hasMatch()) {
                           QMessageBox::warning(this, "Invalid genre", "Please enter DESCRIPTION_REC");
                           return;
                       }
          QString STATUT = ui->lineEdit_5->text();

          QRegularExpression STATUTRegex("[01]");
                       QRegularExpressionMatch match3 = STATUTRegex.match(STATUT);

                       if (!match3.hasMatch()) {
                           QMessageBox::warning(this, "Invalid genre", "Please enter STATUT 0 or 1");
                           return;
                       }

          reclamation tr(ID_RECLAMATION,DATEE,NOM_CLIENT,DESCRIPTION_REC,STATUT);
          bool test = tr.ajouter();

          QMessageBox msgBox;
          if (test) {
              msgBox.setText("ajout avec succes");
              msgBox.exec();
              ui->lineEdit->clear();
              ui->lineEdit_2->clear();
              ui->lineEdit_3->clear();
              ui->lineEdit_4->clear();
              ui->lineEdit_5->clear();

          } else {
              msgBox.setText("echec");
              msgBox.exec();
          }
          QSqlQuery qry;
          QDateTime dateTime=QDateTime::currentDateTime();

          QString date=dateTime.toString();

          qry.prepare("insert into HISTORIQUE (DATEE,ETATRECLAMATION) values (:dateTime,'reclamation en cours de traitement')");
          qry.bindValue(":dateTime",dateTime);

          qry.exec();

          ui->tableView->setModel(tr.afficher());
    };


void gestion_recla::on_pushButton_5_clicked()
{
    reclamation f;
       ui->tableView->setModel(f.afficher());
}

void gestion_recla::on_pushButton_7_clicked()
{
    int ID_RECLAMATION=ui->lineEdit->text().toInt();
    QString DATEE = ui->lineEdit_2->text();
    QString NOM_CLIENT = ui->lineEdit_3->text();
    QString DESCRIPTION_REC = ui->lineEdit_4->text();
    QString STATUT = ui->lineEdit_5->text();
    reclamation tr(ID_RECLAMATION,DATEE,NOM_CLIENT,DESCRIPTION_REC,STATUT);
                    bool test=tr.modifier(ID_RECLAMATION,DATEE,NOM_CLIENT,DESCRIPTION_REC,STATUT);

                    if(test)

                  {ui->tableView->setModel(tr.afficher());

                  QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),

                                    QObject::tr("invite modifiée.\n"

                                                "Click ok to exit."), QMessageBox::Ok);



                  }

                    else

                        QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),

                                    QObject::tr("echec d'ajout !.\n"

                                                "Click Cancel to exit."), QMessageBox::Cancel);


}

void gestion_recla::on_pushButton_6_clicked()
{
    reclamation f;
       int id_reclamation = ui->lineEdit->text().toInt();
       bool test = f.supprimer(id_reclamation);
       if (test) {
           QMessageBox::information(nullptr, QObject::tr("Ok"),
                                    QObject::tr("Suppression effectuée.\n"
                                                "Click Ok to exit."), QMessageBox::Ok);
       } else {
           QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                                 QObject::tr("Échec de la suppression.\n"
                                             "Le reclamationsseur n'existe pas dans la base de données."),
                                 QMessageBox::Cancel);
       }

       QSqlQuery qry;
       QDateTime dateTime=QDateTime::currentDateTime();

       QString date=dateTime.toString();

       qry.prepare("insert into HISTORIQUE (DATEE,ETATRECLAMATION) values (:dateTime,'reclamation traitee')");
       qry.bindValue(":dateTime",dateTime);

       qry.exec();
       ui->tableView->setModel(f.afficher());
}

void gestion_recla::on_trier_clicked()
{
    reclamation f;
         ui->tableView->setModel(f.trierId_rect());
}

void gestion_recla::on_le_chercher_textChanged(const QString &arg1)
{
    reclamation f;
       int ID_RECLAMATION= ui->le_chercher->text().toInt();
     f.recherche(ui->tableView,ID_RECLAMATION);
       if (ui->le_chercher->text().isEmpty())
       {
           ui->tableView->setModel(f.afficher());
       }
}
void gestion_recla::on_telecharger_clicked()
{
    reclamation f;
    f.telechargerPDF();

             QMessageBox::information(nullptr,QObject::tr("OK"),
                        QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);
}




void gestion_recla::on_statistique_clicked()
{
    QBarSeries *series = new QBarSeries();


        QSqlQuery query;
        query.prepare("SELECT ID_RECLAMATION, STATUT from TABLE1  ");
        if (query.exec()) {
            while (query.next()) {
                QString STATUT = query.value("STATUT").toString();
                int ID_RECLAMATION = query.value("ID_RECLAMATION").toInt();

                QBarSet *ID_RECLAMATIONSet = new QBarSet(STATUT);
                *ID_RECLAMATIONSet << ID_RECLAMATION;

                series->append(ID_RECLAMATIONSet);
            }
        } else {
            qDebug() << "Erreur lors de l'exécution de la requête SQL : " << query.lastError().text();

            return;
        }


        QChart *chart = new QChart();
        chart->addSeries(series);


        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);


        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Nombre des reclamations"
                            "");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);


        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);


        QMainWindow *statsWindow = new QMainWindow();
        statsWindow->setCentralWidget(chartView);

        QPushButton *closeButton = new QPushButton("Fermer", statsWindow);
        QObject::connect(closeButton, &QPushButton::clicked, statsWindow, &QMainWindow::close);


        QVBoxLayout *layout = new QVBoxLayout(statsWindow);
        layout->addWidget(chartView);
        layout->addWidget(closeButton);


        statsWindow->resize(800, 600);

        statsWindow->show();
    }


void gestion_recla::on_historique_clicked()
{
    reclamation p;
    ui->tableViewHistorique->setModel(p.afficherHistorique());
}
