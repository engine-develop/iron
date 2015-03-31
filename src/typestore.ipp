#ifndef IR_TYPESTORE_IPP
#define IR_TYPESTORE_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

template<>
struct TTypes< Types_Variable >
{
    static IRON_INLINE const char* label() { return "variable"; }
};

//------------------------------------------------------------------------------
//

template<>
struct TTypes< Types_Node >
{
    static IRON_INLINE const char* label() { return "node"; }
};

//------------------------------------------------------------------------------
//

template< int T >
IRON_INLINE bool operator<( const Type< T >& lhs,
                            const Type< T >& rhs )
{
    return ( lhs.name < rhs.name );
}

//------------------------------------------------------------------------------
//

IRON_INLINE Status FTypeStoreType< Types_Variable >::verifyType( type_t* type )
{
    if (    !type->name.empty()
         && !type->description.empty()
         && !type->category.empty()
         && !type->dataType.empty() )
    {
        return Success;
    }

    return Error;
}

//------------------------------------------------------------------------------
//

IRON_INLINE Status FTypeStoreType< Types_Variable >::parseTypeInfo( std::string& block,
                                                                    type_t* type )
{
    size_t p0 = block.find_first_of( "(" );
    size_t p1 = block.find_first_of( ")", p0 + 1 );
    std::string tuple = block.substr( p0, (p1-p0)+1 );

    std::vector< std::string > tokens;
    split( tuple, tokens, ',' );
    assert( tokens.size() == 4 );
    if ( tokens.size() != 4 ) return Error;

    removePunct( tokens[ 0 ] );
    removePunct( tokens[ 1 ] );
    removePunct( tokens[ 2 ] );
    removePunct( tokens[ 3 ] );

    type->name        = trim( tokens[ 0 ] );
    type->description = trim( tokens[ 2 ] );
    type->category    = trim( tokens[ 3 ] );
    type->id          = 0;
    type->dataType    = trim( tokens[ 1 ] );

    return Success;
}

//------------------------------------------------------------------------------
//

IRON_INLINE void FTypeStoreType< Types_Variable >::createTypes( std::string& file,
                                                                std::vector< type_t* >& types )
{
    std::ifstream fstr( file );
    if ( !fstr.is_open() ) { return; }

    std::string block;
    size_t nb = 0;
    size_t ne = 0;

    std::string line;

    while ( std::getline( fstr, line ) )
    {
        if ( line.find( "IRON_DEFINE_VARIABLE" ) != std::string::npos )
        {
            block += line;

            nb += std::count( line.begin(), line.end(), '(' );
            ne += std::count( line.begin(), line.end(), ')' );

            if ( nb > 0 && nb - ne == 0 )
            {
                Type< Types_Variable >* type = new Type< Types_Variable >();
                parseTypeInfo( block, type );
                types.push_back( type );

                block = "";
                nb = 0;
                ne = 0;
            }
        }
    }

    fstr.close();
}

//------------------------------------------------------------------------------
//

IRON_INLINE Status FTypeStoreType< Types_Node >::verifyType( type_t* type )
{
    if (    !type->name.empty()
         && !type->description.empty()
         && !type->category.empty() )
    {
        return Success;
    }

    return Error;
}

//------------------------------------------------------------------------------
//

IRON_INLINE Status FTypeStoreType< Types_Node >::parseTypeInfo( std::string& block,
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
    assert( tokens.size() == 3 );
    if ( tokens.size() != 3 ) return Error;

    removePunct( tokens[ 0 ] );
    removePunct( tokens[ 1 ] );
    removePunct( tokens[ 2 ] );

    type->name        = trim( tokens[ 0 ] );
    type->description = trim( tokens[ 1 ] );
    type->category    = trim( tokens[ 2 ] );
    type->id          = 0;

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
        attr.name         = trim( tokens[ 0 ] );
        attr.type         = trim( tokens[ 1 ] );
        attr.variable     = trim( tokens[ 2 ] );
        attr.defaultValue = trim( tokens[ 3 ] );
        attr.pin          = trim( tokens[ 4 ] );

        type->attributes.push_back( attr );
    }

    return Success;
}

