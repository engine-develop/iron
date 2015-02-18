ENGINE_PROJ_DIR = D:/data/engine/projects

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$ENGINE_PROJ_DIR/build/ext/serial/include
LIBS += -L$$ENGINE_PROJ_DIR/build/ext/serial/lib -lserial

win32 {
    LIBS += -lsetupapi
}

INCLUDEPATH += $$ENGINE_PROJ_DIR/build/iron/include

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -D__AVR_ATmega328P__

SOURCES += \
    ../tst/iron-tst/main.cpp
