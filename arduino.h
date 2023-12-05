/*#ifndef ARDUINO_H
#define ARDUINO_H

//#include <QDeclarativeItem>
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>
#include <QtSerialPort/QSerialPort> //classe rassemblant des fonctions permettant l echange des donness dans une laision serie
#include <QtSerialPort/QSerialPortInfo> //classe fournissant des informations sur les ports disponible

class ArduinoData;

class Arduino
{
    //Q_OBJECT
public:
    Arduino();
    Arduino(const Arduino &);
    Arduino &operator=(const Arduino &);
    ~Arduino();
    int connect_arduino(); //permet de connecter le PC a arduino
    int close_arduino(); //permet de fermer la connection
    int write_to_arduino(QByteArray); //envoyer des donnees vers arduino
    QByteArray read_from_arduino(); //recevoir des donnees de la carte arduino
    QSerialPort* getserial(); //accesseur
    QString getarduino_port_name();
private:
    //QSharedDataPointer<ArduinoData> data;
    QSerialPort * serial; //Cet objet rassemble des informations (vitesse, bits de donnes, etc.)
    //et des fonctions (envoi, lecture de reception,..) sur ce qu'est une voie serie pour aduino
    static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_producy_id=67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data; //contenant les donnes lues a partir d'arduino
};

#endif // ARDUINO_H*/
