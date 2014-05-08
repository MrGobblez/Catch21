TEMPLATE = app
CONFIG += console
CONFIG += qt
LIBS += `pkg-config opencv --libs`

SOURCES += main.cpp \
    Image_Converter.cpp

HEADERS += \
    Image_Converter.h

