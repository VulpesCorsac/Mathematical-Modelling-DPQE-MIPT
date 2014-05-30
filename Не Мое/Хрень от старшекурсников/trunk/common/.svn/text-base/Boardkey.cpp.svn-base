#include "Boardkey.h"
#include "string.h"

static const char *g_BoardKey[BkCount] =
{
    "Lion"
,   "Food"
,   "Stick"
,   "Trap"
,   "Ill"
,   "Queen_Command"
,   "Lion_Trace"

};

BoardKey  StringToBoardKey(const char *s)
{
    for(int i = 0; i < BkCount; ++i)
    {
        if(strcmp(s, g_BoardKey[i]) == 0)
        {
            return (BoardKey)i;
        }
    }

    return BkUnknown;
}

const char *BoardKeyToString(BoardKey bk)
{
    if(bk < 0 || bk >= BkCount)
    {
        return "Unknown";
    }

    return g_BoardKey[bk];
}

