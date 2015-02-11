#ifndef OV7670_HPP
#define OV7670_HPP

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

#ifdef __AVR__

//------------------------------------------------------------------------------
//

// Engine
#include "utility.hpp"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Pin Mappings: Arduino UNO
//

#define PCLK     2 // Pixel clock
#define VSYNC    3 // Vertical sync
#define D4       4 // Data
#define D5       5 // Data
#define D6       6 // Data
#define D7       7 // Data
#define HREF     8 // Horizontal sync
#define XCLK     9 // System clock
#define D0      A0 // Data
#define D1      A1 // Data
#define D2      A2 // Data
#define D3      A3 // Data
#define SIO_D   A4 // SDA data
#define SIO_C   A5 // SCL clock
#define V3V3       // Power - 3.3V
#define GND        // Ground - GND
#define RESET      // Reset (active low) - 3.3V
#define PWDN       // Power down - GND

//------------------------------------------------------------------------------

namespace engine
{

//------------------------------------------------------------------------------
// Color model
//

enum ColorModel
{
    qqVGA  = 0,
    qVGA   = 1,
    rgb565 = 2,
    rgbRAW = 3
};

//#define qqVGA
//#define qVGA
//#define rgb565
#define rgbRAW

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// OV7670 Object
//

class OV7670
{
public:

    OV7670();

    ~OV7670();

    static void writeReg( uint8_t addr,
                          uint8_t data );

    static uint8_t readReg( uint8_t addr );

    void setup();

    static void read( uint16_t ws,
                      uint16_t hs,
                      uint16_t wg,
                      uint16_t hg );

protected:

    // I2C device addresses
    //
    static const uint8_t s_addr_w = 0x42;
    static const uint8_t s_addr_r = 0x43;
};

//------------------------------------------------------------------------------

} // engine

#endif // __AVR__

#endif // OV7670_HPP
