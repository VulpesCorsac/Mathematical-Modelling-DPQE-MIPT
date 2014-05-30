#include "CommandParser.h"
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
    {"Command_Move", "Нет команды перемещения\n", "Нет значения команды перемещения (Command_Move)\n"},
    {"Number_Of_Messages", "Нет команды кол-ва сообщений", "Нет значения команды кол-ва соощений(Number_Of_Messages)\n"}
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


CCommandParser::CCommandParser() //(int maxPosX, int maxPosY)
:   m_Error(false) //инициализация поля m_Error значением false при вызове конструктора
,   m_nameWasInPacket(numberOfFields, false)
,   m_NamesLeft(numberOfFields)
{
}
static BoardKey FindMessage(const std::string &MessageName)
{

    BoardKey bk = StringToBoardKey(MessageName.c_str());
    if(bk < 0 || bk >= BkCount)
    {
        return BkUnknown;
    }
    else
    {
        return bk;
    }
}

void CCommandParser::OnItemParsed(const std::string &item)
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
        if (FindMessage(argname) != BkUnknown)
        {
            // разбиваем на vector
            size_t foundLast = 0;
            size_t foundNext = 0;

            while(1)
            {
                foundNext = argval.find(' ', foundLast +1 );

                if (foundNext == std::string::npos)
                {
                    break;
                }

                m_Cmd.SetMessage(atoi(argval.substr(foundLast, foundNext).c_str()), FindMessage(argname));

                foundLast = foundNext;


            }

        }
        else
        {
            m_Error = true;
            m_ErrorString = "\nНеизвестная команда: " + argname + "\n";

        }
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
            //заполняем поля класса CCommand
            if(argname == "Number_Of_Messages")
            {                
                m_Cmd.SetNumberOfMessages(atoi(argval.c_str()));
            }
            else if(argname == "Command_Move")
            {
                MoveDirection md = StringToMoveDirection(argval.c_str());
                if(md < 0 || md >= MdCount)
                {
                    m_Error = true;
                    m_ErrorString = "Неизвестная команда перемещения: \"" + argval + "\"\n";
                }
                else
                {
                    m_Cmd.SetCommandMove(md);
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


void CCommandParser::OnBlockCompleted() // проверка полности данных пакета команд
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

//    if(!m_Error)
//    {
//        if (m_Cmd.GetAntStartX() > m_MaxPosX)
//        {
//            m_ErrorString = "Координата X вышла за пределы\n";
//            m_Error = true;
//        }

//        if (m_Cmd.GetAntStartY() > m_MaxPosY)
//        {
//            m_ErrorString = "Координата  Y вышла за пределы\n";
//            m_Error = true;
//        }
//    }

    if(!m_Error)
    {
        m_ErrorString = "Ошибок нет!";
    }
}

bool CCommandParser::IsError() const
{
    return m_Error;
}

const CCommand &CCommandParser::GetCommand() const
{
    return m_Cmd;
}

const std::string &CCommandParser::GetErrorMessage() const
{
    return m_ErrorString;
}



