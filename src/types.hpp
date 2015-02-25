#ifndef TYPES_HPP
#define TYPES_HPP

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

//------------------------------------------------------------------------------
//

// STD
#include <stdint.h>

namespace engine
{

//------------------------------------------------------------------------------
//

enum Status
{
    Error      = 0,
    Success    = 1,
    InvalidArg = 2,
    TimeOut    = 3,
    Begin      = 0,
    End        = 0,
    Continue   = 1
};

//------------------------------------------------------------------------------
//

enum ArchType
{
    CPU = 0x0,
    MCU = 0x1
};

//------------------------------------------------------------------------------
//

template< int A >
struct TArchType
{
    static const uint8_t opposite = 0;
};

template<>
struct TArchType< CPU >
{
    static const uint8_t opposite = MCU;
};

template<>
struct TArchType< MCU >
{
    static const uint8_t opposite = CPU;
};

//------------------------------------------------------------------------------
//

enum LogicLevel
{
    Low  = 0x0,
    High = 0x1
};

//------------------------------------------------------------------------------
//

enum Selection
{
    Any  = 0x0,
    None = 0xFF
};

//------------------------------------------------------------------------------
//

enum State
{
    Selected = 0x1,
    Idle     = 0x2
};

//------------------------------------------------------------------------------
//

typedef uint8_t  digital_t;
typedef uint16_t analog_t;

} // engine

#endif // TYPES_HPP
