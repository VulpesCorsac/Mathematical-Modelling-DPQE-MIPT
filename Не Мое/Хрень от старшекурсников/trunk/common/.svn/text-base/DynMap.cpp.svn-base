#include "DynMap.h"
#include <iostream>
#include "stdlib.h"

CDynMap::CDynMap()
// инициализация всех ячеек карты размером  sizeY(число строк) на sizeX(число столбцов) значением CtGround:
:   m_Cells(defaultX, std::vector<std::vector<AntType> >(defaultY))
,   m_AtError(AtUnknown)
,   m_AtVectorError(1, AtUnknown)
{
}


AntType &CDynMap::Cell(const int x, const int y)
{
    if ((y >= (int)m_Cells.size()) || (x >= (int)m_Cells[y].size()) || (y < 0) || (x < 0))
    {
        return m_AtError;
    }

    if (m_Cells[y][x].size() == 0)
    {
        m_Cells[y][x].push_back(AtUnknown);
    }

    return m_Cells[y][x][0];
}


const AntType &CDynMap::Cell(const int x, const int y) const
{
    if ((y >= (int)m_Cells.size()) || (x >= (int)m_Cells[y].size()) || (y < 0) || (x < 0) || m_Cells[y][x].size() == 0)
    {
        return m_AtError;
    }
    return m_Cells[y][x][0];
}

const std::vector<AntType> &CDynMap::Cell3D(const int x, const int y) const
{
    if ((y >= (int)m_Cells.size()) || (x >= (int)m_Cells[y].size()) || (y < 0) || (x < 0))
    {
        return m_AtVectorError;
    }
    return m_Cells[y][x];
}

std::vector<AntType> &CDynMap::Cell3D(const int x, const int y)
{
    if ((y >= (int)m_Cells.size()) || (x >= (int)m_Cells[y].size()) || (y < 0) || (x < 0))
    {
        return m_AtVectorError;
    }
    return m_Cells[y][x];
}


int CDynMap::GetCellIndex(const int x, const int y) const
{
    return y * GetMapSizeX() + x;
}

int CDynMap::GetMapSizeX() const
{
    return m_Cells[0].size(); // число столбцов
}

void CDynMap::SetMapSizeX(const int sizeX)
{
    if (sizeX < 0)
    {
        return;
    }

    for(size_t y = 0; y < m_Cells.size(); ++y)
    {
        m_Cells[y].resize(sizeX);
    }
}

int CDynMap::GetMapSizeY() const
{
    return m_Cells.size(); // число строк
}

void CDynMap::SetMapSizeY(const int sizeY)
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
            m_Cells.push_back(std::vector<std::vector<AntType> >(GetMapSizeX()));
            --newSizeY;
        }
    }
    else
    {
        m_Cells.resize(newSizeY);
    }
}

void CDynMap::Clear()
{
    for (int y = 0; y < GetMapSizeY(); ++y)
    {
        for (int x = 0; x < GetMapSizeX(); ++x)
        {
            m_Cells[y][x].clear();
        }
    }
}








