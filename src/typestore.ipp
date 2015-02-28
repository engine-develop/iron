#ifndef TYPESTORE_IPP
#define TYPESTORE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

EN_INLINE void FTypeStoreType< Types_Node >::parseTypeInfo( std::string& block,
                                                            Type< Types_Node >* type )
{
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
}

//------------------------------------------------------------------------------
//

EN_INLINE void FTypeStoreType< Types_Node >::parseTypeClass( std::string& block,
                                                             Type< Types_Node >* type )
{
    type->classCode = block;
}

//------------------------------------------------------------------------------
//

EN_INLINE void FTypeStoreType< Types_Node >::createTypes( std::string& file,
                                                          std::vector< Type< Types_Node >* >& types )
{
    std::ifstream fstr( file );
    if ( !fstr.is_open() ) { return; }

    std::string block;
    int blockType = -1;
    char blockBeginChar = ' ';
    char blockEndChar   = ' ';
    size_t nb = 0;
    size_t ne = 0;

    Type< Types_Node >* type = 0x0;

    std::string line;

    while ( std::getline( fstr, line ) )
    {
        if ( line.find( "EN_DEFINE_NODE" ) != std::string::npos )
        {
            type = new Type< Types_Node >();

            blockType = 0;
            blockBeginChar = '(';
            blockEndChar   = ')';
        }

        else if ( line.find( "EN_NODE_CLASS" ) != std::string::npos )
        {
            blockType = 1;
            blockBeginChar = '{';
            blockEndChar   = '}';
        }

        if ( blockType != -1 )
        {
            block += line;

            nb += std::count( line.begin(), line.end(), blockBeginChar );
            ne += std::count( line.begin(), line.end(), blockEndChar );

            if ( nb > 0 && nb - ne == 0 )
            {
                if ( blockType == 0 )
                {
                    parseTypeInfo( block, type );
                }

                else if ( blockType == 1 )
                {
                    parseTypeClass( block, type );

                    types.push_back( type );
                }

                block = "";
                blockType = -1;
                nb = 0;
                ne = 0;
            }
        }
    }

    fstr.close();
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
EN_INLINE bool TypeStore< T >::scanDirectory( const std::string& directory )
{
    std::vector< std::string > files;
    if ( !listDirectory( directory, files, true ) ) { return false; }

    for ( auto it0 = files.begin(); it0 != files.end(); ++it0 )
    {
        std::vector< Type< T >* > types;
        FTypeStoreType< T >::createTypes( *it0, types );

        for ( auto it1 = types.begin(); it1 != types.end(); ++it1 )
        {
            if ( *it1 ) { m_types[ (*it1)->name ] = *it1; }
        }
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
