QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShaderThing
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
    shaderthingopenglwidget.cpp

HEADERS  += mainwindow.h \
    shaderthingopenglwidget.h

FORMS    += mainwindow.ui

DISTFILES += \
    README.md
