#ifndef NODE_IPP
#define NODE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE BNode< D, A >::BNode()
    : m_state( 0 )
{
    setDefaults();
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE BNode< D, A >::~BNode()
{
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE uint8_t& BNode< D, A >::state()
{
    return m_state;
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE void BNode< D, A >::setup()
{
#ifdef __AVR__
    // Set pin modes
    //
    FAttributesSetPinModes< D >::eval();
#endif // __AVR__
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE void BNode< D, A >::loop()
{
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
    template< int AT >
EN_INLINE void BNode< D, A >::setDefault()
{
    static_assert( AT >= 0 && AT < TNode< D >::numAttributes, "invalid attribute index" );

    FSetAttribute< D, AT >::eval( m_attributes, TAttribute< D, AT >::defaultValue );
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
EN_INLINE void BNode< D, A >::setDefaults()
{
    FAttributesSetDefaults< D >::eval( m_attributes );
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
    template< int AT, int V >
EN_INLINE void BNode< D, A >::set()
{
    static_assert( AT >= 0 && AT < TNode< D >::numAttributes, "invalid attribute index" );

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
EN_INLINE void BNode< D, A >::set( const T& value )
{
    static_assert( AT >= 0 && AT < TNode< D >::numAttributes, "invalid attribute index" );

#ifdef __AVR__
    FAttributeSetPin< D, AT >::eval( value );
#endif // __AVR__

    FSetAttribute< D, AT >::eval( m_attributes, value );
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
    template< int AT, class T >
EN_INLINE void BNode< D, A >::get( T& value )
{
    static_assert( AT >= 0 && AT < TNode< D >::numAttributes, "invalid attribute index" );

#ifdef __AVR__
    FAttributeGetPin< D, AT >::eval( value, m_attributes );
#endif // __AVR__

    value = FGetAttribute< D, AT >::template eval< T >( m_attributes );
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
    template< int AT, int V >
EN_INLINE bool BNode< D, A >::is()
{
    typename TAttribute< D, AT >::type_t value;
    get< AT >( value );

    return ( bool( value ) == bool( V ) );
}

//------------------------------------------------------------------------------
//

template< template< int > class D, int A >
    template< int AT, class T >
EN_INLINE bool BNode< D, A >::is( const T& value )
{
    typename TAttribute< D, AT >::type_t value_l;
    get< AT >( value_l );

    return ( value_l == value );
}

} // engine

#endif // NODE_IPP
