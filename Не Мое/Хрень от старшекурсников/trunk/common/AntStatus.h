#ifndef __ANT_STATUS_H_INCLUDED__
#define __ANT_STATUS_H_INCLUDED__

enum AntStatus
{
    AsUnknown = 0
,   AsAlive
,   AsBanned
,   AsWinner
,   AsLooser
,   AsIll
,   AsDead

,   AsCount
};

const char *AntStatusToString(AntStatus as);

#endif // __ANT_STATUS_H_INCLUDED__
