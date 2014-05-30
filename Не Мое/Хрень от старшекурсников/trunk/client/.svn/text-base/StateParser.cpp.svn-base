#include "StateParser.h"
#include "stdlib.h"
#include <iostream>

struct FieldName
{
    std::string name;
    std::string fieldError;
    std::string valueError;
};


const FieldName fields[] = {
    {"Ant_Pos_X",  "Нет координаты Х муравья\n", "Нет значения координаты Х муравья (Ant_Pos_X)\n"},
    {"Ant_Pos_Y",  "Нет координаты Y муравья\n", "Нет значения координаты Y муравья (Ant_Pos_Y)\n"},
    {"Ant_Status",  "Нет состояния муравья\n", "Нет значения состояния муравья (Ant_Status)\n"},
    {"Map_Size",  "Не указан размер карты\n", "Нет значения размера карты (Map_Size)\n"},
    {"View_Radius",  "Не указан радиус обзора муравья\n", "Нет значения радиуса обзора муравья (View_Size)\n"},
    {"View_Cells",  "Не указаны символы, которые видит муравей\n", "Нет значений символов, которые видит муравей (View_Cells)\n"},
    {"View_Dyn_Cells",  "Не указаны динамические символы, которые видит муравей\n", "Нет значений динамических символов, которые видит муравей (View_Dyn_Cells)\n"},
    {"Number_Of_Messages", "Нет команды кол-ва сообщений", "Нет значения команды кол-ва соощений(Number_Of_Messages)\n"},
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

CStateParser::CStateParser()
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

void CStateParser::OnItemParsed(const std::string &item)
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

                m_State.SetMessage(atoi(argval.substr(foundLast, foundNext).c_str()), FindMessage(argname));

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
            //заполняем поля класса CState
            if(argname == "Ant_Pos_X")
            {
                m_State.SetPosX(atoi(argval.c_str()));
            }
            else if(argname == "Ant_Pos_Y")
            {
                m_State.SetPosY(atoi(argval.c_str()));
            }
            else if(argname == "Ant_Status")
            {
                m_State.SetAntStatus((AntStatus)atoi(argval.c_str()));
            }
            else if(argname == "Map_Size")
            {
                m_State.SetMapSize(atoi(argval.c_str()));
            }
            else if(argname == "View_Radius")
            {
                m_State.SetViewRadius(atoi(argval.c_str()));
            }
            else if(argname == "View_Cells")
            {
                 m_State.SetVisibleMap(argval);
            }
            else if(argname == "View_Dyn_Cells")
            {
                 m_State.SetVisibleDynMap(argval);
            }
            else if(argname == "Number_Of_Messages")
            {
                m_State.SetNumberOfMessages(atoi(argval.c_str()));
            }
            else
            {
                m_Error = true;
                m_ErrorString = "\nОшибка разбора поля: " + argname + " со значением: " + argval + "\n";
            }
        }
    }
}


void CStateParser::OnBlockCompleted() // проверка полности данных пакета команд
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

    if(m_State.GetViewSize() != m_State.GetVisibleMap().size())
    {
        m_Error = true;
        m_ErrorString = "\n Неверное количество символов обзора! \n";
    }

    if(!m_Error)
    {
        m_ErrorString = "Ошибок нет!";
    }
}

bool CStateParser::IsError() const
{
    return m_Error;
}

const CState &CStateParser::GetState() const
{
    return m_State;
}

const std::string &CStateParser::GetErrorMessage() const
{
    return m_ErrorString;
}




