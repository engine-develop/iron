#ifndef BUS_CPU_HPP
#define BUS_CPU_HPP

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

// Serial
#include <serial/serial.h>

// Engine
#include "device.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int > class D >
class Bus
{

public:

    typedef TDevice< D > traits_t;

    //------
    //

    static EN_INLINE Bus& get();

    //------
    //

    EN_INLINE std::vector< D< CPU > >& scan();

    EN_INLINE std::vector< D< CPU > >& devices();

    EN_INLINE Status connect( D< CPU >& device );

    EN_INLINE Status disconnect( D< CPU >& device );

protected:

    EN_INLINE Bus() {}
    EN_INLINE ~Bus();
    EN_INLINE Bus( const Bus& ) {}
    EN_INLINE Bus& operator=( const Bus& ) {}

    EN_INLINE void release();

    std::vector< D< CPU > > m_devices;

};

} // engine

//------------------------------------------------------------------------------
//

#include "bus.ipp"

#endif // BUS_CPU_HPP
