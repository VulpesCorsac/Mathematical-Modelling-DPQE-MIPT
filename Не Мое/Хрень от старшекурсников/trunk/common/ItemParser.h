#ifndef CITEMPARSER_H
#define CITEMPARSER_H

#include <string>

class CItemParser
{
public:

    virtual void OnItemParsed(const std::string &item) = 0; // основной метод данного класса,
    //который разбирает входную строку символов на пару "Имя Значение"

    virtual bool IsError() const = 0; // в C++ появился логический тип bool со значениями true и false

    virtual void OnBlockCompleted() = 0;

};

#endif // CITEMPARSER_H
