#ifndef IR_NODE_IPP
#define IR_NODE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< class N >
EN_INLINE BNode< N >::BNode()
    : m_state( 0 )
{
    setDefaults();
}

//------------------------------------------------------------------------------
//

template< class N >
EN_INLINE BNode< N >::~BNode()
{
}

//------------------------------------------------------------------------------
//

template< class N >
EN_INLINE uint8_t& BNode< N >::state()
{
    return m_state;
}

//------------------------------------------------------------------------------
//

template< class N >
EN_INLINE void BNode< N >::setup()
{
#ifdef __AVR__
    // Set pin modes
    //
    FAttributesSetPinModes< N >::eval();
#endif // __AVR__
}

//------------------------------------------------------------------------------
//

template< class N >
EN_INLINE void BNode< N >::loop()
{
}

//------------------------------------------------------------------------------
//

template< class N >
    template< int AT >
EN_INLINE void BNode< N >::setDefault()
{
    static_assert( AT >= 0 && AT < TNode< N >::numAttributes, "invalid attribute index" );

    FSetAttribute< N, AT >::eval( m_attributes, TAttribute< N, AT >::defaultValue );
}

//------------------------------------------------------------------------------
//

template< class N >
EN_INLINE void BNode< N >::setDefaults()
{
    FAttributesSetDefaults< N >::eval( m_attributes );
}

//------------------------------------------------------------------------------
//

template< class N >
    template< int AT, int V >
EN_INLINE void BNode< N >::set()
{
    static_assert( AT >= 0 && AT < TNode< N >::numAttributes, "invalid attribute index" );

#ifdef __AVR__
    FAttributeSetPin< N, AT >::template eval< V >();
#endif // __AVR__

    typename TAttribute< N, AT >::type_t value( V );
    FSetAttribute< N, AT >::eval( m_attributes, value );
}

//------------------------------------------------------------------------------
//

template< class N >
    template< int AT, class T >
EN_INLINE void BNode< N >::set( const T& value )
{
    static_assert( AT >= 0 && AT < TNode< N >::numAttributes, "invalid attribute index" );

#ifdef __AVR__
    FAttributeSetPin< N, AT >::eval( value );
#endif // __AVR__

    FSetAttribute< N, AT >::eval( m_attributes, value );
}

//------------------------------------------------------------------------------
//

template< class N >
    template< int AT, class T >
EN_INLINE void BNode< N >::get( T& value )
{
    static_assert( AT >= 0 && AT < TNode< N >::numAttributes, "invalid attribute index" );

#ifdef __AVR__
    FAttributeGetPin< N, AT >::eval( value, m_attributes );
#endif // __AVR__

    value = FGetAttribute< N, AT >::template eval< T >( m_attributes );
}

//------------------------------------------------------------------------------
//

template< class N >
    template< int AT, int V >
EN_INLINE bool BNode< N >::is()
{
    typename TAttribute< N, AT >::type_t value;
    get< AT >( value );

    return ( bool( value ) == bool( V ) );
}

//------------------------------------------------------------------------------
//

template< class N >
    template< int AT, class T >
EN_INLINE bool BNode< N >::is( const T& value )
{
    typename TAttribute< N, AT >::type_t value_l;
    get< AT >( value_l );

    return ( value_l == value );
}

} // engine

#endif // IR_NODE_IPP
