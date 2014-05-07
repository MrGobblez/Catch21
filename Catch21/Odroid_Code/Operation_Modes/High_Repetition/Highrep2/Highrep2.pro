TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += `pkg-config opencv --libs`


SOURCES += main.cpp \
    Dynamic_Delay.cpp

HEADERS += \
    Dynamic_Delay.h

