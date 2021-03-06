#ifndef TIMER_HPP
#define TIMER_HPP

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
#ifndef __AVR__
#include <chrono>
#endif // __AVR__

// Engine
#include "utility.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

struct Timer
{
#ifdef __AVR__
    typedef uint32_t time_t;
#else
    typedef std::chrono::high_resolution_clock hr_clock_t;
    typedef hr_clock_t::time_point time_t;
#endif // __AVR__

    EN_INLINE Timer( bool start = false );

    EN_INLINE void reset();

    EN_INLINE uint32_t elapsed();

    time_t start;
};

} // engine

//------------------------------------------------------------------------------
//

#include "timer.ipp"

#endif // TIMER_HPP
