#ifndef BUS_MCU_IPP
#define BUS_MCU_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

EN_INLINE Bus< MCU >::Bus()
{
    Serial.begin( 9600 );

    setPort( &Serial );
}

//------------------------------------------------------------------------------
//

EN_INLINE Bus< MCU >::~Bus()
{
    release();
}

//------------------------------------------------------------------------------
//

EN_INLINE Bus< MCU >& Bus< MCU >::get()
{
    static Bus< MCU > obj;

    return obj;
}

//------------------------------------------------------------------------------
//

EN_INLINE void Bus< MCU >::release()
{
}

} // engine

#endif // BUS_MCU_IPP
