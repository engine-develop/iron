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
#include "bus.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

template< class P >
struct BDevice< P, CPU >
{
    typedef TBus< P > traits_t;

    //------
    //

    EN_INLINE BDevice();

    EN_INLINE ~BDevice();

    //------
    //

    template< class T >
    EN_INLINE size_t write( const T& value );

    template< class T >
    EN_INLINE size_t write( const T* buffer,
                            size_t size );

    template< class T >
    EN_INLINE void read( T& value );

    template< class T >
    EN_INLINE void read( T* buffer,
                         size_t size );

    //------
    //

    uint8_t state;
    uint8_t id;
    uint32_t baudrate;

    serial::Serial* port;
};

//------------------------------------------------------------------------------
//

template< class P >
class Bus
{

public:

    //------
    //

    typedef TBus< P > traits_t;

    static EN_INLINE Bus& get();

    //------
    //

    EN_INLINE std::vector< Device< P, CPU > >& scan();

    EN_INLINE std::vector< Device< P, CPU > >& devices();

    EN_INLINE Status connect( Device< P, CPU >& device );

    EN_INLINE Status disconnect( Device< P, CPU >& device );

protected:

    EN_INLINE Bus() {}
    EN_INLINE ~Bus();
    EN_INLINE Bus( const Bus& ) {}
    EN_INLINE Bus& operator=( const Bus& ) {}

    EN_INLINE void release();

    std::vector< Device< P, CPU > > m_devices;

};

} // engine

//------------------------------------------------------------------------------
//

#include "cpu_bus.ipp"

#endif // CPU_BUS_HPP
