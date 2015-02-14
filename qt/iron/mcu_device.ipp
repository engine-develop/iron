#ifndef MCU_DEVICE_IPP
#define MCU_DEVICE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE BDevice< P, MCU >::BDevice()
    : state( Disconnected )
    , id( 0 )
    , baudrate( 9600 )
{
}

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE BDevice< P, MCU >::~BDevice()
{
}

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE void BDevice< P, MCU >::setup( uint8_t id,
                                         uint32_t baudrate )
{
    this->id = id;
    this->baudrate = baudrate;

    Serial.begin( this->baudrate );

    state = Disconnected;
}

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE bool BDevice< P, MCU >::waitConnect()
{
    switch ( Serial.read() )
    {
        case traits_t::ID:
            Serial.write( traits_t::ID );
            break;
        case traits_t::Connect:
            state = Connected;
            break;
        default:
            break;
    }

    return ( state != Connected );
}

//------------------------------------------------------------------------------
//

template< class P >
EN_INLINE bool BDevice< P, MCU >::waitDisconnect()
{
    switch ( Serial.read() )
    {
        case traits_t::ID:
            Serial.write( traits_t::ID );
            break;
        case traits_t::Disconnect:
            state = Disconnected;
            break;
        default:
            break;
    }

    return ( state != Disconnected );
}

//------------------------------------------------------------------------------
//

template< class P >
    template< class T >
size_t BDevice< P, MCU >::write( const T& value )
{
    return Serial.write( value );
}

//------------------------------------------------------------------------------
//

template< class P >
    template< class T >
size_t BDevice< P, MCU >::write( const T* buffer,
                                 size_t size )
{
    return Serial.write( buffer, size );
}

//------------------------------------------------------------------------------
//

template< class P >
    template< class T >
void BDevice< P, MCU >::read( T& value )
{
    value = Serial.read();
}

//------------------------------------------------------------------------------
//

template< class P >
    template< class T >
void BDevice< P, MCU >::read( T* buffer,
                              size_t size )
{
    Serial.read( buffer, size );
}

} // engine

#endif // MCU_DEVICE_IPP
