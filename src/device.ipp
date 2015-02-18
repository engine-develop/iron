#ifndef DEVICE_IPP
#define DEVICE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE BDevice< D, A >::BDevice()
    : state( Disconnected )
    , id( 0 )
    , baudrate( 9600 )
{
    setDefaults();
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE BDevice< D, A >::~BDevice()
{
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
    template< int AT >
EN_INLINE void BDevice< D, A >::setDefault()
{
    static_assert( AT >= 0 && AT < TDevice< D >::numAttributes, "invalid attribute index" );

    FSetAttribute< D, AT >::eval( attributes, TAttribute< D, AT >::defaultValue );
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE void BDevice< D, A >::setDefaults()
{
    FAttributesSetDefaults< D >::eval( attributes );
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
    template< int AT, int V >
EN_INLINE void BDevice< D, A >::set()
{
    static_assert( AT >= 0 && AT < TDevice< D >::numAttributes, "invalid attribute index" );

#ifdef __AVR__
    FAttributeSetPin< D, AT >::template eval< V >();
#endif // __AVR__

    typename TAttribute< D, AT >::type_t value( V );
    FSetAttribute< D, AT >::eval( attributes, value );
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
    template< int AT, class T >
EN_INLINE void BDevice< D, A >::set( const T& value )
{
    static_assert( AT >= 0 && AT < TDevice< D >::numAttributes, "invalid attribute index" );

#ifdef __AVR__
    FAttributeSetPin< D, AT >::eval( value );
#endif // __AVR__

    FSetAttribute< D, AT >::eval( attributes, value );
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
    template< int AT, class T >
EN_INLINE void BDevice< D, A >::get( T& value )
{
    //static_assert( TAttribute< D, AT >::mode != Output, "invalid attribute mode: cannot get outputs" );
    static_assert( AT >= 0 && AT < TDevice< D >::numAttributes, "invalid attribute index" );

#ifdef __AVR__
    FAttributeGetPin< D, AT >::eval( value, attributes );
#endif // __AVR__

    value = FGetAttribute< D, AT >::template eval< T >( attributes );
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE Status BDevice< D, A >::write() const
{
    return Success;
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE Status BDevice< D, A >::read()
{
    return Success;
}

} // engine

#endif // DEVICE_IPP
