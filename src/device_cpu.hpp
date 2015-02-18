#ifndef DEVICE_CPU_HPP
#define DEVICE_CPU_HPP

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

// Serial
#include <serial/serial.h>

// Engine
#include "device.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int > class D >
struct Device< D, CPU > : BDevice< D, CPU >
{
    typedef serial::Serial port_t;

    //------
    //

    EN_INLINE Device();

    EN_INLINE ~Device();

    EN_INLINE void setup( uint32_t baudrate );

    //------
    //

    EN_INLINE void setPort( port_t* port );

    EN_INLINE port_t* port();

    //------
    //

    port_t* m_port;

};

} // engine

//------------------------------------------------------------------------------
//

#include "device_cpu.ipp"

#endif // DEVICE_CPU_HPP
