#ifndef IR_VERSION_HPP
#define IR_VERSION_HPP

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

// Engine
#include "utility.hpp"

//------------------------------------------------------------------------------
//

#define IRON_API_VERSION_MAJOR 0
#define IRON_API_VERSION_MINOR 1
#define IRON_API_VERSION_PATCH 0

#define IRON_API_VERSION_S \
    IRON_STRING( IRON_API_VERSION_MAJOR ) "." \
    IRON_STRING( IRON_API_VERSION_MINOR ) "." \
    IRON_STRING( IRON_API_VERSION_PATCH )

namespace engine
{

//------------------------------------------------------------------------------
//

IRON_INLINE const char* getAPIVersion()
{
    return IRON_API_VERSION_S;
}

} // engine

#endif // IR_VERSION_HPP
