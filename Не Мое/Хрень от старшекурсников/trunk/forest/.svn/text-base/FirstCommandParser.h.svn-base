#ifndef CFIRSTCOMMANDPARSER_H
#define CFIRSTCOMMANDPARSER_H

#include "FirstCommand.h"
#include "ItemParser.h"
#include <vector>

class CFirstCommandParser : public CItemParser
{
private:

    CFirstCommand m_Cmd; //включение объекта CFirstCommand
    bool m_Error; // флаг ошибки
    std::string m_ErrorString; // текстовое собщение об ошибке
    bool m_FullPacket; // признак того, что в пакете были все необходимые поля
    std::vector<bool> m_nameWasInPacket; // флаги наличия поля в пакете
    int m_NamesLeft; // количество полей, которые пока ещё не найдены в пакете.

public:

    CFirstCommandParser(); //(int maxPosX = 5, int maxPosY = 5);

    virtual  void OnItemParsed(const std::string &item);

    virtual bool IsError() const; // в C++ появился логический тип bool со значениями true и false

    const CFirstCommand &GetCommand() const; //метод - акссесор ко включенному объекту CCommand

    const std::string &GetErrorMessage() const;

    virtual void OnBlockCompleted();
};

#endif // CFIRSTCOMMANDPARSER_H
