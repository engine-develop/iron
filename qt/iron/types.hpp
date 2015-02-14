#ifndef TYPES_HPP
#define TYPES_HPP

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
#include <stdint.h>

namespace engine
{

//------------------------------------------------------------------------------
//

enum Status
{
    Status_Error      = 0,
    Status_Ok         = 1,
    Status_InvalidArg = 2
};

//------------------------------------------------------------------------------
//

enum ArchType
{
    CPU = 0,
    MCU = 1
};

//------------------------------------------------------------------------------
//

enum Connectivity
{
    Disconnected = 0x0,
    Connected    = 0x1
};

} // engine

#endif // TYPES_HPP
