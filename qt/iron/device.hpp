#ifndef DEVICE_HPP
#define DEVICE_HPP

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
#include "attribute.hpp"

//------------------------------------------------------------------------------
//

#define EN_DEVICE_CLASS( CNAME ) \
    template< class P, int A > \
    struct CNAME : BDevice< P, A > \
            , AttributeContainer< CNAME > \

namespace engine
{

//------------------------------------------------------------------------------
//

template< class P, int A = CPU >
struct BDevice
{
};

//------------------------------------------------------------------------------
//

template< class P, int A = CPU >
struct Device : BDevice< P, A >
{
};

} // engine

#endif // DEVICE_HPP
