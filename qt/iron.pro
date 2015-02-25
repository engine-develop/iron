#-------------------------------------------------
#
# Project created by QtCreator 2015-02-05T13:32:36
#
#-------------------------------------------------

ARDUINO_DIR     = C:/Program Files (x86)/Arduino
ARDUINO_MCU     = atmega328p
ARDUINO_FCPU    = 16000000
ARDUINO_AVR_DIR = $$ARDUINO_DIR/hardware/tools/avr

QT -= core gui

TARGET = iron
TEMPLATE = lib
CONFIG += staticlib

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += ../ext/chaos-pp-master

INCLUDEPATH += $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino)
INCLUDEPATH += $$quote($$ARDUINO_DIR/hardware/arduino/variants/standard)
INCLUDEPATH += $$quote($$ARDUINO_DIR/libraries)
INCLUDEPATH += $$quote($$ARDUINO_DIR/libraries/Wire)
INCLUDEPATH += $$quote($$ARDUINO_DIR/libraries/Wire/utility)

win32 {
    LIBS += -lsetupapi
}

SOURCES += \
    ../src/port_cpu.cpp \
    ../src/port_cpu_unix.cpp \
    ../src/port_cpu_windows.cpp

HEADERS += \
    ../src/attribute.hpp \
    ../src/bus.hpp \
    ../src/bus.ipp \
    ../src/bus_cpu.hpp \
    ../src/bus_cpu.ipp \
    ../src/bus_mcu.hpp \
    ../src/bus_mcu.ipp \
    ../src/device.hpp \
    ../src/device.ipp \
    ../src/iron.hpp \
    ../src/pins.hpp \
    ../src/pins_atmega328p.hpp \
    ../src/port.hpp \
    ../src/port.ipp \
    ../src/port_cpu.hpp \
    ../src/port_cpu_unix.hpp \
    ../src/port_cpu_windows.hpp \
    ../src/signal.hpp \
    ../src/sync.hpp \
    ../src/sync.ipp \
    ../src/timer.hpp \
    ../src/timer.ipp \
    ../src/types.hpp \
    ../src/typestore.hpp \
    ../src/typestore.ipp \
    ../src/utility.hpp \
    ../src/version.hpp

CONFIG( debug, debug|release ) {
    DEST_DIR = debug
}

CONFIG( release, debug|release ) {
    DEST_DIR = release
}

headers.path = $$PWD/../build/$$TARGET/include
headers.files = $$HEADERS
INSTALLS += headers

libs.path = $$PWD/../build/$$TARGET/lib
libs.files = $${OUT_PWD}/$$DEST_DIR/lib$${TARGET}.a
INSTALLS += libs
