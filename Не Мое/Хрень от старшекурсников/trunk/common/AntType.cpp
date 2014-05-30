#include "AntType.h"
#include "string.h"

const char *g_AntTypes[AtCount] =
{
    "queen"
,   "worker"
,   "scout"
,   "tracker"
,   "sapper"
,   "doctor"
,   "tutor"
,   "farmer"
,   "hunter"
,   "manager"
,   "cowboy"
,   "cow"
,   "lion"

};

const char g_AntTypeChars[AtCount] =
{
    'Q'
,   'W'
,   'R'
,   'T'
,   'S'
,   'D'
,   'V'
,   'F'
,   'H'
,   'M'
,   'P'
,   'C'
,   'L'

};

AntType StringToAntType(const char *s)
{
    for(int i = 0; i < AtCount; ++i)
    {
        if(strcmp(s, g_AntTypes[i]) == 0)
        {
            return (AntType)i;
        }
    }

    return AtUnknown;
}

const char *AntTypeToString(AntType at)
{
    if(at < 0 || at >= AtCount)
    {
        return "unknown";
    }

    return g_AntTypes[at];
}

char AntTypeToChar(AntType at)
{
    if(at < 0 || at >= AtCount)
    {
        return '?';
    }

    return g_AntTypeChars[at];
}

AntType CharToAntType(const char c)
{
    for(int i = 0; i < AtCount; ++i)
    {
        if(c == g_AntTypeChars[i])
        {
            return (AntType)i;
        }
    }

    return AtUnknown;
}


