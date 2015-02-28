//------------------------------------------------------------------------------
//

#include <iron.hpp>

//------------------------------------------------------------------------------
//

namespace engine
{

// Define node
//
EN_DEFINE_NODE(
    ( Camera, "Example camera node", 0xB0, 0x7B, 0xA6, 0x43 ),
    (( Input,    shutter, digital_t, Low,     2    ))
    (( Input,    zoom,    analog_t,  512,     A0   ))
    (( Internal, model,   uint32_t,  2389221, None ))
    (( Internal, flash,   bool,      true,    None ))
    (( Output,   led,     digital_t, Low,     13   )),
    (
    ),
    (
        // Return if device is not selected
        //
        if ( !( this->state() & Selected ) ) { return; }
    )
)

} // engine
