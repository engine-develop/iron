#ifndef PORT_HPP
#define PORT_HPP

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

// Engine
#include "types.hpp"

#ifndef __AVR__
#include "port_cpu.hpp"
#endif // __AVR__

namespace engine
{

//------------------------------------------------------------------------------
//

template< int A >
struct TPort
{
    typedef int obj_t;
};

//------------------------------------------------------------------------------
//
#ifndef __AVR__
template<>
struct TPort< CPU >
{
    typedef Serial obj_t;
};
#endif // __AVR__

//------------------------------------------------------------------------------
//
#ifdef __AVR__
template<>
struct TPort< MCU >
{
    typedef HardwareSerial obj_t;
};
#endif // __AVR__

} // engine

#endif // PORT_HPP
