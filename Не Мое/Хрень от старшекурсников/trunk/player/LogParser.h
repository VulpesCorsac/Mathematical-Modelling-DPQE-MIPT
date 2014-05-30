#ifndef CLOGPARSER_H
#define CLOGPARSER_H

#include "Frame.h"
#include "ItemParser.h"
#include <vector>

class CLogParser : public CItemParser
{
private:

    CFrame m_Frame; //включение объекта CState
    bool m_Error; // флаг ошибки
    std::string m_ErrorString; // текстовое собщение об ошибке
    bool m_FullPacket; // признак того, что в пакете были все необходимые поля
    std::vector<bool> m_nameWasInPacket; // флаги наличия поля в пакете
    int m_NamesLeft; // количество полей, которые пока ещё не найдены в пакете.
    int m_LastAntIndex;

public:

    CLogParser();


    virtual  void OnItemParsed(const std::string &item);

    virtual bool IsError() const; // в C++ появился логический тип bool со значениями true и false

    const CFrame &GetFrame() const; //метод - акссесор ко включенному объекту CState

    const std::string &GetErrorMessage() const;

    virtual void OnBlockCompleted();
};

#endif // CLOGPARSER_H
