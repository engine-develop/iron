#ifndef DEVICE_IPP
#define DEVICE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE BDevice< D >::BDevice()
    : state( Disconnected )
    , id( 0 )
    , baudrate( 9600 )
{
    setDefaults();
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE BDevice< D >::~BDevice()
{
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
    template< int A >
EN_INLINE void BDevice< D >::setDefault()
{
    setAttribute( buffer + FAttributeRange< D, A >::begin,
                  TAttribute< D, A >::defaultValue );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE void BDevice< D >::setDefaults()
{
    FAttributesSetDefaults< D >::eval( buffer );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
    template< int A, class T >
EN_INLINE void BDevice< D >::set( const T& value )
{
    setAttribute( buffer + FAttributeRange< D, A >::begin,
                  value );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
    template< int A, class T >
EN_INLINE void BDevice< D >::get( T& value ) const
{
    getAttribute( buffer + FAttributeRange< D, A >::begin,
                  value );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Status BDevice< D >::write() const
{
    return Status_Ok;
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Status BDevice< D >::read()
{
    return Status_Ok;
}

} // engine

#endif // DEVICE_IPP
