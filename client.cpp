#include <QCoreApplication>
#include "client.h"
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlError>
#include <string>
#include <QPdfWriter>
#include <QPainter>
#include <QPushButton>
#include <QString>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QVariant>
#include <QObject>
#include <QTextDocument>
#include <QTextCursor>
#include <QPrinter>
#include <QFileDialog>
#include <Qt>
#include <QPixmap>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

// Constructor for the Client class
Client::Client()
{

}

// Parameterized constructor for the Client class
Client::Client(int USER_ID, int PHONE_NUMBER, QString NOM, QString PRENOM, QString RECLAMATION, QString MAIL, QDate DATEE, int AGE, QPixmap IMAGE)
{
    // Initializing member variables with provided values
    this->USER_ID = USER_ID;
    this->PHONE_NUMBER = PHONE_NUMBER;
    this->NOM = NOM;
    this->PRENOM = PRENOM;
    this->RECLAMATION = RECLAMATION;
    this->MAIL = MAIL;
    this->DATEE = DATEE;
    this->AGE = AGE;
    this->IMAGE = IMAGE;
}


bool Client::rechercherID(int USER_ID)
{
    QSqlQuery *query=new QSqlQuery;
    query->prepare("SELECT 1 FROM CLIENT WHERE USER_ID = :USER_ID");
    query->bindValue(":USER_ID",USER_ID);

    if (query->exec() && query->next())
    {
            // The ID exists in the database
            return true;
        } else {
            // The ID does not exist in the database
            return false;
        }
}
// Method to remove a client from the database based on USER_ID
bool Client::supprimer_c(int USER_ID)
{
    QSqlQuery query;
    query.prepare("Delete from Client where USER_ID= :USER_ID");
    query.bindValue(":USER_ID", USER_ID);
    return query.exec();
}

// Method to calculate age based on the provided birthdate (DATEE)
int Client::calculateAge(QDate DATEE)
{
    AGE = DATEE.daysTo(QDate::currentDate()) / 365; // Approximate age in years
    return AGE;
}

// Method to add a client to the database
bool Client::ajouter_c()
{
    QSqlQuery query;

    // Convert USER_ID to string for binding
    QString res = QString::number(USER_ID);

    // Convert the QPixmap to a QByteArray for storing in the database
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    IMAGE.save(&buffer, "PNG"); // You can adjust the format as needed
    buffer.close();

    // Prepare and bind values for the SQL query
    query.prepare("insert into Client (USER_ID,NOM,PRENOM,DATEE,PHONE_NUMBER,MAIL,RECLAMATION,AGE,IMAGE) values(:USER_ID,:NOM,:PRENOM,:DATEE,:PHONE_NUMBER,:MAIL,:RECLAMATION,:AGE,:IMAGE)");
    query.bindValue(":USER_ID", res);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":DATEE", DATEE);
    query.bindValue(":PHONE_NUMBER", PHONE_NUMBER);
    query.bindValue(":MAIL", MAIL);
    query.bindValue(":RECLAMATION", RECLAMATION);
    query.bindValue(":AGE", AGE);
    query.bindValue(":IMAGE", byteArray);

    // Execute the query and return the result
    return query.exec();
}

// Method to export client data to a PDF file
bool Client::exportToPDF()
{
    // Assuming you have already connected to your database
    QSqlQuery query("SELECT * FROM Client");

    // Create a QTextDocument to hold the data
    QTextDocument document;
    QTextCursor cursor(&document);

    // Iterate over the results and append them to the QTextDocument as a table
    // Append the table header row
    cursor.insertHtml("<table style='border-collapse: collapse; width: 100%; border: 1px solid #ddd;'>"
                      "<tr>"
                      "<th style='border: 1px solid #ddd; padding: 8px; text-align: left;'>User ID</th>"
                      "<th style='border: 1px solid #ddd; padding: 8px; text-align: left;'>Nom</th>"
                      "<th style='border: 1px solid #ddd; padding: 8px; text-align: left;'>Prenom</th>"
                      "<th style='border: 1px solid #ddd; padding: 8px; text-align: left;'>Date</th>"
                      "<th style='border: 1px solid #ddd; padding: 8px; text-align: left;'>Phone Number</th>"
                      "<th style='border: 1px solid #ddd; padding: 8px; text-align: left;'>Mail</th>"
                      "<th style='border: 1px solid #ddd; padding: 8px; text-align: left;'>Reclamation</th>"
                      "<th style='border: 1px solid #ddd; padding: 8px; text-align: left;'>Age</th>"
                      "</tr>");

    // Iterate over the results and append them to the QTextDocument as a styled table
    while (query.next()) {
        QString user_id = query.value("USER_ID").toString();
        QString nom = query.value("NOM").toString();
        QString prenom = query.value("PRENOM").toString();
        QString datee = query.value("DATEE").toString();
        QString phone_number = query.value("PHONE_NUMBER").toString();
        QString mail = query.value("MAIL").toString();
        QString reclamation = query.value("RECLAMATION").toString();
        QString age = query.value("AGE").toString();

        // Append data to the QTextDocument as a table with black borders and dynamically adjusting column widths
        cursor.insertHtml("<tr>"
                          "<td style='border: 1px solid black; padding: 8px; text-align: left; width: auto;'>" + user_id + "</td>"
                          "<td style='border: 1px solid black; padding: 8px; text-align: left; width: auto;'>" + nom + "</td>"
                          "<td style='border: 1px solid black; padding: 8px; text-align: left; width: auto;'>" + prenom + "</td>"
                          "<td style='border: 1px solid black; padding: 8px; text-align: left; width: auto;'>" + datee + "</td>"
                          "<td style='border: 1px solid black; padding: 8px; text-align: left; width: auto;'>" + phone_number + "</td>"
                          "<td style='border: 1px solid black; padding: 8px; text-align: left; width: auto;'>" + mail + "</td>"
                          "<td style='border: 1px solid black; padding: 8px; text-align: left; width: auto;'>" + reclamation + "</td>"
                          "<td style='border: 1px solid black; padding: 8px; text-align: left; width: auto;'>" + age + "</td>"
                          "</tr>");
    }

    // Close the table tag
    cursor.insertHtml("</table><br>");

    // Get the file path for saving the PDF
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Save PDF", "", "PDF Files (*.pdf)");

    // If a file path is provided, create a QPrinter and print the QTextDocument to the PDF file
    if (!filePath.isEmpty()) {
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filePath);
        document.print(&printer);
        return true;
    }

    // Return false if no file path is provided
    return false;
}

