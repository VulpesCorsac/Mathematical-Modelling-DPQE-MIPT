#include "CMapParser.h"
#include <string>
#include <iostream>
#include "stdlib.h"

const std::string mapRowName = "Map_Row_";

CMapParser::CMapParser():
    PosY(0)
  , m_Error(false)
  , m_WasX(true)
  , m_WasY(true)
{
}

void CMapParser::OnItemParsed(const std::string &item)
{
    int y;
    std::string argname;
    std::string argval; //разбираем строку на пару: "имя"-"значение" с помощью стандартных методов класса string
    std::string::size_type delimiterPos = item.find(' ');
    //добавил проверку пробела т.к иначе пакет c "Last_Name" был бы полноценным и у него были некотрые данные взятые
    //с потолка или с предведущего чтения пакетов

    if (m_Error)
    {
        return;
    }

    if (delimiterPos != (std::string::npos))
    {
        argname = item.substr(0,delimiterPos);
        argval = item.substr(delimiterPos+1);

    }
    else
    {
        argname = item;
    }

    size_t found = argname.find(mapRowName, 0) ;

    if  (argname == "Map_Size")
    {
        m_MapSizeX = atoi(argval.c_str());
        m_Map.SetMapSizeX(m_MapSizeX);
        m_WasX = false;
        m_WasY = false;
        m_Map.SetMapSizeY(m_MapSizeX);
     }

    else if  ((argname == "Map_Size_X")&&(!m_WasX))
    {
        m_MapSizeX = atoi(argval.c_str());
        m_Map.SetMapSizeX(m_MapSizeX);
        m_WasX = false;

        if (m_WasY)
        {
            m_Map.SetMapSizeY(m_MapSizeX);
        }
        //std::cout << " Размер карты по X = " << m_MapSizeX << std::endl;
    }

    else if  ((argname == "Map_Size_Y")&&(!m_WasY))
    {
        m_MapSizeY = atoi(argval.c_str());
        m_Map.SetMapSizeY(m_MapSizeY);
        m_WasY = false;

        if (m_WasX)
        {
            m_Map.SetMapSizeX(m_MapSizeY);
        }

        //std::cout << " Размер карты по Y = " << m_MapSizeY << std::endl;
    }


    else if(found != std::string::npos)
    {
        if ((m_WasX && m_WasY))
        {
            m_Error = true;
            m_ErrorMessage += "Нет Размера Карты";
            return;
        }

        y = atoi(item.substr((found + mapRowName.size()),delimiterPos - (found + mapRowName.size())).c_str());

        if (argval.size() != m_MapSizeX)
        {
            m_Error = true;
            m_ErrorMessage += "No elements ";
            return;
        }

        for (size_t x = 0; x < m_MapSizeX; x++)
        {

            if ((y == 0) || (y == m_Map.GetMapSizeY() - 1))
            {
                if (argval.at(x) != '#')
                {
                    m_Error = true;
                    m_ErrorMessage += "No Wall";
                    return;
                }
            }
            if ((x == 0) || (x == m_MapSizeX - 1))
            {
                if (argval.at(x) != '#')
                {
                    m_Error = true;
                    m_ErrorMessage += "No Wall";
                    return;
                }
            }

            switch(argval.at(x))
            {
            case McGround:
            case McWater:
            case McWall:
            case McHill:
            case McFood:
            case McStick:
                {
                    m_Map.Cell(x,y) = (MapCell) argval.at(x);
                    break;
                }
            case McError:
            case McUnknown:
            default:
                {
                    m_Error = true;
                    m_ErrorMessage = "Can't read: " + argname;
                }
            }
            // std::cout << (char)argval.at(x);
        }
        // std::cout << std::endl;

        if (y != PosY)
        {
            m_Error = true;
            m_ErrorMessage += "Ошибка в построении карты\n";
            return;
        }
        PosY ++;
    }
}

void CMapParser::OnBlockCompleted()
{

}

bool CMapParser::IsError() const
{
    return m_Error;
}

const CMap &CMapParser::GetMapInMapParsr() const
{
    return m_Map;
}
const std::string &CMapParser::GetErrorMessage() const
{
    return m_ErrorMessage;
}


