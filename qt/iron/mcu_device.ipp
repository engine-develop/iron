#ifndef MCU_DEVICE_IPP
#define MCU_DEVICE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE BDevice< D, MCU >::BDevice()
    : state( Disconnected )
    , id( 0 )
    , baudrate( 9600 )
{
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE BDevice< D, MCU >::~BDevice()
{
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE void BDevice< D, MCU >::setup( uint8_t id,
                                         uint32_t baudrate )
{
    this->id = id;
    this->baudrate = baudrate;

    Serial.begin( this->baudrate );

    state = Disconnected;
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE bool BDevice< D, MCU >::waitConnect()
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

template< template< int > class D >
EN_INLINE bool BDevice< D, MCU >::waitDisconnect()
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

template< template< int > class D >
    template< class T >
size_t BDevice< D, MCU >::write( const T& value )
{
    return Serial.write( value );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
    template< class T >
size_t BDevice< D, MCU >::write( const T* buffer,
                                 size_t size )
{
    return Serial.write( buffer, size );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
    template< class T >
void BDevice< D, MCU >::read( T& value )
{
    value = Serial.read();
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
    template< class T >
void BDevice< D, MCU >::read( T* buffer,
                              size_t size )
{
    Serial.read( buffer, size );
}

} // engine

#endif // MCU_DEVICE_IPP
