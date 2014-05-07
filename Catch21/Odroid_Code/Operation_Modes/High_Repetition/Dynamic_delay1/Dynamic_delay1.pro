TEMPLATE = app
CONFIG += console
CONFIG -= qt


LIBS += `pkg-config opencv --libs`

SOURCES += main.cpp

