#include "arduino.h"
#include <QDebug>

Arduino::Arduino()
{
data="";
arduino_port_name="";
arduino_is_available=false;
serial=new QSerialPort;
}

QString Arduino:: getarduino_port_name(){
    return arduino_port_name;
}

QSerialPort* Arduino::getserial(){
    return serial;
}

int Arduino::connect_arduino()
{
    //Recherche du port sur lequel la carte arduino identifiee par arduino_uno_vendor_id
    //est connectee
    foreach (const QSerialPortInfo &serial_port_into, QSerialPortInfo::availablePorts())
     {
        if (serial_port_into.hasVendorIdentifier() && serial_port_into.hasProductIdentifier())
        {
            if(serial_port_into.vendorIdentifier()==arduino_uno_vendor_id && serial_port_into.productIdentifier()==arduino_uno_producy_id)
            {
                arduino_is_available=true;
                arduino_port_name=serial_port_into.portName();
            }
        }
    }
    qDebug() << "arduino_port_name is: " << arduino_port_name;
                if (arduino_is_available)
                {
                    //configuration de la communication (debit..)
                    serial->setPortName(arduino_port_name);
                    if(serial->open(QSerialPort::ReadWrite))
                    {
                        serial->setBaudRate(QSerialPort::Baud9600); //debit: 9600 bits/s
                        serial->setDataBits(QSerialPort::Data8); //longuer des donnees: 8 bits
                        serial->setParity(QSerialPort::NoParity); //1 bit de parite optionnel
                        serial->setStopBits(QSerialPort::OneStop); //nombre de bits de stop:1
                        serial->setFlowControl(QSerialPort::NoFlowControl);
                        return 0;
                    }
                 return 1;
                }

                return -1;
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

int Arduino::write_to_arduino(QByteArray d)
{
    if(serial->isWritable()){
         serial->write(d); //envoyer des donnes vers Arduino
    }
    else{
        qDebug()<< "Couldn't write to serial !";
    }
}


QString Arduino::read_from_arduino(){
if (serial->isReadable())
{
    data=serial->readAll(); //recuperer les donnees recues
    return data;
}
}

