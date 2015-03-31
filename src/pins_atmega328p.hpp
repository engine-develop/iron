#ifndef IR_PINS_ATMEGA328P_HPP
#define IR_PINS_ATMEGA328P_HPP

// Copyright (C) 2015 Engine Development
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

namespace engine
{

// Pin aliases
//
static const uint8_t SS   = 10;
static const uint8_t MOSI = 11;
static const uint8_t MISO = 12;
static const uint8_t SCK  = 13;

static const uint8_t SDA = 18;
static const uint8_t SCL = 19;
#define LED_BUILTIN 13

static const uint8_t A0 = 14;
static const uint8_t A1 = 15;
static const uint8_t A2 = 16;
static const uint8_t A3 = 17;
static const uint8_t A4 = 18;
static const uint8_t A5 = 19;
static const uint8_t A6 = 20;
static const uint8_t A7 = 21;

// Port B
//
IRON_DEFINE_PIN( 8,  B, 0, false, false )
IRON_DEFINE_PIN( 9,  B, 1, true,  false )
IRON_DEFINE_PIN( 10, B, 2, true,  false )
IRON_DEFINE_PIN( 11, B, 3, true,  false )
IRON_DEFINE_PIN( 12, B, 4, false, false )
IRON_DEFINE_PIN( 13, B, 5, false, false )
IRON_DEFINE_PIN_PWM( 9,  TCCR1A, COM1A1, OCR1A )
IRON_DEFINE_PIN_PWM( 10, TCCR1A, COM1B1, OCR1B )
IRON_DEFINE_PIN_PWM( 11, TCCR2A, COM2A1, OCR2A )

// Port C
//
IRON_DEFINE_PIN( A0, C, 0, true, true )
IRON_DEFINE_PIN( A1, C, 1, true, true )
IRON_DEFINE_PIN( A2, C, 2, true, true )
IRON_DEFINE_PIN( A3, C, 3, true, true )
IRON_DEFINE_PIN( A4, C, 4, true, true )
IRON_DEFINE_PIN( A5, C, 5, true, true )

// Port D
//
IRON_DEFINE_PIN( 0, D, 0, false, false )
IRON_DEFINE_PIN( 1, D, 1, false, false )
IRON_DEFINE_PIN( 2, D, 2, false, false )
IRON_DEFINE_PIN( 3, D, 3, true,  false )
IRON_DEFINE_PIN( 4, D, 4, false, false )
IRON_DEFINE_PIN( 5, D, 5, true,  false )
IRON_DEFINE_PIN( 6, D, 6, true,  false )
IRON_DEFINE_PIN( 7, D, 7, false, false )
IRON_DEFINE_PIN_PWM( 3, TCCR2A, COM2B1, OCR2B )
IRON_DEFINE_PIN_PWM( 5, TCCR0A, COM0B1, OCR0B )
IRON_DEFINE_PIN_PWM( 6, TCCR0A, COM0A1, OCR0A )

} // engine

#endif // IR_PINS_ATMEGA328P_HPP
