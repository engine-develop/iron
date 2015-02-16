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
    setAttribute( attributes + FAttributeRange< D, A >::begin,
                  TAttribute< D, A >::defaultValue );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE void BDevice< D >::setDefaults()
{
    FAttributesSetDefaults< D >::eval( attributes );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
    template< int A, int V >
EN_INLINE void BDevice< D >::set()
{
#ifdef __AVR__
    FAttributeSetPin< D, A >::eval< V >();
#endif // __AVR__

    setAttribute( attributes + FAttributeRange< D, A >::begin,
                  TAttribute< D, A >::type_t( V ) );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
    template< int A, class T >
EN_INLINE void BDevice< D >::set( const T& value )
{
#ifdef __AVR__
    FAttributeSetPin< D, A >::eval( value );
#endif // __AVR__

    setAttribute( attributes + FAttributeRange< D, A >::begin,
                  value );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
    template< int A, class T >
EN_INLINE void BDevice< D >::get( T& value ) const
{
#ifdef __AVR__
    FAttributeGetPin< D, A >::eval( value );

    setAttribute( attributes + FAttributeRange< D, A >::begin,
                  value );
#endif // __AVR__

    getAttribute( attributes + FAttributeRange< D, A >::begin,
                  value );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Status BDevice< D >::write() const
{
    return Success;
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE Status BDevice< D >::read()
{
    return Success;
}

} // engine

#endif // DEVICE_IPP
