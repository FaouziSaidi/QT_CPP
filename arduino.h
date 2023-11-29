#ifndef ARDUINO_H
#define ARDUINO_H
#include<QtSerialPort/QtSerialPort>
#include<QtSerialPort/QSerialPortInfo>

class Arduino
{
public:

Arduino();

int connect_arduino (); // permet de connecter le PC à Arduino
int close_arduino();
int write_to_arduino( QByteArray ); // envoyer des données vers arduino
 //recevoir des données de la carte Arduino
QSerialPort* getserial (){return serial;};
QString getarduino_port_name ();
QByteArray read_from_arduino(); //recevoir des données de la carte Arduino
private :
QSerialPort *  serial =new QSerialPort(); //Cet objet rassemble des informations (vitesse, bits de données, etc.) //et des fonctions (envoi, lecture de réception,.) sur ce qu'est une voie série pour Arduino.
static const quint16 arduino_uno_vendor_id=9025;
static const quint16 arduino_uno_producy_id=67;
QString arduino_port_name;
bool arduino_is_available;
QByteArray arduino_code,employeeName;


};

#endif // ARDUINO_H
