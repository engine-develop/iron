#ifndef BUS_MCU_IPP
#define BUS_MCU_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template<>
EN_INLINE Bus< MCU >::Bus()
{
}

//------------------------------------------------------------------------------
//

template<>
EN_INLINE Bus< MCU >::~Bus()
{
    release();
}

//------------------------------------------------------------------------------
//

template<>
EN_INLINE Bus& Bus< MCU >::get()
{
    static Bus< MCU > obj;

    return obj;
}

//------------------------------------------------------------------------------
//

template<>
EN_INLINE void Bus< MCU >::release()
{
}

} // engine

#endif // BUS_MCU_IPP
