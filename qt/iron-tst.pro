ENGINE_PROJ_DIR = D:/data/engine/projects

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += $$ENGINE_PROJ_DIR/build/ext/serial/include
LIBS += -L$$ENGINE_PROJ_DIR/build/ext/serial/lib -lserial

win32 {
    LIBS += -lsetupapi
}

INCLUDEPATH += $$ENGINE_PROJ_DIR/build/iron/include

SOURCES += \
    ../tst/main.cpp
