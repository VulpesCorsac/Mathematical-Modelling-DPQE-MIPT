#ifndef __ANT_TYPE_H_INCLUDED__
#define __ANT_TYPE_H_INCLUDED__

enum AntType
{
    AtUnknown = -1
,   AtQueen = 0     // 0 - королева
,   AtWorker        // 1 - рабочий
,   AtScout         // 2 - разведчик
,   AtTracker       // 3 - следопыт
,   AtSapper        // 4 - сапер
,   AtDoctor        // 5 - врач
,   AtTutor         // 6 - воспитатель
,   AtFarmer        // 7 - фермер
,   AtHunter        // 8 - охотник
,   AtManager       // 9 - завхоз
,   AtCowboy        // 10 - пастух
,   AtCow           // 11 - коровка
,   AtLion          // 12 - муравьиный лев

,   AtCount
};

AntType StringToAntType(const char *s);

const char *AntTypeToString(AntType at);

char AntTypeToChar(AntType at);

AntType CharToAntType(const char c);

#endif // __ANT_TYPE_H_INCLUDED__
