ENGINE_PROJ_DIR = D:/data/engine/projects

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -D__AVR_ATmega328P__

INCLUDEPATH += $$ENGINE_PROJ_DIR/build/iron/include
LIBS += -L$$ENGINE_PROJ_DIR/build/iron/lib -liron

win32 {
    LIBS += -lsetupapi
}

SOURCES += \
    ../tst/iron-tst/main.cpp
