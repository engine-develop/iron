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

IRON_DEFINE_NODE(
    ( Map, "Re-maps a number from one range to another", "Utility" ),
    (( value,    Input,  Int, 0, None ))
    (( fromLow,  Input,  Int, 0, None ))
    (( fromHigh, Input,  Int, 0, None ))
    (( toLow,    Input,  Int, 0, None ))
    (( toHigh,   Input,  Int, 0, None ))
    (( result,   Output, Int, 0, None ))
)

//------------------------------------------------------------------------------
// Define node class
//

IRON_NODE_CLASS( Map )
{
    void evaluate()
    {
        set< 5 >( map( get< 0 >(),
                       get< 1 >(),
                       get< 2 >(),
                       get< 3 >(),
                       get< 4 >() ) );
    }
};

} // engine
