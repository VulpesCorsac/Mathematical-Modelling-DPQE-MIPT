#include "GeneratorLoop.h"
#include "MoveDirection.h"
#include "Map.h"
#include <QtCore>
#include <iostream>
#include <fstream>

CGeneratorLoop::CGeneratorLoop()
{
    srand (QTime::currentTime().msec()); // инициализируем ГСЧ
}

static MoveDirection FindPath(const CMap &map, int startX, int startY, int endX, int endY, int *length = NULL)
{

#ifdef  ROAMING_ANT

    return (MoveDirection) (rand() % MdCount);

#endif  // ROAMING_ANT

#ifdef  MY_PATHFINDING

    return MdStop;

#endif  // MY_PATHFINDING

    int col = map.GetMapSizeX();
    int row = map.GetMapSizeY();
    std::vector<std::vector<int> > mapBuf(row, std::vector<int>(col, -1)); // двумерный вектор, равный размеру карты

    // все, что проходимо, делаем сушей, что непроходимо  - стенками

    CMap walkingMap = map;

    for(int y = 0; y < walkingMap.GetMapSizeY(); ++y)
    {
        for(int x = 0; x < walkingMap.GetMapSizeX(); ++x)
        {
            switch(walkingMap.Cell(x, y))
            {
            case McWater:
            case McWall:
            case McError:
                {
                    walkingMap.Cell(x, y) = McWall;
                    break;
                }
            default:
                {
                    walkingMap.Cell(x, y) = McGround;
                }
            }
        }
    }

    // нечего искать путь, все равно не пройдешь:
    if (walkingMap.Cell(endX, endY) == McWall)
    {
        return MdStop;
    }

    int step = 0;
    mapBuf[endY][endX] = step; // начинаем нумеровать с точки цели, начиная с 0
    bool pathFound = false; // // переменная, определяющая найден путь или нет
    MoveDirection move = MdStop;

    while(!pathFound)
    {
        // Пробегаем по всей карте, ищем клетки с номером, равным значению step.
        // Когда находим, нумеруем 4 соседних клетки значением на 1 большим, если они ещё не были пронумерованы
        bool nextStepFound = false; // переменная, определяющая нашлись ли клетки с номером, равным значению step
        for(int j = 0; j < row; j++)
        {
            for(int i = 0; i < col; i++)
            {
                if(mapBuf[j][i] == step)
                {
                    if(i + 1 < col)
                    {
                        if(mapBuf[j][i+1] < 0 && walkingMap.Cell(i,j) == McGround)
                        {
                            mapBuf[j][i+1] = step + 1;
                            nextStepFound = true;
                            // если пронумеровали клетку с координатами начальной точки, то выходим из цикла и отдаём команду, куда идти
                            if((i + 1 == startX) && (j == startY))
                            {
                                pathFound = true; // путь найден
                                move = MdLeft;
                            }
                        }
                    }
                    if(j + 1 < row)
                    {
                        if(mapBuf[j+1][i] < 0 && walkingMap.Cell(i,j) == McGround)
                        {
                            mapBuf[j+1][i] = step + 1;
                            nextStepFound = true;
                            if((i == startX) && (j + 1 == startY))
                            {
                                pathFound = true;
                                move = MdUp;
                            }
                        }
                    }
                    if(i > 0)
                    {
                        if(mapBuf[j][i-1] < 0 && walkingMap.Cell(i,j) == McGround)
                        {
                            mapBuf[j][i-1] = step + 1;
                            nextStepFound = true;
                            if((i - 1 == startX) && (j == startY))
                            {
                                pathFound = true;
                                move = MdRight;
                            }
                        }
                    }
                    if(j > 0)
                    {
                        if(mapBuf[j-1][i] < 0 && walkingMap.Cell(i,j) == McGround)
                        {
                            mapBuf[j-1][i] = step + 1;
                            nextStepFound = true;
                            if((i == startX) && (j - 1 == startY))
                            {
                                pathFound = true;
                                move = MdDown;
                            }
                        }
                    }
                }
            }
        }
        // если не нашли клетку с номером, равным значению step, то выходим из цикла, т.к. путь найти невозможно
        if(!nextStepFound)
        {
            return MdStop;
            break; // путь найти невозможно
        }
        step++;

       if(length != NULL)
        {
            *length = step;
        }

    }

    return move;
}




