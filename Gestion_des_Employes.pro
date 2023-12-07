QT       += core gui sql
QT +=charts
QT += printsupport multimedia
QT +=sql
QT += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authentification.cpp \
    connection.cpp \
    employes.cpp \
    gestion_recla.cpp \
    gestion_station.cpp \
    gestionvehiculeselectriques.cpp \
    main.cpp \
    gestion_employes.cpp \
    reclamation.cpp \
    station.cpp \
    voitureelectrique.cpp \
    gestion_client.cpp \
    client.cpp \
    fournisseur.cpp \
    fournisseurs.cpp \
    notifications.cpp \
    qcustomplot.cpp \
    statistic.cpp \
    arduino.cpp

HEADERS += \
    authentification.h \
    connection.h \
    employes.h \
    gestion_employes.h \
    gestion_recla.h \
    gestion_station.h \
    gestionvehiculeselectriques.h \
    reclamation.h \
    station.h \
    voitureelectrique.h \
    gestion_client.h \
    client.h \
    fournisseur.h \
    fournisseurs.h \
    notifications.h \
    qcustomplot.h \
    statistic.h \
    arduino.h

FORMS += \
    authentification.ui \
    gestion_employes.ui \
    gestion_recla.ui \
    gestion_station.ui \
    gestionvehiculeselectriques.ui \
    gestion_client.ui \
    fournisseur.ui \
    statistic.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

SUBDIRS += \
    gestion_recla.pro
