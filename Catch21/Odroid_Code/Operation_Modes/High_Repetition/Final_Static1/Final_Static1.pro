TEMPLATE = app
CONFIG += console
CONFIG -= qt
LIBS += `pkg-config opencv --libs`


SOURCES += main.cpp \
    Stream_Delay.cpp

HEADERS += \
    Stream_Delay.h

