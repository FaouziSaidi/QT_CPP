#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QCoreApplication>

#include <QSystemTrayIcon>
#include<QString>
class notification
{
public:
    notification();
    void notification_ajoutfournisseur();

    void notification_supprimerfournisseur();

    void notification_modifierfournisseur();

void notification_failed();


};



#endif // NOTIFICATION_H
