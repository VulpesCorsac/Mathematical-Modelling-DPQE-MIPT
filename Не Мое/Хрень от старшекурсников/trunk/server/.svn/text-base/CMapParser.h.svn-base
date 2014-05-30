#ifndef CMAPPARSER_H
#define CMAPPARSER_H

#include "ItemParser.h"
#include "Map.h"


class CMapParser : public CItemParser
{

private:
    CMap m_Map;
    int PosY;
    std::string m_ErrorMessage;
    size_t m_MapSizeX;
    size_t m_MapSizeY;
    bool m_Error;
    bool m_WasX;
    bool m_WasY;


public:

    CMapParser();

    virtual  void OnItemParsed(const std::string &item);

    virtual bool IsError() const; // в C++ появился логический тип bool со значениями true и false

    const CMap &GetMapInMapParsr() const; //метод - акссесор ко включенному объекту CCommand

    const std::string &GetErrorMessage() const;

    virtual void OnBlockCompleted();

};

#endif // CMAPPARSER_H