// Method to retrieve client data for display in a QTableView
QSqlQueryModel *Client::afficher_c()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    // Fetch data from the Client table and order by NOM
    model->setQuery("select * from Client ORDER BY NOM");

    // Set header data for the QTableView
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("USER_ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TELEPHONE_NUMBER"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("RECLAMATION"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("IMAGE"));

    // Return the model containing client data
    return model;
}

// Method to modify client data in the database based on USER_ID
bool Client::modifier_c(int USER_ID, int PHONE_NUMBER, QString NOM, QString PRENOM, QString RECLAMATION, QString MAIL, QDate DATEE, int AGE, QPixmap IMAGE)
{
    QSqlQuery query;

    // Prepare the SQL query to update client data
    query.prepare("UPDATE CLIENT SET USER_ID=:USER_ID, NOM=:NOM, PRENOM=:PRENOM,  DATEE=:DATEE, PHONE_NUMBER=:PHONE_NUMBER, MAIL=:MAIL, RECLAMATION=:RECLAMATION, AGE=:AGE, IMAGE=:IMAGE WHERE USER_ID=:USER_ID");

    // Bind values for the SQL query
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":USER_ID", USER_ID);
    query.bindValue(":MAIL", MAIL);
    query.bindValue(":PHONE_NUMBER", PHONE_NUMBER);
    query.bindValue(":RECLAMATION", RECLAMATION);
    query.bindValue(":DATEE", DATEE);
    query.bindValue(":AGE", AGE);

    // Convert the QPixmap to QByteArray for storage in the database
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    IMAGE.save(&buffer, "PNG"); // You can adjust the format as needed
    query.bindValue(":IMAGE", byteArray);

    // Execute the query and return the result
    return query.exec();
}

// Method to search for a client by USER_ID and display in a QTableView
void Client::rechercher(QTableView *tableView, int USER_ID)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString USER_ID_string = QString::number(USER_ID);
    QSqlQuery *query = new QSqlQuery;

    // Prepare and execute the query to search for a client by USER_ID
    query->prepare("select * from CLIENT where USER_ID like '%" + USER_ID_string + "%' ;");
    query->exec();
    model->setQuery(*query);

    // Set the model for the QTableView and display
    tableView->setModel(model);
    tableView->show();
}

// Method to retrieve and categorize client ages for charting
QMap<QString, int> Client::getClientAges()
{
    QMap<QString, int> ageData;

    // Modify this query based on your actual database structure
    QSqlQuery query("SELECT AGE FROM CLIENT");

    while (query.next()) {
        int age = query.value("AGE").toInt();

        // Categorize age into ranges
        QString ageRange;
        if (age >= 18 && age <= 25) {
            ageRange = "18-25";
        } else if (age >= 26 && age <= 35) {
            ageRange = "26-35";
        } else if (age >= 36 && age <= 60) {
            ageRange = "36-60";
        } else {
            ageRange = "60+";
        }

        // Increment count for the age range
        ageData[ageRange]++;
    }

    // Return the categorized age data
    return ageData;
}

// Getter methods to retrieve member variables
int Client::getUSER_ID() { return USER_ID; }
int Client::getPHONE_NUMBER() { return PHONE_NUMBER; }
QDate Client::getDATE() { return DATEE; }
QString Client::getNOM() { return NOM; }
QString Client::getPRENOM() { return PRENOM; }
QString Client::getMAIL() { return MAIL; }
QString Client::getRECLAMATION() { return RECLAMATION; }
int Client::getAGE() { return AGE; }
QPixmap Client::getImage() { return IMAGE; }

// Setter methods to set member variables
void Client::setUSER_ID(int USER_ID) {
    this->USER_ID = USER_ID;
}
void Client::setNUMBER_PHONE(int PHONE_NUMBER) {
    this->PHONE_NUMBER = PHONE_NUMBER;
}
void Client::setNOM(QString NOM) {
    this->NOM = NOM;
}
void Client::setPRENOM(QString PRENOM) {
    this->PRENOM = PRENOM;
}
void Client::setRECLAMATION(QString RECLAMATION) {
    this->RECLAMATION = RECLAMATION;
}

void Client::setMAIL(QString MAIL) {
    this->MAIL = MAIL;
}
void Client::setDATE(QDate DATEE) {
    this->DATEE = DATEE;
}
void Client::setAGE(int AGE) {
    this->AGE = AGE;
}
void Client::setImage(QPixmap IMAGE) {
    this->IMAGE = IMAGE;
}






