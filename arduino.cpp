#include <QDebug>
#include <QSqlQuery>
#include "arduino.h"


Arduino::Arduino()
{

}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

int Arduino::connect_arduino() {
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (serial_port_info.description().contains("Arduino")) { // Vérifie la description du port série
            arduino_port_name = serial_port_info.portName(); // Récupère le nom du port
            arduino_is_available = true;
            break; // Arrête la recherche après avoir trouvé le port Arduino
        }
    }

    qDebug() << "Arduino port name:" << arduino_port_name;

    if (arduino_is_available) {

       serial->setPortName(arduino_port_name); // Configure le port série avec le nom trouvé

qDebug() << "ohhhhh" ;
        if (serial->open(QSerialPort::ReadWrite)) { // Ouvre le port série
            serial->setBaudRate(QSerialPort::Baud9600); // Configure le baudrate
            serial->setDataBits(QSerialPort::Data8); // Configure les bits de données
            serial->setParity(QSerialPort::NoParity); // Configure la parité
            serial->setStopBits(QSerialPort::OneStop); // Configure les bits de stop
            serial->setFlowControl(QSerialPort::NoFlowControl); // Configure le contrôle de flux

            return 0; // Connexion réussie
        } else {
            qDebug() << "Error: Failed to open serial port.";
            return 1; // Échec de la connexion
        }
    } else {
        qDebug() << "Error: Arduino not found.";
        return 2; // Arduino non trouvé
    }
}


int Arduino::close_arduino()
{
    if(serial->isOpen())
    {
        serial->close();
        return 0;
    }
    return 1;
}


QByteArray Arduino::read_from_arduino()
{
    QByteArray data;

    if (serial->isOpen() && serial->isReadable())
    {
        QTime timer;
        timer.start();

        while (data.length() < 10 && timer.elapsed() < 3000) {
            if (serial->bytesAvailable() >= 10 - data.length()) {
                data.append(serial->read(10 - data.length()));
            }

            QCoreApplication::processEvents();
        }

        if (data.length() < 10) {
            //qDebug() << "Pas assez de données reçues dans le délai spécifié.";
        }
        else {

                    QString strData = QString::fromUtf8(data);
                    strData = strData.trimmed();
                    data = strData.left(8).toUtf8();
                }
    }
    else {
        qDebug() << "Le port série n'est pas ouvert ou n'est pas lisible.";
    }

    return data;
}

/*
QByteArray Arduino::read_from_arduino()
{
    QByteArray data = "";

    if (serial->isOpen() && serial->isReadable())
    {
        // Attendez que des données soient disponibles ou un certain délai soit écoulé
        QTime timer;
        timer.start();

        while (data.isEmpty() && timer.elapsed() < 3000 && data.length()<8) {  // Attendre jusqu'à 1000 millisecondes (1 seconde)
            if (serial->bytesAvailable() > 0) {
                data = serial->readLine();
                qDebug() << "DATA : " << data;


            }

            QCoreApplication::processEvents();  // Permet de traiter d'autres événements et d'éviter le gel de l'interface graphique
        }

        if (data.isEmpty()) {
            qDebug() << "Pas de données reçues dans le délai spécifié.";
        }
    }
    else {
        qDebug() << "Le port série n'est pas ouvert ou n'est pas lisible.";
    }

    return data;
}
*/

/*
QByteArray Arduino::read_from_arduino()
{
    QByteArray data="";
    if (serial->isOpen() && serial->isReadable())
    {
        while(data=="")
        {
            if (serial->bytesAvailable() > 0) {
                data = serial->readLine();
                qDebug() << "DATA : " << data;
            }
             return data;
        }

    }
qDebug() << "PAS DE DONNES " ;
}

*/


int Arduino::write_to_arduino(QByteArray d)
{
    if (serial->isWritable())
    {
        serial->write(d);
        return 0; // Succès de l'écriture
    }
    else
    {
        qDebug() << "Error: Couldn't write to serial!";
        return 1; // Échec de l'écriture
    }
}


