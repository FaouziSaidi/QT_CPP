#ifndef GESTION_CLIENT_H
#define GESTION_CLIENT_H
#include "client.h"
#include "arduino.h"
#include <QMainWindow>
#include <QPushButton>
#include <QPdfWriter>
#include <QPainter>
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
#include <QPixmap>
#include <QSqlQuery>
#include <QBuffer>


#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QObject>
#include <Qt>

#include <QPalette>
#include <QDebug>

#include <QtCharts>
#include <QChartView>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class Gestion_client; }
QT_END_NAMESPACE

class Gestion_client : public QMainWindow
{
    Q_OBJECT

public:
    Gestion_client(QWidget *parent = nullptr);
    ~Gestion_client();
private slots :
    void on_pushButton_Ajouter_clicked();
    void on_pushButton_Supprimer_clicked();
    void on_pushButton_Modifier_clicked();
    void on_tableView_activated(const QModelIndex &index);
    void on_lineEdit_ID_textChanged(const QString &arg1);
    void on_dateEdit_userDateChanged(const QDate &date);
    void on_pushButton_Browse_clicked();
    void on_pushButton_PDF_clicked();


    void on_gestion_voitures2_clicked();

    void on_gestion_employee2_clicked();

private:
    Ui::Gestion_client *ui;
    Client Ctmp;
    QChartView *chartView;
    QByteArray data;
    //Arduino A;

    void createAgePieChart();
};
#endif // GESTION_CLIENT_H
