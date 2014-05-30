
#include "AntStatus.h"
#include "string.h"

static const char *g_AntStatus[AsCount] =
{
    "неизвестный"
,   "живой и здоровый"
,   "забанен"
,   "ПОБЕДИТЕЛЬ"
,   "проигравший"
,   "больной"
,   "мертвый"

};


const char *AntStatusToString(AntStatus as)
{
    if(as < 0 || as >= AsCount)
    {
        return "unknown";
    }

    return g_AntStatus[as];
}
