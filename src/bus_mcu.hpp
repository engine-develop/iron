#ifndef BUS_MCU_HPP
#define BUS_MCU_HPP

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
#include "bus.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

template<>
class Bus< MCU >
    : public BBus
{

public:

    //------
    //

    static EN_INLINE Bus& get();

protected:

    EN_INLINE Bus();
    EN_INLINE ~Bus();
    EN_INLINE Bus( const Bus& ) {}
    EN_INLINE Bus& operator=( const Bus& ) { return *this; }

    EN_INLINE void release();

};

} // engine

//------------------------------------------------------------------------------
//

#include "bus_mcu.ipp"

#endif // BUS_MCU_HPP
