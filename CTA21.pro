#-------------------------------------------------
#
# Project created by QtCreator 2015-06-08T16:07:26
#
#-------------------------------------------------

QT       += core gui webkitwidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CTA21
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    centresecours.cpp \
    engin.cpp \
    intervention.cpp \
    formdepart.cpp

HEADERS  += mainwindow.h \
    centresecours.h \
    engin.h \
    intervention.h \
    formdepart.h

FORMS    += mainwindow.ui \
    formdepart.ui

RESOURCES += \
    ressources.qrc
