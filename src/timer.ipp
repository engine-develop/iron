#ifndef IR_TIMER_IPP
#define IR_TIMER_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

IRON_INLINE Timer::Timer( bool start )
    : start( time_t() )
{
    if ( start ) reset();
}

//------------------------------------------------------------------------------
//

IRON_INLINE void Timer::reset()
{
#ifdef __AVR__
    start = millis();
#else
    start = hr_clock_t::now();
#endif // __AVR__
}

//------------------------------------------------------------------------------
//

IRON_INLINE uint32_t Timer::elapsed()
{
#ifdef __AVR__
    return millis() - start;
#else
    return std::chrono::duration_cast< std::chrono::milliseconds >(
                hr_clock_t::now() - start ).count();
#endif // __AVR__
}

} // engine

#endif // IR_TIMER_IPP
