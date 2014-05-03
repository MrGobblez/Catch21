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
    Control/Control.cpp \
    Motion_Tracking/Color_Recognition/Tracking.cpp \
    Serial_Communication/Serial_Communication.cpp \
    File_Handler/File_Handler.cpp \
    GUI/Window_Handler/Window_Handler.cpp \
    Operation_Modes/Low_Repetition/Low_Repetition_Version3/Menu.cpp
    #Menu/Menu.cpp

HEADERS += \
    Camera/OpenCV/Camerainput.h \
    Motion_Tracking/Color_Recognition/Process.h \
    Control/Control.h \
    Motion_Tracking/Color_Recognition/Tracking.h \
    Serial_Communication/Serial_Communication.h \
    File_Handler/File_Handler.h \
    GUI/Window_Handler/Window_Handler.h \
    Operation_Modes/Low_Repetition/Low_Repetition_Version3/Menu.h
    #Menu/Menu.h
