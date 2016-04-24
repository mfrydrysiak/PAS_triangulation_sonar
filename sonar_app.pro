#-------------------------------------------------
#
# Project created by QtCreator 2016-03-26T12:54:45
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = sonar_app
TEMPLATE = app


SOURCES +=  src/main.cpp\
            src/mainwindow.cpp \
            src/qcustomplot.cpp \
    src/settingsserialdialog.cpp \
    src/echo.cpp \
    src/sensor.cpp

HEADERS  += src/mainwindow.h \
            src/qcustomplot.h \
    src/settingsserialdialog.h \
    src/echo.h \
    src/sensor.h

FORMS    += mainwindow.ui \
    settingsserialdialog.ui




