#ifndef CPU_BUS_HPP
#define CPU_BUS_HPP

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
#include "../bus.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

template< class P >
struct BBusDevice< P, CPU >
{
    serial::Serial port;
};

//------------------------------------------------------------------------------
//

template< class P >
struct Bus< P, CPU > : BBus
{
    typedef TBus< P > traits_t;

    static EN_INLINE std::vector< BusDevice< P, CPU > > listDevices();

    static EN_INLINE Bus_Status connect( const BusDevice< P, CPU >& device,
                                         const uint16_t& baudRate = 9600 );

    static EN_INLINE Bus_Status disconnect( const BusDevice< P, CPU >& device );
};

} // engine

//------------------------------------------------------------------------------
//

#include "cpu_bus.ipp"

#endif // CPU_BUS_HPP
