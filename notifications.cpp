#include "notifications.h"
#include "QApplication"
#include <QSystemTrayIcon>
#include<QString>
notification::notification()
{

}
void notification::notification_ajoutfournisseur()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   notifyIcon->setIcon(QIcon(":/new/prefix1/icon_valide.png"));
   notifyIcon->show();
    notifyIcon->showMessage("Gestion des fournisseur ","nouveau fournisseur est ajouté ",QSystemTrayIcon::Information,15000);
    srand (time(NULL));
}

void notification::notification_supprimerfournisseur(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   notifyIcon->setIcon(QIcon(":/new/prefix1/icon_valide.png"));
   notifyIcon->show();
    notifyIcon->showMessage("Gestion des fournisseur","fournisseur est supprimé",QSystemTrayIcon::Information,15000);
srand (time(NULL));
}


void notification::notification_modifierfournisseur(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   notifyIcon->setIcon(QIcon(":/new/prefix1/icon_valide.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des fournisseur ","fournisseur est modifié",QSystemTrayIcon::Information,15000);
srand (time(NULL));
}


void notification::notification_failed(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;


    notifyIcon->show();
    notifyIcon->showMessage("Gestion des fournisseur ","action failed",QSystemTrayIcon::Critical,15000);
srand (time(NULL));
}



















