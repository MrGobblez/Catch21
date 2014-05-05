TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

SOURCES += main.cpp \
    Camera/OpenCV/Camerainput.cpp \
    Motion_Tracking/Color_Recognition/Process.cpp \
    Thread_Controll/Controll.cpp \
    Motion_Tracking/Color_Recognition/Tracking.cpp \
    Serial_Communication/Serial_Communication.cpp

HEADERS += \
    Camera/OpenCV/Camerainput.h \
    Motion_Tracking/Color_Recognition/Process.h \
    Thread_Controll/Controll.h \
    Motion_Tracking/Color_Recognition/Tracking.h \
    Serial_Communication/Serial_Communication.h

