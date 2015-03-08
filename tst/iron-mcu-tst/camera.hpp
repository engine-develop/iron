//------------------------------------------------------------------------------
//

#include <iron.hpp>

//------------------------------------------------------------------------------
//

namespace engine
{

//------------------------------------------------------------------------------
// Define node
//

EN_DEFINE_NODE(
    ( Camera, "Example camera node", "sensor" ),
    (( Input,    shutter, digital_t, Low,     2    ))
    (( Input,    zoom,    analog_t,  512,     A0   ))
    (( Internal, model,   uint32_t,  2389221, None ))
    (( Internal, flash,   bool,      true,    None ))
    (( Output,   led,     digital_t, Low,     13   ))
)

//------------------------------------------------------------------------------
// Define node class
//

EN_NODE_CLASS( Camera )
{
    void setup()
    {
    }

    void loop()
    {
    }
};

} // engine
