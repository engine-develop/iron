TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -D__AVR_ATmega328P__
#QMAKE_CXXFLAGS += -E -C -P

INCLUDEPATH += ../ext/chaos-pp-master
INCLUDEPATH += ../build/iron/include
LIBS += -L../../build/iron/lib -liron

win32 {
    LIBS += -lsetupapi
}

SOURCES += \
    ../tst/iron-cpu-tst/main.cpp

HEADERS += \
    ../tst/iron-cpu-tst/camera.hpp
