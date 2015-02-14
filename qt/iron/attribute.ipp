#ifndef ATTRIBUTE_IPP
#define ATTRIBUTE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< class T >
EN_INLINE void setAttribute( const T& value,
                             uint8_t* buffer )
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

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE AttributeContainer< D >::AttributeContainer()
{
    memset( m_buffer, 0, nbytes );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
EN_INLINE AttributeContainer< D >::~AttributeContainer()
{
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
    template< int A, class T >
EN_INLINE void AttributeContainer< D >::set( const T& value )
{
    setAttribute( value,
                  m_buffer + FAttributeRange< D, A >::begin );
}

//------------------------------------------------------------------------------
//

template< template< int > class D >
    template< int A, class T >
EN_INLINE void AttributeContainer< D >::get( T& value ) const
{
    getAttribute( m_buffer + FAttributeRange< D, A >::begin,
                  value );
}

} // engine

#endif // ATTRIBUTE_IPP