void CGeneratorLoop::GeneratorLoop(size_t mapSize, size_t waterSize, size_t foodAmount, size_t stickAmount, size_t antDistance, size_t trapAmount)
{
    int iteration = 1;

    GenerateMap(mapSize, mapSize, waterSize, foodAmount, stickAmount, antDistance, trapAmount);

    while(!CheckMap(foodAmount, stickAmount, trapAmount))
    {
        ++iteration;
        system("clear");
        std::cout << "Попытка номер: " << iteration << std::endl << std::flush;
        GenerateMap(mapSize, mapSize, waterSize, foodAmount, stickAmount, antDistance, trapAmount);
    }

    std::cout << "Карта успешно сгенерирована!" << std::endl <<
                 "Число итераций: " << iteration << std::endl << std::flush;
}

void CGeneratorLoop::WriteMap(const std::string &fileName)
{
    // печатаем карту на экране для наглядности

    std::cout  << "\nРазмер карты по горизонтали: " << m_Map.GetMapSizeX()
            << "\nРазмер карты по вертикали: " << m_Map.GetMapSizeY()
            << std::endl << std::flush;

    for (int rowNumber = 0; rowNumber < m_Map.GetMapSizeY(); ++rowNumber)
    {
        for (int colNumber = 0; colNumber < m_Map.GetMapSizeX(); ++colNumber)
        {
            std::cout << (char)m_Map.Cell(colNumber, rowNumber);
        }
        std::cout << std::endl;
    }

   // записываем файл с картой
    std::ofstream mapFile(fileName.c_str());

    if(!mapFile.is_open())
    {
        std::cerr << "Ошибка открытия файла!!!" << std::endl;
        return;
    }

    mapFile << "Map_Size " << m_Map.GetMapSizeY() << std::endl << std::flush;

    for (int rowNumber = 0; rowNumber < m_Map.GetMapSizeY() ; ++rowNumber)
    {
        mapFile << "Map_Row_";

        if (rowNumber < 10)
        {
            mapFile << "0";
        }

        mapFile << rowNumber << " ";

        for (int colNumber = 0; colNumber < m_Map.GetMapSizeX(); ++colNumber)
        {
            mapFile << (char)m_Map.Cell(colNumber, rowNumber);
        }

        mapFile << std::endl;
    }

}

void CGeneratorLoop::GenerateMap(size_t sizeX, size_t sizeY, size_t waterSize, size_t foodAmount, size_t stickAmount, size_t antDistance, size_t trapAmount)
{

    m_Map.SetMapSizeX(sizeX);
    m_Map.SetMapSizeY(sizeY);

    // заполняем всю карту сушей и делаем стенки

    for (int y = 0; y < m_Map.GetMapSizeY(); y++)
    {
        for (int x = 0; x < m_Map.GetMapSizeX(); x++)
        {
            m_Map.Cell(x, y) = McGround;
            if ((x == 0)||(x == m_Map.GetMapSizeX() - 1)||(y == 0)||(y == m_Map.GetMapSizeY() - 1))
            {
               m_Map.Cell(x, y) = McWall;
            }
        }
    }
    // размещаем водоем
    size_t x = 1 + rand() % (m_Map.GetMapSizeX() - 2);
    size_t y = 1 + rand() % (m_Map.GetMapSizeY() - 2);

    size_t waterCount = 0;
    while (waterCount < waterSize)
    {

        MoveDirection flow = (MoveDirection) (rand() % MdCount);

        switch (flow)
        {
        case MdRight:
            x++;
            if (m_Map.Cell(x, y) == McWall)
                x = abs(m_Map.GetMapSizeX() - 2 - x);
            break;
        case MdLeft:
            x--;
            if (m_Map.Cell(x, y) == McWall)
                x = abs(m_Map.GetMapSizeX() - 2 - x);
            break;
        case MdUp:
            y++;
            if (m_Map.Cell(x, y) == McWall)
                y = abs(m_Map.GetMapSizeY() - 2 - y);
            break;
        case MdDown:
            y--;
            if (m_Map.Cell(x, y) == McWall)
                y = abs(m_Map.GetMapSizeY() - 2 - y);
            break;
        default:
            continue;
        }


        if (m_Map.Cell(x, y) == McWater)
        {
            continue;
        }

        m_Map.Cell(x, y) = McWater;
        ++waterCount;
    }

    // устанавливаем муравейник
    int HillX, HillY;
    HillX = 1 + rand() % (m_Map.GetMapSizeX() - 2);
    HillY = 1 + rand() % (m_Map.GetMapSizeY() - 2);
    m_Map.Cell(HillX, HillY) = McHill;

     // ставим еду
    for ( size_t foodCount = 1; foodCount <= foodAmount; foodCount++)
    {
//        m_Map.Cell(1 + rand() % (m_Map.GetMapSizeX() - 2), 1 + rand() % (m_Map.GetMapSizeY() - 2)) = McFood;
          while(!m_Map.TryPlaceRandResource(McFood));
    }

    // ставим стройматериалы

   for (size_t stickCount = 1; stickCount <= stickAmount; stickCount++)
   {
//       m_Map.Cell(1 + rand() % (m_Map.GetMapSizeX() - 2), 1 + rand() % (m_Map.GetMapSizeY() - 2)) = McStick;
       while(!m_Map.TryPlaceRandResource(McStick));
   }

   // ставим ловушки

   for (size_t trapCount = 1; trapCount <= trapAmount; trapCount++)
   {
       while(!m_Map.TryPlaceRandResource(McTrap));
   }

   // ставим склад
   while(!m_Map.TryPlaceRandResource(McStock));


   // записываем в массив возможные начальные координаты муравьев
   MoveDirection m;



       for (int rowNumber = 0; rowNumber < m_Map.GetMapSizeY(); ++rowNumber)
       {
           for (int colNumber = 0; colNumber < m_Map.GetMapSizeX(); ++colNumber)
           {
               int length;
               m = FindPath(m_Map, HillX, HillY, colNumber, rowNumber, &length);
               if (length == antDistance)
               {
                    m_AbleCoordinates.push_back(colNumber);
                    m_AbleCoordinates.push_back(rowNumber);
               }
           }
       }



}

