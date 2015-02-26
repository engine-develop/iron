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

// Arduino
#ifdef __AVR__
#include <HardwareSerial.h>
#endif // __AVR__

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
// Port adaptor interface
//

struct APort
{
    static EN_INLINE void close( port_obj_t* port );

    static EN_INLINE void setBaudrate( port_obj_t* port,
                                       const uint32_t& baudrate );

    static EN_INLINE uint32_t available( port_obj_t* port );

    static EN_INLINE void write( port_obj_t* port,
                                 const uint8_t* buffer,
                                 size_t size );

    template< class T >
    static EN_INLINE void write( port_obj_t* port,
                                 const T& value );

    template< class T >
    static EN_INLINE void read( port_obj_t* port,
                                T& value );

    static EN_INLINE void read( port_obj_t* port,
                                uint8_t* buffer,
                                size_t size );
};

//------------------------------------------------------------------------------
//

template< int S >
struct PortBuffer
{
    EN_INLINE PortBuffer( port_obj_t* port_ = 0x0 );

    EN_INLINE void reset();

    EN_INLINE void write();

    EN_INLINE void read();

    port_obj_t* port;
    uint16_t i;
    uint8_t data[ S ];
};

} // engine

//------------------------------------------------------------------------------
//

#include "port.ipp"

#endif // PORT_HPP
