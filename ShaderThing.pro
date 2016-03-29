QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShaderThing
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
    shaderthingopenglwidget.cpp \
    shaderlanguagehighlighter.cpp

HEADERS  += mainwindow.h \
    shaderthingopenglwidget.h \
    shaderlanguagehighlighter.h

FORMS    += mainwindow.ui

DISTFILES += \
    README.md \
    keywords.txt

RESOURCES += \
    shaderthing.qrc
