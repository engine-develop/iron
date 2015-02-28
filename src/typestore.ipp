#ifndef TYPESTORE_IPP
#define TYPESTORE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template<>
EN_INLINE std::string FTypeStore< Types_Node >::blockLabel()
{
    return "EN_DEFINE_NODE";
}

//------------------------------------------------------------------------------
//

template<>
EN_INLINE Type< Types_Node >* FTypeStore< Types_Node >::createType( std::string& block )
{
    Type< Types_Node >* type = new Type< Types_Node >();

    size_t p0 = block.find_first_of( "(" );
    size_t p1 = 0;

    //----------
    // Find info tuple
    //
    p0 = block.find_first_of( "(", p0 + 1 );
    p1 = block.find_first_of( ")", p0 + 1 );
    std::string tuple = block.substr( p0, (p1-p0)+1 );

    std::vector< std::string > tokens;
    split( tuple, tokens, ',' );
    assert( tokens.size() == 7 );

    removePunct( tokens[ 0 ] );
    removePunct( tokens[ 6 ] );

    type->name        = trim( tokens[ 0 ] );
    type->description = trim( tokens[ 1 ] );
    type->category    = trim( tokens[ 2 ] );
    type->id0         = trim( tokens[ 3 ] );
    type->id1         = trim( tokens[ 4 ] );
    type->id2         = trim( tokens[ 5 ] );
    type->id3         = trim( tokens[ 6 ] );

    //----------
    // Find attributes
    //
    while ( 1 )
    {
        p0 = block.find_first_of( "(", p1 );
        if ( p0 == std::string::npos ) { break; }
        p0 = block.find_first_of( "(", p0+1 );
        p1 = block.find_first_of( ")", p0 );
        tuple = block.substr( p0, (p1-p0)+1 );

        tokens.clear();
        split( tuple, tokens, ',' );
        assert( tokens.size() == 5 );

        removePunct( tokens[ 0 ] );
        removePunct( tokens[ 4 ] );

        NodeTypeAttribute attr;
        attr.type         = trim( tokens[ 0 ] );
        attr.name         = trim( tokens[ 1 ] );
        attr.dataType     = trim( tokens[ 2 ] );
        attr.defaultValue = trim( tokens[ 3 ] );
        attr.pin          = trim( tokens[ 4 ] );

        type->attributes.push_back( attr );
    }

    return type;
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
EN_INLINE bool TypeStore< T >::scanFile( const std::string& file )
{
    std::ifstream fstr( file );
    if ( !fstr.is_open() ) { return false; }

    bool open = false;
    size_t nbo = 0;
    std::string block;

    std::string line;

    while ( std::getline( fstr, line ) )
    {
        if ( line.find( FTypeStore< T >::blockLabel() ) != std::string::npos )
        {
            open = true;
        }

        if ( open )
        {
            block += line;

            nbo += ( std::count( line.begin(), line.end(), '(' )
                   - std::count( line.begin(), line.end(), ')' ) );

            if ( nbo == 0 )
            {
                Type< T >* type = FTypeStore< T >::createType( block );

                if ( type ) { m_types[ type->name ] = type; }

                block = "";
                open = false;
            }
        }
    }

    fstr.close();

    return true;
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE bool TypeStore< T >::scanDirectory( const std::string& directory )
{
    std::vector< std::string > files;
    if ( !listDirectory( directory, files, true ) ) { return false; }

    for ( auto it = files.begin(); it != files.end(); ++it )
    {
        scanFile( *it );
    }

    return true;
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE void TypeStore< T >::init( const std::vector< std::string >& directories )
{
    release();

    for ( auto it = directories.begin();
            it != directories.end(); ++it )
    {
        scanDirectory( *it );
    }
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE const typename TypeStore< T >::registry_t& TypeStore< T >::types() const
{
    return m_types;
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE typename TypeStore< T >::iterator_t TypeStore< T >::typesBegin()
{
    return m_types.begin();
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE typename TypeStore< T >::iterator_t TypeStore< T >::typesEnd()
{
    return m_types.end();
}

} // engine

#endif // TYPESTORE_IPP
