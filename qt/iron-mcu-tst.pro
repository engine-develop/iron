ENGINE_PROJ_DIR = D:/data/engine/projects

ARDUINO_DIR     = C:/Program Files (x86)/Arduino
ARDUINO_MCU     = atmega328p
ARDUINO_FCPU    = 16000000
ARDUINO_PORT    = COM3
ARDUINO_AVR_DIR = $$ARDUINO_DIR/hardware/tools/avr

QT -= gui core
CONFIG -= qt
TEMPLATE = app

INCLUDEPATH += $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino)
INCLUDEPATH += $$quote($$ARDUINO_DIR/hardware/arduino/variants/standard)
INCLUDEPATH += $$quote($$ARDUINO_DIR/hardware/tools/avr/avr/include)
INCLUDEPATH += $$quote($$ARDUINO_DIR/libraries)

INCLUDEPATH += $$ENGINE_PROJ_DIR/build/iron/include

QMAKE_CC                     = $$ARDUINO_AVR_DIR/bin/avr-gcc
QMAKE_CFLAGS                 = -s -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$$ARDUINO_MCU -DF_CPU=$$ARDUINO_FCPU
QMAKE_CFLAGS_DEBUG           =
QMAKE_CFLAGS_RELEASE         =
QMAKE_CFLAGS_THREAD          =

QMAKE_CXX                    = $$ARDUINO_AVR_DIR/bin/avr-gcc
QMAKE_CXXFLAGS               = -s -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$$ARDUINO_MCU -DF_CPU=$$ARDUINO_FCPU
QMAKE_CXXFLAGS              += -std=c++0x
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

QMAKE_POST_LINK += $$quote($$ARDUINO_AVR_DIR/bin/avr-objcopy -O ihex -R .eeprom ${DESTDIR_TARGET} ${DESTDIR_TARGET}.hex $$escape_expand(\\n\\t))
QMAKE_POST_LINK += $$quote($$ARDUINO_AVR_DIR/bin/avrdude -C $$shell_quote($$ARDUINO_AVR_DIR/etc/avrdude.conf) -F -V -c arduino -p $$upper($$ARDUINO_MCU) -P $$ARDUINO_PORT -b 115200 -U flash:w:$$shell_quote(${DESTDIR_TARGET}.hex) $$escape_expand(\\n\\t))

HEADERS += \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/Arduino.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/binary.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/Client.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/HardwareSerial.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/IPAddress.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/new.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/Platform.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/Print.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/Printable.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/Server.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/Stream.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/Udp.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/USBAPI.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/USBCore.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/USBDesc.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/WCharacter.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/wiring_private.h) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/WString.h)

SOURCES += \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/WInterrupts.c) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/wiring.c) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/wiring_analog.c) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/wiring_digital.c) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/wiring_pulse.c) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/wiring_shift.c) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/WString.cpp) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/WMath.cpp) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/USBCore.cpp) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/Tone.cpp) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/Stream.cpp) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/Print.cpp) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/new.cpp) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/main.cpp) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/IPAddress.cpp) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/HID.cpp) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/HardwareSerial.cpp) \
    $$quote($$ARDUINO_DIR/hardware/arduino/cores/arduino/CDC.cpp) \
    ../tst/iron-avr-tst/sketch.cpp
