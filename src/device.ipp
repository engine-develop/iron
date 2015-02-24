#ifndef DEVICE_IPP
#define DEVICE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE BDevice< D, A >::BDevice()
    : m_state( 0 )
    , m_baudrate( 9600 )
    , m_port( 0x0 )
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
EN_INLINE uint8_t& BDevice< D, A >::state()
{
    return m_state;
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE void BDevice< D, A >::setBaudrate( const uint32_t& baudrate )
{
    m_baudrate = baudrate;

    if ( m_port )
    {
        APort::setBaudrate( m_port, m_baudrate );
    }
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE const uint32_t& BDevice< D, A >::baudrate() const
{
    return m_baudrate;
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE void BDevice< D, A >::setPort( port_obj_t* port )
{
    m_port = port;
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE port_obj_t* BDevice< D, A >::port()
{
    return m_port;
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE void BDevice< D, A >::setup()
{
#ifdef __AVR__
    // Set pin modes
    //
    FAttributesSetPinModes< D >::eval();

    signal< A, Signal_ID >();
#endif // __AVR__
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE Status BDevice< D, A >::preEvaluate()
{
    // Handle ID signal
    //
    if ( wait< A, Signal_ID >( 10 ) == Success )
    {
        signal< A, Signal_ID >();
    }

    // Handle Connect signal
    //
    if ( wait< A, Signal_Connect >( 10 ) == Success )
    {
        m_state |= Connected;
    }

    // Handle Disconnect signal
    //
    if ( wait< A, Signal_Disconnect >( 10 ) == Success )
    {
        m_state &= ~Connected;
    }

    return Success;
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE Status BDevice< D, A >::evaluate()
{
    preEvaluate();

    return Success;
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
    template< int AT >
EN_INLINE void BDevice< D, A >::setDefault()
{
    static_assert( AT >= 0 && AT < TDevice< D >::numAttributes, "invalid attribute index" );

    FSetAttribute< D, AT >::eval( m_attributes, TAttribute< D, AT >::defaultValue );
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE void BDevice< D, A >::setDefaults()
{
    FAttributesSetDefaults< D >::eval( m_attributes );
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
    FSetAttribute< D, AT >::eval( m_attributes, value );
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

    FSetAttribute< D, AT >::eval( m_attributes, value );
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
    template< int AT, class T >
EN_INLINE void BDevice< D, A >::get( T& value )
{
    static_assert( AT >= 0 && AT < TDevice< D >::numAttributes, "invalid attribute index" );

#ifdef __AVR__
    FAttributeGetPin< D, AT >::eval( value, m_attributes );
#endif // __AVR__

    value = FGetAttribute< D, AT >::template eval< T >( m_attributes );
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
