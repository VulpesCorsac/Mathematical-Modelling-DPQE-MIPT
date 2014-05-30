#ifndef CMAP_H
#define CMAP_H

#include "Ant.h"
#include <vector>

enum MapCell
{
    McError = ' '     // ошибка при выходе за границы карты (пробел)
 ,  McUnknown = '?'   // неоткрытая ячейка
 ,  McWay = '*'       // проложенный путь
 ,  McGround = '.'    // суша
 ,  McWater = '~'     // вода
 ,  McWall = '#'      // стенка
 ,  McHill = '^'      // муравейник
 ,  McFood = '%'      // еда
 ,  McStick = '/'     // стройматерил
 ,  McStock = '$'     // склад
 ,  McTrap = '@'      // ловушка

};

const int defaultSizeX = 50;
const int defaultSizeY = 50;

class CMap
{

private:

    std::vector<CAnt> m_Ants; // вектор муравьев

    std::vector< std::vector<MapCell> > m_Cells; // двумерный вектор содержимого карты

    MapCell m_McError;

public:

    CMap(); // конструктор

    // Определяем два метода. Константный и неконстантный для получения ссылки на опредленного муравья:
    CAnt &GetAnt(const int index);

    const CAnt &GetAnt(const int index) const;

    // Этот метод добавляет муравья на карту
    size_t PushAnt(const CAnt &ant);

    // Этот метод позволяет узнать количество муравьев
    size_t GetNumberOfAnts() const;
//CMap::Map[y][x]
    // метод возвращает ссылку на содержимое ячейки карты y - строка, x - столбец
    MapCell &Cell(const int x, const int y);

    const MapCell &Cell(const int x, const int y) const;

    // Этот метод дает уникальный номер (индекс) для каждой ячейки карты
    int GetCellIndex(const int x, const int y) const;

    int GetMapSizeX() const;

    void SetMapSizeX(const int sizeX);

    int GetMapSizeY() const;

    void SetMapSizeY(const int sizeY);

    bool TryPlaceRandResource(MapCell mc);

};

#endif // CMAP_H
