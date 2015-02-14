#ifndef IRBUS_HPP
#define IRBUS_HPP

// Copyright (C) 2015 Engine Development
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Image Relay Bus interfaces
//
// Bus layout is 16 byte header, with pixel data following:
//      B0-15 - Header
//      BN-M  - Pixel data
//
// Header layout:
//
// B0:  ID
//          b[7-0] Magic number
// B1:  Configuration
//          b[3-0] API version
// B2:  Device
//          b[7-0] ID
// B3:  Channel
//          b[3-0] Type
//          b[7-4] Stride
// B4:  Color Separation
//          b[3-0] Type
//          b[7-4] Reserved
// B5:  Stereo
//          b[0]   Enabled
//          b[3-1] Layout
// B6:  Resolution X
//          b[7-0] Low byte
// B7:  Resolution X
//          b[7-0] High byte
// B8:  Resolution Y
//          b[7-0] Low byte
// B9:  Resolution Y
//          b[7-0] High byte
// B10: Reserved
// B10: Reserved
// B11: Reserved
// B12: Reserved
// B13: Reserved
// B14: Reserved
// B15: Reserved
//

//------------------------------------------------------------------------------
//

// Engine
#include "bus.hpp"

namespace engine
{

//------------------------------------------------------------------------------
//

enum IR_I
{
    IR_I_ID      = 0,
    IR_I_Config  = 1,
    IR_I_Device  = 2,
    IR_I_Channel = 3,
    IR_I_ClrSep  = 4,
    IR_I_Stereo  = 5,
    IR_I_ResXL   = 6,
    IR_I_ResXH   = 7,
    IR_I_ResYL   = 8,
    IR_I_ResYH   = 9
};

//------------------------------------------------------------------------------
//

enum IR_Config
{
    IR_Config_Version_Mask = 0xF,
    IR_Config_Version_1    = 1
};

//------------------------------------------------------------------------------
//

enum IR_Channel
{
    IR_Channel_Type_Mask     = 0xF,
    IR_Channel_Type_RGB      = 0x0,
    IR_Channel_Type_Scalar   = 0x1,

    IR_Channel_Stride_Mask   = 0xF0,
    IR_Channel_Stride_Shift  = 4,
    IR_Channel_Stride_RGB    = 3,
    IR_Channel_Stride_Scalar = 1
};

//------------------------------------------------------------------------------
//

enum IR_ColorSeparation
{
    IR_ColorSeparation_Type_Mask  = 0xF,
    IR_ColorSeparation_Type_Bayer = 0x0
};

//------------------------------------------------------------------------------
//

enum IR_Stereo
{
    IR_Stereo_Enable_Mask = 0x1,
    IR_Stereo_Enable_Off  = 0x0,
    IR_Stereo_Enable_On   = 0x1,

    IR_Stereo_Layout_Mask        = 0xE,
    IR_Stereo_Layout_Shift       = 1,
    IR_Stereo_Layout_Interleaved = 0x0,
    IR_Stereo_Layout_Serial      = 0x1
};

//------------------------------------------------------------------------------
//
#if 0
struct IRHeader
{
    EN_INLINE IRHeader();

    EN_INLINE ~IRHeader();

    //------

    EN_INLINE unsigned char* data();

    EN_INLINE void reset();

    EN_INLINE bool set( char* header );

    EN_INLINE bool set( char* begin,
                        char* end );

    //------

    EN_INLINE void setResolution( const uint16_t& rx,
                                  const uint16_t& ry );

    EN_INLINE uint16_t resolutionX();

    EN_INLINE uint16_t resolutionY();

    //------

    unsigned char m_data[ 16 ];
};
#endif

} // engine

//------------------------------------------------------------------------------
//

#include "irbus.ipp"

#endif // IRBUS_HPP
