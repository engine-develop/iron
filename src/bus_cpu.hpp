#ifndef IR_BUS_CPU_HPP
#define IR_BUS_CPU_HPP

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
#include <vector>

// Engine
#include "bus.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

template<>
class Bus< CPU >
    : public BBus
{

public:

    //----------
    //

    static IRON_INLINE Bus& get();

    //----------
    // Fields
    //

    IRON_INLINE std::vector< port_obj_t* >& ports();

    //----------
    // Devices
    //

    template< class N >
    IRON_INLINE std::vector< N > scan();

    template< class N >
    IRON_INLINE Status select( N& device );

    template< class N >
    IRON_INLINE Status deselect( N& device );

protected:

    IRON_INLINE Bus();
    IRON_INLINE ~Bus();
    IRON_INLINE Bus( const Bus& ) {}
    IRON_INLINE Bus& operator=( const Bus& ) { return *this; }

    IRON_INLINE void release();

    std::vector< port_obj_t* > m_ports;

};

//------------------------------------------------------------------------------
//

template< class N >
IRON_INLINE std::vector< N > scan();

//------------------------------------------------------------------------------
//

template< class N >
IRON_INLINE Status select( N& device );

//------------------------------------------------------------------------------
//

template< class N >
IRON_INLINE Status deselect( N& device );

} // engine

//------------------------------------------------------------------------------
//

#include "bus_cpu.ipp"

#endif // IR_BUS_CPU_HPP
