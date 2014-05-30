#include "FirstCommandParser.h"
#include "AntType.h"
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <string>

struct FieldName
{
    std::string name;
    std::string fieldError;
    std::string valueError;
};


const FieldName fields[] = {
    {"Ant_Name",  "Нет имени муравья\n", "Нет значения имени муравья (Ant_Name)\n"},
    {"Ant_Type", "Нет профессии муравья\n", "Нет значения профессии муравья (Ant_Type)\n"},
};

const int numberOfFields = sizeof(fields) / sizeof(fields[0]);

const int fieldNotFound = -1;

static int FindField(const std::string &fieldName)
{
    for(int fieldNumber = 0; fieldNumber < numberOfFields; fieldNumber++)
    {
        if (fields[fieldNumber].name == fieldName)
        {
            return fieldNumber;
        }
    }

    return fieldNotFound;
}


CFirstCommandParser::CFirstCommandParser() //(int maxPosX, int maxPosY)
:   m_Error(false) //инициализация поля m_Error значением false при вызове конструктора
,   m_nameWasInPacket(numberOfFields, false)
,   m_NamesLeft(numberOfFields)
{
}

void CFirstCommandParser::OnItemParsed(const std::string &item)
{

    std::string argname;
    std::string argval; //разбираем строку на пару: "имя"-"значение" с помощью стандартных методов класса string
    std::string::size_type delimiterPos = item.find(' ');
    //добавил проверку пробела т.к иначе пакет c "Last_Name" был бы полноценным и у него были некотрые данные взятые
    //с потолка или с предведущего чтения пакетов

    if (delimiterPos != (std::string::npos))
    {
        argname = item.substr(0,delimiterPos);
        argval = item.substr(delimiterPos+1);
    }
    else
    {
        argname = item;
    }

    int index = FindField(argname);

    if (index == fieldNotFound)
    {
        m_Error = true;
        m_ErrorString = "\nНеизвестная команда: " + argname + "\n";
    }
    else if (m_nameWasInPacket[index])
    {
        m_Error = true;
        m_ErrorString = "\nКоманда " + argname + " встретилась повторно\n";
    }
    else
    {
        m_nameWasInPacket[index] = true;
        --m_NamesLeft;

        if (argval.empty())
        {
            m_ErrorString += fields[index].valueError;
            m_Error = true;
        }
        else
        {
            // заполняем поля класса CFirstCommand
            if(argname == "Ant_Name")
            {
                m_Cmd.SetName(argval);
            }
            else if(argname == "Ant_Type")
            {
                AntType at = StringToAntType(argval.c_str());
                if(at < 0 || at >= AtCount)
                {
                    m_Error = true;
                    m_ErrorString = "Неизвестная профессия муравья: " + argval + "\n";
                }
                else
                {
                    m_Cmd.SetType(at);
                }
            }

            else
            {
                m_Error = true;
                m_ErrorString = "\nОшибка разбора поля: " + argname + " со значением: " + argval + "\n";
            }
        }
    }
}


void CFirstCommandParser::OnBlockCompleted() // проверка полности данных пакета команд
{

    if(m_NamesLeft > 0)
    {
        for(int fieldNumber = 0; fieldNumber < numberOfFields; fieldNumber++)
        {
            if (!m_nameWasInPacket[fieldNumber])
            {
                m_ErrorString += fields[fieldNumber].fieldError;
            }
        }

        m_Error = true;
    }


    if(!m_Error)
    {
        m_ErrorString = "Ошибок нет!";
    }
}

bool CFirstCommandParser::IsError() const
{
    return m_Error;
}

const CFirstCommand &CFirstCommandParser::GetCommand() const
{
    return m_Cmd;
}

const std::string &CFirstCommandParser::GetErrorMessage() const
{
    return m_ErrorString;
}



