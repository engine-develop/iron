#ifndef IRON_HPP
#define IRON_HPP

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

#ifndef __AVR__
#if __cplusplus < 201103L
#error library requires C++11 support
#endif
#endif // __AVR__

//------------------------------------------------------------------------------
//

// Engine
#include "version.hpp"
#include "utility.hpp"
#include "types.hpp"
#include "timer.hpp"
#include "pins.hpp"
#include "attribute.hpp"
#include "port.hpp"
#include "signal.hpp"
#include "device.hpp"
#include "node.hpp"
#include "sync.hpp"
#include "bus.hpp"

#ifndef __AVR__
#include "typestore.hpp"
#endif // __AVR__

#endif // IRON_HPP
