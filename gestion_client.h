#ifndef GESTION_CLIENT_H
#define GESTION_CLIENT_H
#include "client.h"
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

QT_BEGIN_NAMESPACE
namespace Ui { class Gestion_client; }
QT_END_NAMESPACE

class Gestion_client : public QMainWindow
{
    Q_OBJECT

public:
    Gestion_client(QWidget *parent = nullptr);
    void verifierBirthday(const QDate& DATEE);
    ~Gestion_client();
private slots :
    void on_pushButton_Ajouter_clicked();
    void on_pushButton_Supprimer_clicked();
    void on_pushButton_Modifier_clicked();
    void on_tableView_activated(const QModelIndex &index);

    void on_lineEdit_ID_textChanged(const QString &arg1);

private:
    Ui::Gestion_client *ui;
    Client Ctmp;
};
#endif // GESTION_CLIENT_H
