#ifndef CPACKETPARSER_H
#define CPACKETPARSER_H

#include <string>

class CItemParser; // Объявление класса CCommandParser. Определение этого класса не нужно для компиляции этого хедера.

class CPacketParser
{

private:
    CItemParser *m_ItemParser; // здесь хранится указатель на объект парсера команд, которому нужно отдавать
    std::string m_ErrorMessage;
    std::string m_Item; // объект класса string. Сюда накапливается строка ("Имя Значение") из входного пакета
    int m_MaxSize;
    int m_PacketSize;
    bool m_Error;

public:

    // читает побайтно данные из входного потока, разбивает на строки и передает их в обработчик пакета
    // в случае конца пакета возвращает FALSE
    bool AddByte(char b);
    CPacketParser(CItemParser *m, int MaxSize = 1000);

    const std::string &GetErrorMessage() const;
    bool IsError() const;
};

#endif // CPACKETPARSER_H
