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
    ( Constrain, "Constrains a number to be within a range", "Utility" ),
    (( x,      Input,  Int, 0, None ))
    (( a,      Input,  Int, 0, None ))
    (( b,      Input,  Int, 0, None ))
    (( result, Output, Int, 0, None ))
)

//------------------------------------------------------------------------------
// Define node class
//

IRON_NODE_CLASS( Constrain )
{
    void evaluate()
    {
        set< 3 >( constrain( get< 0 >(),
                             get< 1 >(),
                             get< 2 >() ) );
    }
};

} // engine
