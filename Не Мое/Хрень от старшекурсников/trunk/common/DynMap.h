#ifndef CDYNMAP_H
#define CDYNMAP_H

#include <vector>
#include "AntType.h"


const int defaultX = 50;
const int defaultY = 50;

class CDynMap
{

private:

    std::vector< std::vector<std::vector<AntType> > > m_Cells; // трехмерный вектор содержимого карты

    AntType m_AtError;

    std::vector<AntType> m_AtVectorError;

public:

    CDynMap(); // конструктор

    // метод возвращает ссылку на содержимое ячейки карты y - строка, x - столбец
    AntType &Cell(const int x, const int y);

    const AntType &Cell(const int x, const int y) const;

    const std::vector<AntType> &Cell3D(const int x, const int y) const;

    std::vector<AntType> &Cell3D(const int x, const int y);

    // Этот метод дает уникальный номер (индекс) для каждой ячейки карты
    int GetCellIndex(const int x, const int y) const;

    int GetMapSizeX() const;

    void SetMapSizeX(const int sizeX);

    int GetMapSizeY() const;

    void SetMapSizeY(const int sizeY);  

    void Clear();

};

#endif // CDYNMAP_H
