#include "PacketParser.h"
#include "ItemParser.h"
#include <iostream>


CPacketParser::CPacketParser(CItemParser *m, int MaxSize)
:   m_ItemParser(m)
,   m_MaxSize(MaxSize)
,   m_PacketSize(m_MaxSize)
,   m_Error(false)
{
}

const std::string &CPacketParser::GetErrorMessage() const
{
    return m_ErrorMessage;
}

bool CPacketParser::AddByte(char b) // b - символ, пришедший из входного потока
{
    if(b == '\r')
    {
        return true;
    }

    if(b == '\n')
    {
        m_PacketSize = m_MaxSize;
        if(m_Item.empty()) // стандартная функция из класса string. Проверяет не пустая ли это строка.
        {
            m_ItemParser->OnBlockCompleted();
            return false; // конец пакета - встретились два перевода каретки подряд
        }

        //Передаем строку (точнее даем работать со своей) Обработчику пакетов
        m_ItemParser->OnItemParsed(m_Item);

        m_Item.clear(); // стандартная функция из класса string. Очищает строку
    }
    else
    {
        m_Item.push_back(b); // стандартная функция из класса string
        // добавляет очередной байт в конец строки
    }
    m_PacketSize --;

    if (m_PacketSize == 0)
    {
        m_ItemParser->OnBlockCompleted();
        m_ErrorMessage = "Превышен допустимый размер пакета\n";
        m_Error = true;
        return false;
    }

    return true;
}

bool CPacketParser::IsError() const
{
    return m_Error;
}
