#ifndef BUS_HPP
#define BUS_HPP

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
#include "timer.hpp"
#include "signal.hpp"
#include "port.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

class BBus
{

public:

    EN_INLINE BBus();

    EN_INLINE ~BBus();

    //------
    // Fields
    //

    EN_INLINE void setPort( port_obj_t* port );

    EN_INLINE port_obj_t* port();

    //------
    // Signals
    //

    template< class S >
    EN_INLINE Status signal( port_obj_t* port );

    template< class S >
    EN_INLINE Status wait( port_obj_t* port,
                           uint32_t timeout = uint32_t( -1 ) );

    template< class S >
    EN_INLINE Status signal();

    template< class S >
    EN_INLINE Status wait( uint32_t timeout = uint32_t( -1 ) );

protected:

    port_obj_t* m_port;

};

//------------------------------------------------------------------------------
//

template< int A >
class Bus
    : public BBus
{
};

//------------------------------------------------------------------------------
//

template< int A, class S >
EN_INLINE Status signal();

//------------------------------------------------------------------------------
//

template< int A, class S >
EN_INLINE Status wait( uint32_t timeout = uint32_t( -1 ) );

} // engine

//------------------------------------------------------------------------------
//

#include "bus.ipp"

#ifdef __AVR__
#include "bus_mcu.hpp"
#else
#include "bus_cpu.hpp"
#endif // __AVR__

#endif // BUS_HPP
