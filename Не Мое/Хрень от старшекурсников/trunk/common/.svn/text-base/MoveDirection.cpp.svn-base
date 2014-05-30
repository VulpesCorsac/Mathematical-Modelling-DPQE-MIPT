#include "MoveDirection.h"
#include "string.h"

static const char *g_MoveDirections[MdCount] =
{
    "stop"
,   "left"
,   "right"
,   "up"
,   "down"
};

MoveDirection StringToMoveDirection(const char *s)
{
    for(int i = 0; i < MdCount; ++i)
    {
        if(strcmp(s, g_MoveDirections[i]) == 0)
        {
            return (MoveDirection)i;
        }
    }
    
    return MdUnknown;
}

const char *MoveDirectionToString(MoveDirection md)
{
    if(md < 0 || md >= MdCount)
    {
        return "unknown";
    }
    
    return g_MoveDirections[md];
}
