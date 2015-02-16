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

// Engine
#include "version.hpp"
#include "utility.hpp"
#include "types.hpp"
#include "attribute.hpp"
#include "device.hpp"
#include "i2c.hpp"

#ifdef __AVR__
#include "utility_mcu.hpp"
#include "pins_mcu.hpp"
#include "device_mcu.hpp"
#else
#include "utility_cpu.hpp"
#include "device_cpu.hpp"
#include "bus_cpu.hpp"
#endif // __AVR__

#endif // IRON_HPP
