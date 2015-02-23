#ifndef TIMER_IPP
#define TIMER_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

EN_INLINE Timer::Timer( bool start )
    : start( time_t() )
{
    if ( start ) reset();
}

//------------------------------------------------------------------------------
//

EN_INLINE void Timer::reset()
{
#ifdef __AVR__
    start = millis();
#else
    start = hr_clock_t::now();
#endif // __AVR__
}

//------------------------------------------------------------------------------
//

EN_INLINE uint32_t Timer::elapsed()
{
#ifdef __AVR__
    return millis() - start;
#else
    return std::chrono::duration_cast< std::chrono::milliseconds >(
                hr_clock_t::now() - start ).count();
#endif // __AVR__
}

} // engine

#endif // TIMER_IPP
