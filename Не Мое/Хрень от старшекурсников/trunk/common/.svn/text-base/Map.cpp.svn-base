#include "Map.h"
#include <iostream>
#include "stdlib.h"

CMap::CMap()
// инициализация всех ячеек карты размером  sizeY(число строк) на sizeX(число столбцов) значением CtGround:
:   m_Cells(defaultSizeX, std::vector<MapCell>(defaultSizeY, McUnknown))
,   m_McError(McError)
{
}

CAnt &CMap::GetAnt(const int index)
{
    return m_Ants[index];
}

const CAnt &CMap::GetAnt(const int index) const
{
    return m_Ants[index];
}

size_t CMap::PushAnt(const CAnt &ant)
{
    m_Ants.push_back(ant);
    return (m_Ants.size() - 1);
}

size_t CMap::GetNumberOfAnts() const
{
   return m_Ants.size();
}

MapCell &CMap::Cell(const int x, const int y)
{
    if ((y >= (int)m_Cells.size()) || (x >= (int)m_Cells[y].size()) || (y < 0) || (x < 0))
    {
        return m_McError;
    }
    return m_Cells[y][x];
}

const MapCell &CMap::Cell(const int x, const int y) const
{
    if ((y >= (int)m_Cells.size()) || (x >= (int)m_Cells[y].size()) || (y < 0) || (x < 0))
    {
        return m_McError;
    }
    return m_Cells[y][x];
}

int CMap::GetCellIndex(const int x, const int y) const
{
    return y * GetMapSizeX() + x;
}

int CMap::GetMapSizeX() const
{
    return m_Cells[0].size(); // число столбцов
}

void CMap::SetMapSizeX(const int sizeX)
{
    if (sizeX < 0)
    {
        return;
    }

    for(size_t y = 0; y < m_Cells.size(); ++y)
    {
        m_Cells[y].resize(sizeX, McUnknown);
    }
}

int CMap::GetMapSizeY() const
{
    return m_Cells.size(); // число строк
}

void CMap::SetMapSizeY(const int sizeY)
{
    if(sizeY < 0)
    {
        return;
    }

    size_t oldSizeY = m_Cells.size();
    size_t newSizeY = sizeY;

    if (newSizeY > oldSizeY)
    {
        while(newSizeY > oldSizeY)
        {
            m_Cells.push_back(std::vector<MapCell>(GetMapSizeX(), McUnknown));
            --newSizeY;
        }
    }
    else
    {
        m_Cells.resize(newSizeY);
    }
}

bool CMap::TryPlaceRandResource(MapCell mc)
{
    int x = rand() % GetMapSizeX();
    int y = rand() % GetMapSizeY();

    if (m_Cells[y][x] != McGround)
    {
        return false;
    }
    else
    {
        m_Cells[y][x] = mc;
        return true;
    }
}






