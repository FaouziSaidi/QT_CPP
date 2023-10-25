#include "gestionvehiculeselectriques.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GestionVehiculesElectriques w;
    Connection c; //Instance de la classe Connection

    bool test=c.createconnect();
        if(test)
        {
            w.show();
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("connection successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("connection failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
    return a.exec();
}
