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
#include "utility.hpp"

#ifndef __AVR__
#include "port_cpu.hpp"
#endif // __AVR__

namespace engine
{

//------------------------------------------------------------------------------
//

#ifdef __AVR__
typedef HardwareSerial port_obj_t;
#else
typedef Serial port_obj_t;
#endif // __AVR__

//------------------------------------------------------------------------------
//

EN_INLINE uint32_t available( port_obj_t* port );

//------------------------------------------------------------------------------
//

template< class T >
EN_INLINE void write( port_obj_t* port,
                      const T& value );

//------------------------------------------------------------------------------
//

template< class T >
EN_INLINE void read( port_obj_t* port,
                     T& value );

} // engine

//------------------------------------------------------------------------------
//

#include "port.ipp"

#endif // PORT_HPP
