#include "LogParser.h"
#include "stdlib.h"
#include <iostream>

struct FieldName
{
    std::string name;
    std::string fieldError;
    std::string valueError;
};


const FieldName fields[] = {
    {"Game_Step",  "Нет номера шага игры\n", "Нет значения номера шага игры (Game_Step)\n"},
    {"Map_Size",  "Не указан размер карты\n", "Нет значения размера карты (Map_Size)\n"},
    {"Food_In_Hill",  "Не указано количество еды в муравейнике\n", "Нет значения количества еды в муравейнике (Food_In_Hill)\n"},
    {"Food_In_Stock",  "Не указано количество еды на складе\n", "Нет значения количества еды на складе (Food_In_Stock)\n"},
    {"Stick_In_Hill",  "Не указано количество палочек в муравейнике\n", "Нет значения количества палочек в муравейнике (Stick_In_Hill)\n"},
    {"Children_Grownup",  "Не указано число выращенных деток\n", "Нет значения числа выращенных деток (Children_Grownup)\n"},
    {"Number_Of_Ants",  "Нет количества муравьев\n", "Нет значения количества муравьев (Number_Of_Ants)\n"},
    {"Number_Of_Messages",  "Нет числа сообщений\n", "Нет значения числа сообщений (Number_Of_Messages)\n"},
    {"Ant_Name",  "Нет имени муравья\n", "Нет значения имени муравья (Ant_Name)\n"},
    {"Ant_Type", "Нет профессии муравья\n", "Нет значения профессии муравья (Ant_Type)\n"},
    {"Ant_Pos_X",  "Нет координаты Х муравья\n", "Нет значения координаты Х муравья (Ant_Pos_X)\n"},
    {"Ant_Pos_Y",  "Нет координаты Y муравья\n", "Нет значения координаты Y муравья (Ant_Pos_Y)\n"},
    {"Ant_Status",  "Нет состояния муравья\n", "Нет значения состояния муравья (Ant_Status)\n"},
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

CLogParser::CLogParser()
:   m_Error(false) //инициализация поля m_Error значением false при вызове конструктора
,   m_nameWasInPacket(numberOfFields, false)
,   m_NamesLeft(numberOfFields)
,   m_LastAntIndex(0)
{
}

void CLogParser::OnItemParsed(const std::string &item)
{

    std::string argname;
    std::string argval; //разбираем строку на пару: "имя"-"значение" с помощью стандартных методов класса string
    std::string::size_type delimiterPos = item.find(' ');
    //добавил проверку пробела т.к иначе пакет c "Last_Name" был бы полноценным и у него были некоторые данные взятые
    //с потолка или с предведущего чтения пакетов

    if (delimiterPos != (std::string::npos))
    {
        argname = item.substr(0, delimiterPos);
        argval = item.substr(delimiterPos + 1);
    }
    else
    {
        argname = item;
    }

    int index = FindField(argname);

    if (index == fieldNotFound)
    {
        if (FindMessage(argname) != BkUnknown) // а не сообщение ли это для доски объявлений?
        {
            // разбиваем на значения
            size_t foundLast = 0;
            size_t foundNext = 0;

            while(1)
            {
                foundNext = argval.find(' ', foundLast + 1);

                int value = atoi(argval.substr(foundLast, foundNext).c_str());

                m_Frame.GetBoard().AddValue(value, FindMessage(argname));

                foundLast = foundNext;

                if (foundNext == std::string::npos)
                {
                    break;
                }
            }
        }
        else if(argname.find("Map_Row_") == 0) // может это строка с символами карты?
        {
            if (argval.size() != m_Frame.GetMapSize())
            {
                m_Error = true;
                m_ErrorString = "\nНеверное количество элементов в строке карты: " + argval + "\n";
            }
            else
            {
                CMap &map = m_Frame.GetMap();
                int nextRow = map.GetMapSizeY();
                map.SetMapSizeY(nextRow + 1);
                for(size_t x = 0; x < m_Frame.GetMapSize(); ++x)
                {
                    switch(argval.at(x))
                    {
                    case McGround:
                    case McWater:
                    case McWall:
                    case McHill:
                    case McFood:
                    case McStick:
                    case McStock:
                    case McTrap:
                        {
                            map.Cell(x, nextRow) = (MapCell) argval.at(x);
                            break;
                        }
                    case McError:
                    case McUnknown:                    
                        {
                            m_Error = true;
                            m_ErrorString = "\nНеверный символ в карте: " + argval.substr(x, 1) + "\n";
                        }
                    }
                }
            }
        }
        else
        {
            m_Error = true;
            m_ErrorString = "\nНеизвестная команда: " + argname + "\n";
        }
    }
    else if (m_nameWasInPacket[index] && (argname != "Ant_Name") && (argname != "Ant_Type") && (argname != "Ant_Pos_X") && (argname != "Ant_Pos_Y") && (argname != "Ant_Status"))
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
            //заполняем поля класса CFrame
            if(argname == "Game_Step")
            {
                m_Frame.SetGameStep(atoi(argval.c_str()));
            }
            else if(argname == "Food_In_Hill")
            {
                m_Frame.SetFoodInHill(atoi(argval.c_str()));
            }
            else if(argname == "Food_In_Stock")
            {
                m_Frame.SetFoodInStock(atoi(argval.c_str()));
            }
            else if(argname == "Stick_In_Hill")
            {
                m_Frame.SetStickInHill(atoi(argval.c_str()));
            }
            else if(argname == "Children_Grownup")
            {
                m_Frame.SetChildrenGrownup(atoi(argval.c_str()));
            }
            else if(argname == "Number_Of_Ants")
            {
                m_Frame.SetNumberOfAnts(atoi(argval.c_str()));
            }
            else if(argname == "Ant_Name")
            {
                CAnt ant;
                ant.SetAntName(argval);
                m_LastAntIndex = m_Frame.GetMap().PushAnt(ant);
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
                    m_Frame.GetMap().GetAnt(m_LastAntIndex).SetAntType(at);
                }
            }
            else if(argname == "Ant_Pos_X")
            {
                m_Frame.GetMap().GetAnt(m_LastAntIndex).SetAntPosX(atoi(argval.c_str()));
            }
            else if(argname == "Ant_Pos_Y")
            {
                m_Frame.GetMap().GetAnt(m_LastAntIndex).SetAntPosY(atoi(argval.c_str()));
            }
            else if(argname == "Ant_Status")
            {
                m_Frame.GetMap().GetAnt(m_LastAntIndex).SetAntStatus((AntStatus)atoi(argval.c_str()));
            }
            else if(argname == "Map_Size")
            {
                m_Frame.SetMapSize(atoi(argval.c_str()));
                m_Frame.GetMap().SetMapSizeX(m_Frame.GetMapSize());
                m_Frame.GetMap().SetMapSizeY(0);
            }
            else if(argname == "Number_Of_Messages")
            {
                m_Frame.SetNumberOfMessages(atoi(argval.c_str()));
            }
            else
            {
                m_Error = true;
                m_ErrorString = "\nОшибка разбора поля: " + argname + " со значением: " + argval + "\n";
            }
        }
    }
}


void CLogParser::OnBlockCompleted() // проверка полности данных пакета команд
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

    // проверка того, что все заявленные муравьи попали на карту
    if (m_Frame.GetMap().GetNumberOfAnts() != (size_t)m_Frame.GetNumberOfAnts())
    {
          m_Error = true;
          m_ErrorString += "\n Количество муравьев не соответствует заявленному! \n";
    }

    if(!m_Error)
    {
        m_ErrorString = "Ошибок нет!";
    }
}

bool CLogParser::IsError() const
{
    return m_Error;
}

const CFrame &CLogParser::GetFrame() const
{
    return m_Frame;
}

const std::string &CLogParser::GetErrorMessage() const
{
    return m_ErrorString;
}




