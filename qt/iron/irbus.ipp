#ifndef IRBUS_IPP
#define IRBUS_IPP

namespace engine
{
#if 0
//------------------------------------------------------------------------------
//

EN_INLINE BusHeader::BusHeader()
{
    reset();
}

//------------------------------------------------------------------------------
//

EN_INLINE BusHeader::~BusHeader()
{
}

//------------------------------------------------------------------------------
//

EN_INLINE unsigned char* BusHeader::data()
{
    return m_data;
}

//------------------------------------------------------------------------------
//

EN_INLINE void BusHeader::reset()
{
    //memset( m_data, 0, sizeof( m_data ) );

    m_data[ IRBus_I_ID ]      = IRBus_ID_MagicNumber;
    m_data[ IRBus_I_Config ]  = IRBus_Config_Version_1;
    m_data[ IRBus_I_Device ]  = 0;
    m_data[ IRBus_I_Channel ] = IRBus_Channel_Type_RGB
        | ( IRBus_Channel_Stride_RGB << IRBus_Channel_Stride_Shift );
    m_data[ IRBus_I_ClrSep ]  = IRBus_ColorSeparation_Type_Bayer;
    m_data[ IRBus_I_Stereo ]  = IRBus_Stereo_Enable_Off
        | ( IRBus_Stereo_Layout_Interleaved << IRBus_Stereo_Layout_Shift );
    m_data[ IRBus_I_ResXL ]   = 0;
    m_data[ IRBus_I_ResXH ]   = 0;
    m_data[ IRBus_I_ResYL ]   = 0;
    m_data[ IRBus_I_ResYH ]   = 0;
}

//------------------------------------------------------------------------------
//

EN_INLINE bool BusHeader::set( char* header )
{
    //memcpy( m_data, header, sizeof( m_data ) );

    return ( uint8_t( m_data[ IRBus_I_ID ] ) == IRBus_ID_MagicNumber );
}

//------------------------------------------------------------------------------
//

EN_INLINE bool BusHeader::set( char* begin,
                                 char* end )
{
    while ( begin != end )
    {
        if ( uint8_t( *begin ) == IRBus_ID_MagicNumber )
        {
            return set( begin );
        }

        ++begin;
    }

    return false;
}

//------------------------------------------------------------------------------
//

EN_INLINE void BusHeader::setResolution( const uint16_t& rx,
                                           const uint16_t& ry )
{
    m_data[ IRBus_I_ResXL ] = byteLow( rx );
    m_data[ IRBus_I_ResXH ] = byteHigh( rx );
    m_data[ IRBus_I_ResYL ] = byteLow( ry );
    m_data[ IRBus_I_ResYH ] = byteHigh( ry );
}

//------------------------------------------------------------------------------
//

EN_INLINE uint16_t BusHeader::resolutionX()
{
    return uint16_t( bytesJoin( m_data[ IRBus_I_ResXH ],
                                m_data[ IRBus_I_ResXL ] ) );
}

//------------------------------------------------------------------------------
//

EN_INLINE uint16_t BusHeader::resolutionY()
{
    return uint16_t( bytesJoin( m_data[ IRBus_I_ResYH ],
                                m_data[ IRBus_I_ResYL ] ) );
}
#endif
} // engine

#endif // IRBUS_IPP
