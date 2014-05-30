#ifndef CCOMMANDPARSER_H
#define CCOMMANDPARSER_H

#include "Command.h"
#include "ItemParser.h"
#include <vector>
#include <Boardkey.h>

class CCommandParser : public CItemParser
{

private:

    CCommand m_Cmd; //включение объекта CCommand
    int m_MaxPosX; // максимально допустимая координата X
    int m_MaxPosY; // максимально допустимая координата Y
    bool m_Error; // флаг ошибки
    std::string m_ErrorString; // текстовое собщение об ошибке
    bool m_FullPacket; // признак того, что в пакете были все необходимые поля
    std::vector<bool> m_nameWasInPacket; // флаги наличия поля в пакете
    int m_NamesLeft; // количество полей, которые пока ещё не найдены в пакете.

public:

    CCommandParser(); //(int maxPosX = 5, int maxPosY = 5);

    virtual  void OnItemParsed(const std::string &item);

    virtual bool IsError() const; // в C++ появился логический тип bool со значениями true и false

    const CCommand &GetCommand() const; //метод - акссесор ко включенному объекту CCommand

    const std::string &GetErrorMessage() const;

    virtual void OnBlockCompleted();

};

#endif // CCOMMANDPARSER_H
