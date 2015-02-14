#ifndef IRON_HPP
#define IRON_HPP

//------------------------------------------------------------------------------
//

// Engine
#include "types.hpp"
#include "utility.hpp"
#include "bus.hpp"
#include "irbus.hpp"
#include "i2c.hpp"
#include "attribute.hpp"

#ifdef __AVR__
#include "mcu_utility.hpp"
#include "mcu_pins.hpp"
#include "mcu_bus.hpp"
#else
#include "cpu_utility.hpp"
#include "cpu_bus.hpp"
#endif // __AVR__

#endif // IRON_HPP