//------------------------------------------------------------------------------
//

IRON_INLINE Status FTypeStoreType< Types_Node >::parseTypeClass( std::string& block,
                                                                 Type< Types_Node >* type )
{
    size_t p0 = block.find_first_of( "{" );
           p0 = block.find_first_of( "{", p0+1 );
    size_t p1 = block.find_first_of( "}", p0+1 );

    type->evaluateCode = block.substr( p0+1, p1-p0-1 );

    return Success;
}

//------------------------------------------------------------------------------
//

IRON_INLINE void FTypeStoreType< Types_Node >::createTypes( std::string& file,
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
        if ( line.find( "IRON_DEFINE_NODE" ) != std::string::npos )
        {
            type = new Type< Types_Node >();

            blockType = 0;
            blockBeginChar = '(';
            blockEndChar   = ')';
        }

        else if ( line.find( "IRON_NODE_CLASS" ) != std::string::npos )
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
IRON_INLINE TypeStore< T >::TypeStore()
    : m_types()
{
}

//------------------------------------------------------------------------------
//

template< int T >
IRON_INLINE TypeStore< T >::~TypeStore()
{
    clear();
}

//------------------------------------------------------------------------------
//

template< int T >
IRON_INLINE TypeStore< T >& TypeStore< T >::get()
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
IRON_INLINE void TypeStore< T >::reload()
{
    clear();
    init();
}

//------------------------------------------------------------------------------
//

template< int T >
IRON_INLINE void TypeStore< T >::clear()
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
IRON_INLINE void TypeStore< T >::init()
{
    // Register types from environment
    //
    registerTypes( Environment::get().pathDirectories() );
}

//------------------------------------------------------------------------------
//

template< int T >
IRON_INLINE Status TypeStore< T >::verifyType( Type< T >* type )
{
    return FTypeStoreType< T >::verifyType( type );
}

//------------------------------------------------------------------------------
//

template< int T >
IRON_INLINE Status TypeStore< T >::registerType( Type< T >* type )
{
    assert( type );
    if ( !type ) return Error;

    if ( !verifyType( type ) ) return Error;

    // Get key id
    //
    std::string hash_t( type->category );
    hash_t += "/";
    hash_t += type->name;
    std::hash< std::string > fhash;
    uint32_t id = fhash( hash_t );

    // Insert
    //
    if ( m_types.count( id ) )
    {
        IRON_DEBUG( "Failed to add type '%s'. Typestore already contains id.\n", type->name.c_str() );

        return Error;
    }

    type->id = id;
    m_types[ type->id ] = type;

    return Success;
}

//------------------------------------------------------------------------------
//

template< int T >
IRON_INLINE void TypeStore< T >::registerTypes( const std::string& directory )
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
IRON_INLINE void TypeStore< T >::registerTypes( const std::vector< std::string >& directories )
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
IRON_INLINE const typename TypeStore< T >::registry_t& TypeStore< T >::types() const
{
    return m_types;
}

//------------------------------------------------------------------------------
//

template< int T >
IRON_INLINE Type< T >* TypeStore< T >::type( const uint32_t& id )
{
    if ( m_types.count( id ) == 0 )
    {
        return 0x0;
    }

    return m_types[ id ];
}

//------------------------------------------------------------------------------
//

template< int T >
IRON_INLINE std::vector< std::string > TypeStore< T >::categories()
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
IRON_INLINE std::vector< Type< T >* > TypeStore< T >::typesByName( const std::string& name )
{
    std::vector< Type< T >* > types;

    for ( auto it = m_types.begin(); it != m_types.end(); ++it )
    {
        if ( it->second->name == name )
        {
            types.push_back( it->second );
        }
    }

    return types;
}

//------------------------------------------------------------------------------
//

template< int T >
IRON_INLINE std::vector< Type< T >* > TypeStore< T >::typesByCategory( const std::string& category )
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
