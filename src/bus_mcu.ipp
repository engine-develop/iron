#ifndef IR_BUS_MCU_IPP
#define IR_BUS_MCU_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

IRON_INLINE Bus< MCU >::Bus()
{
    Serial.begin( 9600 );

    setPort( &Serial );
}

//------------------------------------------------------------------------------
//

IRON_INLINE Bus< MCU >::~Bus()
{
    release();
}

//------------------------------------------------------------------------------
//

IRON_INLINE Bus< MCU >& Bus< MCU >::get()
{
    static Bus< MCU > obj;

    return obj;
}

//------------------------------------------------------------------------------
//

IRON_INLINE void Bus< MCU >::release()
{
}

} // engine

#endif // IR_BUS_MCU_IPP
