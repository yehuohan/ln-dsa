
#-------------------------------------------------
#
# Project created by Vim 2018-06-11 22:00:05
#
#-------------------------------------------------

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG  += c++11

# debug, release, debug_and_release
CONFIG += debug
CONFIG -= release
CONFIG(debug, debug|release) {
    TARGET      = conv 
    OBJECTS_DIR = debug
} else {
    TARGET      = conv 
    OBJECTS_DIR = release
    DEFINES    += QT_NO_WARNING_OUTPUT \
                QT_NO_DEBUG_OUTPUT
}
DESTDIR = $$OBJECTS_DIR/../
MOC_DIR  = $$OBJECTS_DIR/moc
UI_DIR   = $$OBJECTS_DIR/ui
RCC_DIR  = $$OBJECTS_DIR/rcc

INCLUDEPATH += \
    C:/MyApps/opencv341/build/include/

LIBS        += \
    -L$$"C:/MyApps/opencv341/build/x64/vc14/lib" \
    -lopencv_world341d

unix {
    #LIBS += `pkg-config --libs `
}

#PRECOMPILED_HEADER = pch.h
SOURCES    += \
    convolution.cpp

#HEADERS   += \
