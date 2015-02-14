#ifndef ATTRIBUTE_IPP
#define ATTRIBUTE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< class T >
EN_INLINE void setAttribute( uint8_t* buffer,
                             const T& value )
{
    memcpy( buffer, &value, sizeof( T ) );
}

//------------------------------------------------------------------------------
//

template< class T >
EN_INLINE void getAttribute( const uint8_t* buffer,
                             T& value )
{
    memcpy( &value, buffer, sizeof( T ) );
}

} // engine

#endif // ATTRIBUTE_IPP
