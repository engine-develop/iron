#ifndef MCU_BUS_HPP
#define MCU_BUS_HPP

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
#include <Arduino.h>

// Engine
#include "bus.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

template< class P >
struct BDevice< P, MCU >
{
    typedef TBus< P > traits_t;

    //------
    //

    EN_INLINE BDevice();

    EN_INLINE ~BDevice();

    EN_INLINE void setup( uint8_t i_id,
                          uint32_t i_baudrate );

    EN_INLINE bool waitConnect();

    EN_INLINE bool waitDisconnect();

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
};

} // engine

//------------------------------------------------------------------------------
//

#include "mcu_bus.ipp"

#endif // MCU_BUS_HPP
