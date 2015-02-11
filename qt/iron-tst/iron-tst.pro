ENGINE_PROJ_DIR = D:/data/engine/projects

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$ENGINE_PROJ_DIR/build/ext/serial/include
LIBS += -L$$ENGINE_PROJ_DIR/build/ext/serial/lib -lserial

LIBS += -lsetupapi

INCLUDEPATH += $$ENGINE_PROJ_DIR/build/iron/include
LIBS += -L$$ENGINE_PROJ_DIR/build/iron/lib -liron

SOURCES += main.cpp
