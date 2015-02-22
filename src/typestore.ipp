#ifndef TYPESTORE_IPP
#define TYPESTORE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int A > class D >
EN_INLINE std::string DeviceType< D >::name()
{
    return traits_t::name();
}

//------------------------------------------------------------------------------
//

template< template< int A > class D >
EN_INLINE std::string DeviceType< D >::description()
{
    return traits_t::description();
}

//------------------------------------------------------------------------------
//

template< template< int A > class D >
EN_INLINE uint32_t DeviceType< D >::id()
{
    return traits_t::id;
}

//------------------------------------------------------------------------------
//

template< template< int A > class D >
EN_INLINE void* DeviceType< D >::create()
{
    return static_cast< void* >( new D< CPU >() );
}

//------------------------------------------------------------------------------
//

template< template< int A > class D >
EN_INLINE void DeviceType< D >::remove( void* obj )
{
    D< CPU >* obj_d = static_cast< D< CPU >* >( obj );
    delete obj_d;
    obj = 0x0;
}

//------------------------------------------------------------------------------
//

template< template< int A > class D >
EN_INLINE void DeviceType< D >::evaluate( void* obj )
{
    D< CPU >* obj_d = static_cast< D< CPU >* >( obj );
    obj_d.evaluate();
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE TypeStore< T >::TypeStore()
    : m_types()
{
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE TypeStore< T >::~TypeStore()
{
    release();
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE TypeStore< T >& TypeStore< T >::get()
{
    static TypeStore< T > obj;

    return obj;
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE void TypeStore< T >::release()
{
    for ( iterator_t it = m_types.begin();
            it != m_types.end(); ++it )
    {
        if ( it->second ) delete it->second;
    }

    m_types.clear();
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE Status TypeStore< T >::registerType( Type< T >* type )
{
    assert( type );

    m_types[ type->id() ] = type;

    return Success;
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE typename TypeStore< T >::iterator_t TypeStore< T >::begin()
{
    return m_types.begin();
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE typename TypeStore< T >::iterator_t TypeStore< T >::end()
{
    return m_types.end();
}

} // engine

#endif // TYPESTORE_IPP
