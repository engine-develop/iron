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
#include "ov7670.hpp"

#ifdef __AVR__
#include "mcu/mcu_utility.hpp"
#include "mcu/mcu_bus.hpp"
#else
#include "cpu/cpu_utility.hpp"
#include "cpu/cpu_bus.hpp"
#endif // __AVR__

#endif // IRON_HPP
