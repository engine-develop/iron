#ifndef ATTRIBUTE_IPP
#define ATTRIBUTE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< class V >
EN_INLINE void setAttribute( const V& value,
                             uint8_t* buffer )
{
    memcpy( buffer, &value, sizeof( V ) );
}

//------------------------------------------------------------------------------
//

template< class V >
EN_INLINE void getAttribute( const uint8_t* buffer,
                             V& value )
{
    memcpy( &value, buffer, sizeof( V ) );
}

//------------------------------------------------------------------------------
//

template< class T >
EN_INLINE AttributeContainer< T >::AttributeContainer()
{
    memset( m_buffer, 0, nbytes );
}

//------------------------------------------------------------------------------
//

template< class T >
EN_INLINE AttributeContainer< T >::~AttributeContainer()
{
}

//------------------------------------------------------------------------------
//

template< class T >
    template< int A, class V >
EN_INLINE void AttributeContainer< T >::set( const V& value )
{
    setAttribute( value,
                  m_buffer + FAttributeRange< T, A >::begin );
}

//------------------------------------------------------------------------------
//

template< class T >
    template< int A, class V >
EN_INLINE void AttributeContainer< T >::get( V& value ) const
{
    getAttribute( m_buffer + FAttributeRange< T, A >::begin,
                  value );
}

} // engine

#endif // ATTRIBUTE_IPP
