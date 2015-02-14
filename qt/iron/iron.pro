#-------------------------------------------------
#
# Project created by QtCreator 2015-02-05T13:32:36
#
#-------------------------------------------------

ENGINE_PROJ_DIR = D:/data/engine/projects

ARDUINO_DIR     = C:/Program Files (x86)/Arduino
ARDUINO_MCU     = atmega328p
ARDUINO_FCPU    = 16000000
ARDUINO_AVR_DIR = $$ARDUINO_DIR/hardware/tools/avr
ARDUINO_AVR_BUILD = 0

QT -= core gui

PROJECT = iron
TARGET = $$PROJECT
TEMPLATE = lib
CONFIG += staticlib

CONFIG += avr-gcc

avr-gcc {
    TARGET = $$PROJECT-avr

    QMAKE_CC                     = $$ARDUINO_AVR_DIR/bin/avr-gcc
    QMAKE_CFLAGS                 = -s -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$$ARDUINO_MCU -DF_CPU=$$ARDUINO_FCPU
    QMAKE_CFLAGS_DEBUG           =
    QMAKE_CFLAGS_RELEASE         =
    QMAKE_CFLAGS_THREAD          =

    QMAKE_CXX                    = $$ARDUINO_AVR_DIR/bin/avr-g++
    QMAKE_CXXFLAGS               = -s -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$$ARDUINO_MCU -DF_CPU=$$ARDUINO_FCPU
    QMAKE_CXXFLAGS               = -std=c++0x
    QMAKE_CXXFLAGS_DEBUG         =
    QMAKE_CXXFLAGS_RELEASE       =
    QMAKE_CXXFLAGS_THREAD        =
    QMAKE_CXXFLAGS_EXCEPTIONS_ON =
    QMAKE_CXXFLAGS_RTTI_ON       =

    QMAKE_LINK                   = $$ARDUINO_AVR_DIR/bin/avr-gcc
    QMAKE_LFLAGS                 = -s -Os -Wall -mmcu=$$ARDUINO_MCU
    QMAKE_LFLAGS_EXCEPTIONS_ON   =
    QMAKE_LFLAGS_WINDOWS         =
    QMAKE_LN_SHLIB               =
    QMAKE_LIBS                   = -lm
} else {
}

INCLUDEPATH += $$ENGINE_PROJ_DIR/build/ext/serial/include
LIBS += -L$$ENGINE_PROJ_DIR/build/ext/serial/lib -lserial

LIBS += -lsetupapi

INCLUDEPATH += $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino)
INCLUDEPATH += $$quote($$ARDUINO_DIR/hardware/arduino/variants/standard)
INCLUDEPATH += $$quote($$ARDUINO_DIR/hardware/tools/avr/avr/include)
INCLUDEPATH += $$quote($$ARDUINO_DIR/libraries)
INCLUDEPATH += $$quote($$ARDUINO_DIR/libraries/Wire)
INCLUDEPATH += $$quote($$ARDUINO_DIR/libraries/Wire/utility)

SOURCES +=

HEADERS += \
    i2c.hpp \
    utility.hpp \
    iron.hpp \
    types.hpp \
    i2c.hpp \
    cpu_utility.hpp \
    cpu_bus.hpp \
    cpu_bus.ipp \
    mcu_utility.hpp \
    mcu_bus.hpp \
    mcu_bus.ipp \
    bus.hpp \
    bus.ipp \
    irbus.hpp \
    irbus.ipp \
    mcu_pins.hpp \
    attribute.hpp \
    attribute.ipp

headers.path = $$ENGINE_PROJ_DIR/build/$$PROJECT/include
headers.files = $$HEADERS
INSTALLS += headers

#libs.path = $$shell_path($$ENGINE_PROJ_DIR/build/$$PROJECT/lib)
#libs.files = $$DESTDIR_TARGET
#INSTALLS += libs
