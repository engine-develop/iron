#ifndef SYNC_IPP
#define SYNC_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< template< int A > class D >
EN_INLINE Status sync( const D& src )
{
    return Success;
}

} // engine

#endif // SYNC_IPP