bool CGeneratorLoop::CheckMap(size_t foodAmount, size_t stickAmount, size_t trapAmount)
{
    // Тестовое условие для примера. Еда не должна закрыть собой муравейник.
    bool  errorHill = false, errorFood = true, errorStick = true, errorTrap = true,errorStock = true;
    size_t currentFoodCount = 0, currentStickCount = 0, currentTrapCount = 0, HillX, HillY;

    MoveDirection m;

    for (int rowNumber = 0; rowNumber < m_Map.GetMapSizeY(); ++rowNumber)
    {
        for (int colNumber = 0; colNumber < m_Map.GetMapSizeX(); ++colNumber)
        {
            //есть ли муравейник

            if (m_Map.Cell(colNumber, rowNumber) == McHill)
            {
                errorHill = true;
                HillX = colNumber;
                HillY = rowNumber;
            }

            //подсчитываем кол-во еды
            if (m_Map.Cell(colNumber, rowNumber) == McFood)
            {
                currentFoodCount++;
                //проверяем можно ли дойти от муровейника до еды
                m = FindPath(m_Map, HillX, HillY, colNumber, rowNumber);
                if (m == MdStop)
                {
                    errorFood = false;
                }
            }

            //подсчитываем кол-во ресурсов
            if (m_Map.Cell(colNumber, rowNumber) == McStick)
            {
                currentStickCount++;
                //проверяем можно ли дойти от муровейника до ресурсов
                m = FindPath(m_Map, HillX, HillY, colNumber, rowNumber);
                if (m == MdStop)
                {
                    errorStick = false;
                }
            }

            //подсчитываем кол-во ловушек
            if (m_Map.Cell(colNumber, rowNumber) == McTrap)
            {
                currentTrapCount++;
                //проверяем можно ли дойти от муровейника до ловушек
                m = FindPath(m_Map, HillX, HillY, colNumber, rowNumber);
                if (m == MdStop)
                {
                    errorTrap = false;
                }
            }

            //проверяем можно ли дойти от муровейника до склада
            if (m_Map.Cell(colNumber, rowNumber) == McStock)
            {
                m = FindPath(m_Map, HillX, HillY, colNumber, rowNumber);
                if (m == MdStop)
                {
                    errorStock = false;
                }
            }

            if ((currentStickCount == stickAmount) && (currentFoodCount == foodAmount) && errorHill && errorStick && errorFood && errorTrap && errorStock)
            {
                return true;
            }
        }
    }

    return false;
}

const int * CGeneratorLoop::GetLinkOfAbleCoordinates()
{
    return &m_AbleCoordinates[0];
}
