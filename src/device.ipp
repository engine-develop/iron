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
    , port( 0x0 )
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
EN_INLINE void BDevice< D, A >::setup()
{
#ifdef __AVR__
    FAttributesSetPinModes< D >::eval();
#endif // __AVR__
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE Status BDevice< D, A >::evaluate()
{
    return Success;
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE void BDevice< D, A >::setPort( port_t* p )
{
    port = p;
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE typename BDevice< D, A >::port_t* BDevice< D, A >::port()
{
    return port;
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
    template< int S >
EN_INLINE bool BDevice< D, A >::wait()
{
    return wait< D, S >( port, this );
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
    static_assert( AT >= 0 && AT < TDevice< D >::numAttributes, "invalid attribute index" );

#ifdef __AVR__
    FAttributeGetPin< D, AT >::eval( value, attributes );
#endif // __AVR__

    value = FGetAttribute< D, AT >::template eval< T >( attributes );
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
    template< int AT, int V >
EN_INLINE bool BDevice< D, A >::is()
{
    typename TAttribute< D, AT >::type_t value;
    get< AT >( value );

    return ( bool( value ) == bool( V ) );
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
    template< int AT, class T >
EN_INLINE bool BDevice< D, A >::is( const T& value )
{
    typename TAttribute< D, AT >::type_t value_l;
    get< AT >( value_l );

    return ( value_l == value );
}

} // engine

#endif // DEVICE_IPP
