#-------------------------------------------------
#
# Project created by QtCreator 2016-03-26T12:54:45
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = sonar_app
TEMPLATE = app


SOURCES +=  main.cpp\
            mainwindow.cpp \
            qcustomplot.cpp \
    settingsserialdialog.cpp \
    echo.cpp \
    sensor.cpp

HEADERS  += mainwindow.h \
            qcustomplot.h \
    settingsserialdialog.h \
    echo.h \
    sensor.h

FORMS    += mainwindow.ui \
    settingsserialdialog.ui
