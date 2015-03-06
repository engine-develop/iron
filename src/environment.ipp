#ifndef IR_ENVIRONMENT_IPP
#define IR_ENVIRONMENT_IPP

namespace engine
{

//------------------------------------------------------------------------------
//

EN_INLINE Environment::Environment()
    : m_installDirectory()
    , m_userDirectory()
    , m_pathDirectories()
{
}

//------------------------------------------------------------------------------
//

EN_INLINE Environment::~Environment()
{
    release();
}

//------------------------------------------------------------------------------
//

EN_INLINE Environment& Environment::get()
{
    static Environment obj;

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

EN_INLINE void Environment::reload()
{
    release();
    init();
}

//------------------------------------------------------------------------------
//

EN_INLINE void Environment::release()
{
    m_installDirectory.clear();
    m_userDirectory.clear();
    m_pathDirectories.clear();
}

//------------------------------------------------------------------------------
//

EN_INLINE void Environment::init()
{
    // Get install directory
    //
    m_installDirectory = getAppsDirectory();
    m_installDirectory.append( "/" );
    m_installDirectory.append( "iron" );

    // Get/create user directory
    //
    m_userDirectory = getHomeDirectory();
    m_userDirectory.append( "/" );
    m_userDirectory.append( "iron" );

    createDirectories( m_userDirectory );

    // Add install directory to paths
    //
    m_pathDirectories.push_back( m_installDirectory );

    // Add user directory to paths
    //
    m_pathDirectories.push_back( m_userDirectory );

    // Add current directory to paths
    //
    m_pathDirectories.push_back( getCurrentDirectory() );

    // Add env var to paths
    //
    const char* envpath = getenv( "IRON_PATH" );

    if ( envpath )
    {
        std::string envpath_s( envpath );

        std::vector< std::string > envpathdirs;
        split( envpath_s, envpathdirs, ';' );

        m_pathDirectories.insert( m_pathDirectories.end(),
                                  envpathdirs.begin(),
                                  envpathdirs.end() );
    }
}

//------------------------------------------------------------------------------
//

EN_INLINE const std::string& Environment::userDirectory()
{
    return m_userDirectory;
}

//------------------------------------------------------------------------------
//

EN_INLINE const std::vector< std::string >& Environment::pathDirectories()
{
    return m_pathDirectories;
}

} // engine

#endif // IR_ENVIRONMENT_IPP
