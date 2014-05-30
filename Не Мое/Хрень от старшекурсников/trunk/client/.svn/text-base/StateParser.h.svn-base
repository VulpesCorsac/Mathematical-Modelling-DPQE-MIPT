#ifndef CSTATEPARSER_H
#define CSTATEPARSER_H

#include "State.h"
#include "ItemParser.h"
#include <Boardkey.h>
#include <vector>

class CStateParser : public CItemParser
{
private:

    CState m_State; //включение объекта CState
    bool m_Error; // флаг ошибки
    std::string m_ErrorString; // текстовое собщение об ошибке
    bool m_FullPacket; // признак того, что в пакете были все необходимые поля
    std::vector<bool> m_nameWasInPacket; // флаги наличия поля в пакете
    int m_NamesLeft; // количество полей, которые пока ещё не найдены в пакете.

public:

    CStateParser();

    virtual  void OnItemParsed(const std::string &item);

    virtual bool IsError() const; // в C++ появился логический тип bool со значениями true и false

    const CState &GetState() const; //метод - акссесор ко включенному объекту CState

    const std::string &GetErrorMessage() const;

    virtual void OnBlockCompleted();
};

#endif // CSTATEPARSER_H
