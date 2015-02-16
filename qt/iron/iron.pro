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

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += $$ENGINE_PROJ_DIR/build/ext/serial/include
LIBS += -L$$ENGINE_PROJ_DIR/build/ext/serial/lib -lserial

win32 {
    LIBS += -lsetupapi
}

INCLUDEPATH += $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino)
INCLUDEPATH += $$quote($$ARDUINO_DIR/hardware/arduino/variants/standard)
INCLUDEPATH += $$quote($$ARDUINO_DIR/hardware/tools/avr/avr/include)
INCLUDEPATH += $$quote($$ARDUINO_DIR/libraries)
INCLUDEPATH += $$quote($$ARDUINO_DIR/libraries/Wire)
INCLUDEPATH += $$quote($$ARDUINO_DIR/libraries/Wire/utility)

SOURCES +=

HEADERS += \
    attribute.hpp \
    attribute.ipp \
    bus_cpu.hpp \
    bus_cpu.ipp \
    device.hpp \
    device.ipp \
    device_cpu.hpp \
    device_cpu.ipp \
    device_mcu.hpp \
    device_mcu.ipp \
    i2c.hpp \
    iron.hpp \
    pins_mcu.hpp \
    types.hpp \
    utility.hpp \
    utility_cpu.hpp \
    utility_mcu.hpp \
    version.hpp

headers.path = $$ENGINE_PROJ_DIR/build/$$PROJECT/include
headers.files = $$HEADERS
INSTALLS += headers

#libs.path = $$shell_path($$ENGINE_PROJ_DIR/build/$$PROJECT/lib)
#libs.files = $$DESTDIR_TARGET
#INSTALLS += libs

OTHER_FILES +=
