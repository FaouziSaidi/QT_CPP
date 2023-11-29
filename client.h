#ifndef CLIENT_H
#define CLIENT_H
#include <QDate>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QTableView>
#include<QString>
#include <QPdfWriter>
#include <QPainter>
#include <QPushButton>
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
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>



class Client
{
private:
    int USER_ID,PHONE_NUMBER,AGE;
    QString NOM,PRENOM,RECLAMATION,MAIL;
    QDate DATEE;
    QPixmap IMAGE;

public:
    Client();
    Client (int USER_ID, int PHONE_NUMBER,QString NOM, QString PRENOM,QString RECLAMATION,QString MAIL,QDate DATEE, int AGE, QPixmap IMAGE);


    //METHODS

        bool ajouter_c();
        bool supprimer_c(int USER_ID);
        QSqlQueryModel * afficher_c();
        bool modifier_c(int USER_ID, int PHONE_NUMBER,QString NOM, QString PRENOM,QString RECLAMATION, QString MAIL,QDate DATEE, int AGE, QPixmap IMAGE);
        void rechercher(QTableView * tableView, int);
        int calculateAge (QDate DATEE);
        bool exportToPDF();
        void saveImageToDatabase(int userId, QPixmap image);
        static QMap<QString, int> getClientAges();
         static void updateAgePieChart();
         bool rechercherID(int USER_ID);


    //Getters

       int getUSER_ID();
       int getPHONE_NUMBER();
       QDate getDATE();
       QString getNOM();
       QString getPRENOM();
       QString getMAIL();
       QString getRECLAMATION();
       int getAGE();
       QPixmap getImage();

    //Setters
       void setUSER_ID(int USER_ID);
       void setNUMBER_PHONE(int PHONE_NUMBER);
       void setNOM (QString NOM);
       void setPRENOM (QString PRENOM);
       void setRECLAMATION(QString RECLAMATION );
       void setMAIL (QString MAIL);
       void setDATE (QDate DATEE);
       void setAGE (int AGE);
       void setImage(QPixmap IMAGE);

};

#endif // CLIENT_H
