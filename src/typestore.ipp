#ifndef IR_TYPESTORE_IPP
#define IR_TYPESTORE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE bool operator<( const Type< T >& lhs,
                          const Type< T >& rhs )
{
    return ( lhs.name < rhs.name );
}

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
    if ( tokens.size() != 7 ) return;

    removePunct( tokens[ 0 ] );
    removePunct( tokens[ 1 ] );
    removePunct( tokens[ 2 ] );
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
    clear();
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE TypeStore< T >& TypeStore< T >::get()
{
    static TypeStore< T > obj;

    static bool reloadDone = false;

    if ( !reloadDone )
    {
        obj.reload();
        reloadDone = true;
    }

    return obj;
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE void TypeStore< T >::reload()
{
    clear();
    init();
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE void TypeStore< T >::clear()
{
    for ( auto it = m_types.begin(); it != m_types.end(); ++it )
    {
        if ( it->second ) delete it->second;
    }

    m_types.clear();
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE void TypeStore< T >::init()
{
    // Register types from environment
    //
    registerTypes( Environment::get().pathDirectories() );
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE Status TypeStore< T >::registerType( Type< T >* type )
{
    assert( type );

    // Get key id
    //
    uint8_t id0 = strHexToDec( type->id0 );
    uint8_t id1 = strHexToDec( type->id1 );
    uint8_t id2 = strHexToDec( type->id2 );
    uint8_t id3 = strHexToDec( type->id3 );
    uint32_t pid = EN_PACK4( id0, id1, id2, id3 );

    // Insert
    //
    if ( m_types.count( pid ) )
    {
        EN_DEBUG( "Failed to add type '%s'. Typestore already contains id.\n", type->name.c_str() );

        return Error;
    }

    m_types[ pid ] = type;

    return Success;
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE void TypeStore< T >::registerTypes( const std::string& directory )
{
    std::vector< std::string > files;
    if ( !listDirectory( directory, files, true ) ) { return; }

    for ( auto it0 = files.begin(); it0 != files.end(); ++it0 )
    {
        std::vector< Type< T >* > types;
        FTypeStoreType< T >::createTypes( *it0, types );

        for ( auto it1 = types.begin(); it1 != types.end(); ++it1 )
        {
            if ( *it1 )
            {
                registerType( *it1 );
            }
        }
    }
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE void TypeStore< T >::registerTypes( const std::vector< std::string >& directories )
{
    for ( auto it = directories.begin();
            it != directories.end(); ++it )
    {
        registerTypes( *it );
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
EN_INLINE std::vector< std::string > TypeStore< T >::categories()
{
    std::vector< std::string > categories;

    for ( auto it = m_types.begin(); it != m_types.end(); ++it )
    {
        if ( std::find( categories.begin(),
                        categories.end(),
                        it->second->category ) == categories.end() )
        {
            categories.push_back( it->second->category );
        }
    }

    return categories;
}

//------------------------------------------------------------------------------
//

template< int T >
EN_INLINE std::vector< Type< T >* > TypeStore< T >::typesByCategory( const std::string& category )
{
    std::vector< Type< T >* > types;

    for ( auto it = m_types.begin(); it != m_types.end(); ++it )
    {
        if ( it->second->category == category )
        {
            types.push_back( it->second );
        }
    }

    return types;
}

} // engine

#endif // IR_TYPESTORE_IPP
