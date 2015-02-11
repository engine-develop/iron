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

enum Bus_I
{
    Bus_I_ID      = 0,
    Bus_I_Config  = 1,
    Bus_I_Device  = 2,
    Bus_I_Channel = 3,
    Bus_I_ClrSep  = 4,
    Bus_I_Stereo  = 5,
    Bus_I_ResXL   = 6,
    Bus_I_ResXH   = 7,
    Bus_I_ResYL   = 8,
    Bus_I_ResYH   = 9
};

//------------------------------------------------------------------------------
//

enum Bus_Config
{
    Bus_Config_Version_Mask = 0xF,
    Bus_Config_Version_1    = 1
};

//------------------------------------------------------------------------------
//

enum Bus_Channel
{
    Bus_Channel_Type_Mask     = 0xF,
    Bus_Channel_Type_RGB      = 0x0,
    Bus_Channel_Type_Scalar   = 0x1,

    Bus_Channel_Stride_Mask   = 0xF0,
    Bus_Channel_Stride_Shift  = 4,
    Bus_Channel_Stride_RGB    = 3,
    Bus_Channel_Stride_Scalar = 1
};

//------------------------------------------------------------------------------
//

enum Bus_ColorSeparation
{
    Bus_ColorSeparation_Type_Mask  = 0xF,
    Bus_ColorSeparation_Type_Bayer = 0x0
};

//------------------------------------------------------------------------------
//

enum Bus_Stereo
{
    Bus_Stereo_Enable_Mask = 0x1,
    Bus_Stereo_Enable_Off  = 0x0,
    Bus_Stereo_Enable_On   = 0x1,

    Bus_Stereo_Layout_Mask        = 0xE,
    Bus_Stereo_Layout_Shift       = 1,
    Bus_Stereo_Layout_Interleaved = 0x0,
    Bus_Stereo_Layout_Serial      = 0x1
};

//------------------------------------------------------------------------------
//

EN_DEFINE_BUS_PROTOCOL( IR, 16, 0xB0, 0x7B, 0xA6 )

} // engine

#endif // IRBUS_HPP
