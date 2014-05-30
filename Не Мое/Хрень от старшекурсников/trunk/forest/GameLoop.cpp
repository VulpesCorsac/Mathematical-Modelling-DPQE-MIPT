#include "GameLoop.h"
#include "PacketParser.h"
#include "CommandParser.h"
#include "FirstCommandParser.h"
#include "StateWriter.h"
#include "Ant.h"
#include <QtCore>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtTest/QTest>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "CMapParser.h"

const int stickOnMap = 10;
const int foodOnMap = 10;
const int trapOnMap = 5;

const int lionStomach = 1;
const int trapReleaseInterval = 100000;
const size_t managerCommandIndex = 4;

const int stickToWin = 50;
const int foodToWin = 50;
const int childrenToWin = 20;
const int cowToWin = 5;
const int mushroomToWin = 0;

static MoveDirection FindPath(const CMap &map, int startX, int startY, int endX, int endY)
{
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
            break; // путь найти невозможно
        }
        step++;
    }

    return move;
  }



CGameLoop::CGameLoop()
:   m_GameStep(-1)
,   m_FoodInHill(0)
,   m_FoodInStock(0)
,   m_StickInHill(0)
,   m_ChildrenGrownup(0)
,   m_CowInHill(0)
,   m_MushroomInHill(0)
,   m_ManagerDirection(ToHill)
{
    srand (QTime::currentTime().msec()); // инициализируем ГСЧ
}

void CGameLoop::ReadMap()
{

    m_Map.SetMapSizeX(20);
    m_Map.SetMapSizeY(20);
    m_DynMap.SetMapSizeX(20);
    m_DynMap.SetMapSizeY(20);

    // временно вместо чтения из файла заполняем сушей

    for (int y = 0; y < m_Map.GetMapSizeY(); y++)
    {
        for (int x = 0; x < m_Map.GetMapSizeX(); x++)
        {
            m_Map.Cell(x, y) = McGround;
        }
    }

    // ставим стенки
    for (int y = 0; y < m_Map.GetMapSizeY(); y++)
    {
        m_Map.Cell(0, y) = McWall;        
        m_Map.Cell(m_Map.GetMapSizeX() - 1, y) = McWall;       
    }

    for (int x = 0; x < m_Map.GetMapSizeX(); x++)
    {
        m_Map.Cell(x, 0) = McWall;
        m_Map.Cell(x, m_Map.GetMapSizeY() - 1) = McWall;
    }

    // ставим еду, дерево и ловушки
    for(int stick = 0; stick < stickOnMap; ++stick)
    {
        while(!m_Map.TryPlaceRandResource(McStick));
    }

    for(int food = 0; food < foodOnMap; ++food)
    {
        while(!m_Map.TryPlaceRandResource(McFood));
    }

    for(int trap = 0; trap < trapOnMap; ++trap)
    {
        while(!m_Map.TryPlaceRandResource(McTrap));
    }

    // и ставим муравейник
    while(!m_Map.TryPlaceRandResource(McHill));

    // и склад
    while(!m_Map.TryPlaceRandResource(McStock));

     //std::ifstream map("../../../../map.txt");
     std::ifstream map("../map.txt");


     if(!map.is_open())
     {
         std::cerr << "Ошибка открытия файла map!!!" << std::endl;
     }
     else
     {
         CMapParser MapParser;

         ReadBlockFromStream(map, &MapParser);
         if(MapParser.IsError())
         {
             std::cout << "\nError in MapParser: " << MapParser.GetErrorMessage() << std::endl;
         }
         else
         {
             m_Map = MapParser.GetMapInMapParsr();
             m_DynMap.SetMapSizeX(m_Map.GetMapSizeX());
             m_DynMap.SetMapSizeY(m_Map.GetMapSizeY());
         }
     }

    // std::cout << "карта успешно заполнена" << std::endl << std::flush;
}

void CGameLoop::GameLoop(int port, int ants, int delay)
{

//    std::ifstream f("../commandlog.txt");

//    if(!f.is_open())
//    {
//        std::cerr << "Ошибка открытия файла!!!" << std::endl;
//        return;
//    }


    QTcpServer tcpServer;
    tcpServer.setMaxPendingConnections(ants);

    if (!tcpServer.listen(QHostAddress::Any, port))
    {
        qDebug() <<  "ERROR! Unable to start the server: "
                << tcpServer.errorString();

        tcpServer.close();
        return;
    }

    std::cout << "Жду муравьев...." << std::endl << std::flush;

    // ожидаем поключения всех муравьев и получаем указатели на их сокеты
    for(int antNumber = 0; antNumber < ants; ++antNumber)
    {
        while (!tcpServer.waitForNewConnection(-1)) // таймаут ожидания в миллисекундах, -1 - бесконечное ожидание
        {
        }

        if(tcpServer.hasPendingConnections())
        {
            std::cerr << "Муравей подсоединился!!! Всего муравьев: " << antNumber + 1
                      << " Ждем еще: " << ants - antNumber - 1 << "\n";
        }

        QTcpSocket *next_ant = tcpServer.nextPendingConnection();

        CAnt a;
        a.SetAntSocket(next_ant);
        m_Map.PushAnt(a);
    }


    for (size_t antNumber = 0; antNumber < m_Map.GetNumberOfAnts(); ++antNumber)
    {
        if (m_Map.GetAnt(antNumber).AntIsBanned() || m_Map.GetAnt(antNumber).AntIsWinner())
        {
            continue;
        }

        CFirstCommandParser firstCommandParser;

        if(!ReadBlockFromStream(m_Map.GetAnt(antNumber).GetAntSocket(), &firstCommandParser))
        {
            //тут обрабатываем ошибки

            if(firstCommandParser.IsError())
            {
                std::cerr << "Муравей забанен!!! По причине: " << std::endl;
                std::cerr << "Ошибка в FirstCommandParser: " << firstCommandParser.GetErrorMessage()
                        <<  std::endl << std::flush;
            }
            else
            {
                qDebug() << "SOCKET ERROR: " << m_Map.GetAnt(antNumber).GetAntSocket()->errorString();
            }
            m_Map.GetAnt(antNumber).BanAnt();
            continue;
        }
        else
        {
            ApplyFirstCommand(antNumber, firstCommandParser.GetCommand());

            const CFirstCommand &c = firstCommandParser.GetCommand(); // ссылка для сокращения последующего кода
            std::cout << "Муравья зовут: " << c.GetName() << std::endl;
        }
    }

    UpdateMap();

    for (size_t antNumber = 0; antNumber < m_Map.GetNumberOfAnts(); ++antNumber)
    {
        if (m_Map.GetAnt(antNumber).AntIsBanned())
        {
            continue;
        }
        CStateWriter stateWriter(m_Map.GetAnt(antNumber).GetAntSocket());
        if (!stateWriter.SendState(antNumber, m_Map, m_Board) && !m_Map.GetAnt(antNumber).AntIsWinner())
        {
            m_Map.GetAnt(antNumber).BanAnt();
            //continue;
        }
    }

     //std::ofstream log("../../../../gamelog.txt");
     std::ofstream log("../gamelog.txt");

    for(;;) // основной цикл
    {
        QTest::qSleep(delay + 1);

        if (NumberOfPlayingAnts() == 0) // все муравьи либо победили, либо забанены
        {
            log.close();
            return;
        }

        for (size_t antNumber = 0; antNumber < m_Map.GetNumberOfAnts(); ++antNumber)
        {
            if (m_Map.GetAnt(antNumber).AntIsBanned() || m_Map.GetAnt(antNumber).AntIsWinner())
            {
                continue;
            }

            CCommandParser cmdParser;

            if(!ReadBlockFromStream(m_Map.GetAnt(antNumber).GetAntSocket(), &cmdParser))
            {
                //тут обрабатываем ошибки

                if(cmdParser.IsError())
                {
                    std::cerr << "Муравей забанен!!! По причине: " << std::endl;
                    std::cerr << "Ошибка в CommandParser: " << cmdParser.GetErrorMessage()
                            <<  std::endl << std::flush;
                }
                else
                {
                    qDebug() << "SOCKET ERROR: " << m_Map.GetAnt(antNumber).GetAntSocket()->errorString();
                }
                m_Map.GetAnt(antNumber).BanAnt();
                continue;
            }
            else
            {
                ApplyCommand(antNumber, cmdParser.GetCommand());

                //                std::cout << "Муравей дает команду: " << MoveDirectionToString(cmdParser.GetCommand().GetCommandMove())
                //                        << "\n" << std::endl;
            }
        }

        // рассчитываем новое состояние карты.
        UpdateMap();

        for (size_t antNumber = 0; antNumber < m_Map.GetNumberOfAnts(); ++antNumber)
        {
            if (m_Map.GetAnt(antNumber).AntIsBanned())
            {
                continue;
            }

            CStateWriter stateWriter(m_Map.GetAnt(antNumber).GetAntSocket());
            if (!stateWriter.SendState(antNumber, m_Map, m_Board) && !m_Map.GetAnt(antNumber).AntIsWinner())
            {
                m_Map.GetAnt(antNumber).BanAnt();
                //continue;
            }
        }

        // печатаем карту

        ShowMap();
        WriteLog(log);
    }
}


void CGameLoop::CloseGame()
{

}

void CGameLoop::PlaceAnt(int antNumber)
{
    CAnt &a = m_Map.GetAnt(antNumber);
    if ((a.GetAntType() == AtCow) || (a.GetAntType() == AtLion))
    {
        // помещаем в случайную клетку
        bool hillIsReachable = false;
        while(!hillIsReachable)
        {
            int startX = rand() % (m_Map.GetMapSizeX() - 2) + 1;
            int startY = rand() % (m_Map.GetMapSizeX() - 2) + 1;
            bool hillPresent = false;

            for (int endY = 0; endY < m_Map.GetMapSizeY(); ++endY)
            {
                for (int endX = 0; endX < m_Map.GetMapSizeX(); ++endX)
                {
                    if (m_Map.Cell(endX, endY) == McHill)
                    {
                        hillPresent = true;

                        if (MdStop != FindPath(m_Map, startX, startY, endX, endY))
                        {
                            hillIsReachable = true;
                        }
                    }
                }
            }

            a.SetAntPosX(startX);
            a.SetAntPosY(startY);

            if (!hillPresent)
            {
                std::cerr << "ОШИБКА! На карте нет муравейника!" << std::endl << std::flush;
                break;
            }
        }
    }
    else
    {
       // остальных в муравейник
        bool hillPresent = false;
        int hillX = 0;
        int hillY = 0;

        for (int endY = 0; endY < m_Map.GetMapSizeY(); ++endY)
        {
            for (int endX = 0; endX < m_Map.GetMapSizeX(); ++endX)
            {
                if (m_Map.Cell(endX, endY) == McHill)
                {
                    hillPresent = true;
                    hillX = endX;
                    hillY = endY;

                }
            }
        }


        a.SetAntPosX(hillX);
        a.SetAntPosY(hillY);

        if (!hillPresent)
        {
            std::cerr << "ОШИБКА! На карте нет муравейника!" << std::endl << std::flush;
        }
    }
}

void CGameLoop::ApplyFirstCommand(int antNumber, const CFirstCommand &firstCommand)
{

    // заполняем поля муравья полученными данными:
    CAnt &a = m_Map.GetAnt(antNumber);
    a.SetAntName(firstCommand.GetName());
    a.SetAntType(firstCommand.GetType());

    // выбираем радиус обзора муравья (потом сделать выбор в зависимости от его типа)

    switch (a.GetAntType())
    {
    case AtQueen:
        {
            a.SetAntViewRadius(0);
            break;
        }
    case AtWorker:
    case AtDoctor:
    case AtTutor:
    case AtFarmer:
    case AtCow:
    case AtManager:
        {
            a.SetAntViewRadius(1);
            break;
        }
    case AtScout:    
    case AtLion:
    case AtSapper:
    case AtHunter:
        {
            a.SetAntViewRadius(2);
            break;
        }
    case AtTracker:
    case AtCowboy:
        {
            a.SetAntViewRadius(3);
            break;
        }
    case AtUnknown:
    case AtCount:
        break;
    }

    // помещаем на карту
    PlaceAnt(antNumber);


    // помещаем видимые им ячейки в число открытых
    SetAntCellsOpened(antNumber);

    // объявляем здоровым
    a.SetAntStatus(AsAlive);
}

void CGameLoop::UpdateMap() // расчет нового состояния карты после хода всех муравьев
{
    // !!! В этом методе должна находится основная игровая логика !!!

    ++m_GameStep;

    UpdateDynMap();

    if(m_Board.GetMessage(BkQueenCommand).size() > managerCommandIndex)
    {
        m_ManagerDirection = (ManagerDirection)m_Board.GetMessage(BkQueenCommand)[managerCommandIndex];
    }

    for (size_t antNumber = 0; antNumber < m_Map.GetNumberOfAnts(); ++antNumber)
    {
        CAnt &a = m_Map.GetAnt(antNumber);

        if (m_Map.GetAnt(antNumber).AntIsBanned() || m_Map.GetAnt(antNumber).AntIsWinner())
        {
            continue;
        }

        switch (m_Map.Cell(a.GetAntPosX(), a.GetAntPosY()))
        {
        case McFood:
            if(a.GetAntType() == AtLion)
            {
                break;
            }
            if(a.GetAntLoad() == AlEmpty)
            {
                a.SetAntLoad(AlFood);
            }
            break;
        case McStick:
            if(a.GetAntType() == AtLion)
            {
                break;
            }
            if(a.GetAntLoad() == AlEmpty)
            {
                a.SetAntLoad(AlStick);
            }
            break;
        case McHill:
            {
                if(a.GetAntType() == AtLion)
                {
                    if(m_FoodInHill >= lionStomach)
                    {
                        m_FoodInHill -= lionStomach;
                    }
                    PlaceAnt(antNumber);
                }
                else if(a.GetAntType() == AtManager)
                {
                    if(m_ManagerDirection == ToHill)
                    {
                        if(a.GetAntLoad() == AlFood)
                        {
                            ++m_FoodInHill;
                            a.SetAntLoad(AlEmpty);
                        }
                    }
                    else if(m_ManagerDirection == ToStock)
                    {
                        if(a.GetAntLoad() == AlEmpty)
                        {
                            if(m_FoodInHill > 0)
                            {
                                a.SetAntLoad(AlFood);
                                --m_FoodInHill;
                            }
                        }
                    }
                }
                else
                {
                    switch(a.GetAntLoad())
                    {
                    case AlFood:
                        ++m_FoodInHill;
                        a.SetFoodResult(a.GetFoodResult() + 1);
                        a.SetAntLoad(AlEmpty);
                        break;
                    case AlStick:
                        ++m_StickInHill;
                        a.SetStickResult(a.GetStickResult() + 1);
                        a.SetAntLoad(AlEmpty);
                        break;
                    case AlChild:
                        if (a.GetLastStepNumber() >= 5)
                        {
                            m_ChildrenGrownup++;
                            a.SetAntLoad(AlEmpty);
                        }
                    case AlError:
                    case AlEmpty:
                    case AlWater:
                        if ((a.GetAntType() == AtTutor) && (a.GetAntLoad() == AlEmpty))
                        {
                            a.SetAntLoad(AlChild);
                            break;
                        }
                    case AlCount:
                        break;
                    }
                }
                a.SetLastStepNumber(0);
                break;
            }
        case McTrap:
            {
                if (a.GetAntType() == AtSapper)
                {
                    if((rand() % 2) == 0) // оператор "а что если?"
                    {
                        a.SetAntStatus(AsIll);
                    }
                    else
                    {
                        m_Map.Cell(a.GetAntPosX(), a.GetAntPosY()) = McGround;
                    }

                }
                else if((a.GetAntType() != AtLion) && (a.GetAntType() != AtCow) && (a.GetAntType() != AtDoctor))
                {
                    a.SetAntStatus(AsIll);
                }
                break;
            }
        case McStock:
            {
                if(a.GetAntType() == AtManager)
                {
                    if(m_ManagerDirection == ToStock)
                    {
                        if(a.GetAntLoad() == AlFood)
                        {
                            ++m_FoodInStock;
                            a.SetAntLoad(AlEmpty);
                        }
                    }
                    else if (m_ManagerDirection == ToHill)
                    {
                        if(a.GetAntLoad() == AlEmpty)
                        {
                            if(m_FoodInStock > 0)
                            {
                                a.SetAntLoad(AlFood);
                                --m_FoodInStock;
                            }
                        }
                    }
                }
                break;
            }
        case McWay:
        case McGround:        
        case McUnknown:
            break;
        case McWater:
        case McWall:
        case McError:
            break;
        }
        a.SetLastStepNumber(a.GetLastStepNumber() + 1); //увеличеваем кол-во шагов

        // формируем поле зрения муравья
        int x = a.GetAntPosX();
        int y = a.GetAntPosY();
        int r = a.GetAntViewRadius();
        size_t maxAntsInCell = 1;
        a.SetVisibleCells("");
        a.SetVisibleDynCells("");

        for (int row = y - r; row <= y + r; row++)
        {
            for (int col = x - r; col <= x + r; col++)
            {
                MapCell cell = m_Map.Cell(col, row);

                if((a.GetAntType() != AtSapper) && (cell == McTrap))
                {
                    cell = McGround;
                }

                a.SetVisibleCells(a.GetVisibleCells() + (char)cell);

               // определяем максимальное число муравьев в одной ячейке на данном кусочке карты
               if (m_DynMap.Cell3D(col, row).size() > maxAntsInCell)
               {
                   maxAntsInCell = m_DynMap.Cell3D(col, row).size();
               }
            }
        }


        for (size_t depth = 0; depth < maxAntsInCell; ++depth)
        {
            for (int row = y - r; row <= y + r; row++)
            {
                for (int col = x - r; col <= x + r; col++)
                {
                    if (m_DynMap.Cell3D(col, row).size() > depth)
                    {
                        a.SetVisibleDynCells(a.GetVisibleDynCells() + AntTypeToChar(m_DynMap.Cell3D(col, row)[depth]));
                    }
                    else
                    {
                        a.SetVisibleDynCells(a.GetVisibleDynCells() + AntTypeToChar(AtUnknown));
                    }
                }
            }
        }
    }


    if ((m_StickInHill >= stickToWin) && (m_FoodInHill >= foodToWin) && (m_ChildrenGrownup >= childrenToWin) && (m_CowInHill >= cowToWin) && (m_MushroomInHill >= mushroomToWin))
    {
        //ПОБЕДА!!!
        for (size_t antNumber = 0; antNumber < m_Map.GetNumberOfAnts(); ++antNumber)
        {
            if (m_Map.GetAnt(antNumber).AntIsBanned())
            {
                continue;
            }
            m_Map.GetAnt(antNumber).SetAntStatus(AsWinner);
            m_Map.GetAnt(antNumber).SetLastStepNumber(m_GameStep);
        }
    }

    if((m_GameStep % trapReleaseInterval) == 0)
    {
        for (size_t antNumber = 0; antNumber < m_Map.GetNumberOfAnts(); ++antNumber)
        {
            if (m_Map.GetAnt(antNumber).GetAntStatus() == AsIll)
            {
                m_Map.GetAnt(antNumber).SetAntStatus(AsAlive);
            }
        }
    }

    //не встретился ли больной муравей с доктором?
    for (size_t antNumber = 0; antNumber < m_Map.GetNumberOfAnts(); ++antNumber)
    {
        CAnt &a = m_Map.GetAnt(antNumber);

        if (m_Map.GetAnt(antNumber).AntIsBanned() || m_Map.GetAnt(antNumber).AntIsWinner())
        {
            continue;
        }

        if(a.GetAntStatus() == AsIll)
        {
            if(IsNeighbour(a, AtDoctor))
            {
                a.SetAntStatus(AsAlive);
            }
        }

        if(a.GetAntType() == AtLion)
        {
            if(IsNeighbour(a, AtHunter))
            {
                PlaceAnt(antNumber);
            }
        }
        else if(a.GetAntType() == AtCow)
        {
            if(IsNeighbour(a, AtCowboy))
            {
                PlaceAnt(antNumber);
                ++m_CowInHill;
            }
        }
    }
}

bool CGameLoop::IsNeighbour(const CAnt &ant, const AntType neighbour)
{
    std::vector<AntType> neighbours = m_DynMap.Cell3D(ant.GetAntPosX(), ant.GetAntPosY());

    for(size_t depth = 0; depth < neighbours.size(); ++depth)
    {
        if(neighbours[depth] == neighbour)
        {
            return true;
        }
    }

    return false;
}

void CGameLoop::UpdateDynMap() // отображение на динамической карте объектов, которые могут двигаться
{

    m_DynMap.Clear();

    for (size_t antNumber = 0; antNumber < m_Map.GetNumberOfAnts(); ++antNumber)
    {
        CAnt &a = m_Map.GetAnt(antNumber);      
        if (m_Map.GetAnt(antNumber).AntIsBanned() || m_Map.GetAnt(antNumber).AntIsWinner())
        {
            continue;
        }

        m_DynMap.Cell3D(a.GetAntPosX(), a.GetAntPosY()).push_back(a.GetAntType());
    }
}

void CGameLoop::ApplyCommand(int antNumber, const CCommand &command)
{
    CAnt &a = m_Map.GetAnt(antNumber);
    MoveDirection moveCommand = command.GetCommandMove();

    if(a.GetAntStatus() == AsIll)
    {
        moveCommand = MdStop;
    }

    a.SetAntMoveCommand(moveCommand);

    int nextX = a.GetAntPosX();
    int nextY = a.GetAntPosY();

    switch (moveCommand)
    {
    case MdLeft:
        --nextX;
        break;
    case MdRight:
        ++nextX;
        break;
    case MdUp:
        --nextY;
        break;
    case MdDown:
        ++nextY;
        break;
    case MdUnknown:
    case MdCount:
    case MdStop:
        break;
    }

    switch (m_Map.Cell(nextX, nextY))
    {
    case McWay:
    case McGround:
    case McHill:
    case McFood:
    case McStick:
    case McStock:
    case McTrap:
    case McUnknown:
        a.SetAntPosX(nextX);
        a.SetAntPosY(nextY);
        break;
    case McWater:
    case McWall:
    case McError:
        break;
    }

    // помещаем видимые им ячейки в число открытых
    SetAntCellsOpened(antNumber);

    // обновляем доску объявлений
    UpdateBoard(command);

}

void CGameLoop::SetAntCellsOpened(int antNumber)
{
    CAnt &a = m_Map.GetAnt(antNumber);
    int x = a.GetAntPosX();
    int y = a.GetAntPosY();
    int r = a.GetAntViewRadius();
    for (int rowNumber = y - r; rowNumber <= y + r; ++rowNumber)
    {
        for (int colNumber = x - r; colNumber <= x + r; ++colNumber)
        {
           a.AddOpenedCell(m_Map.GetCellIndex(x, y));
        }
     }
}


void CGameLoop::UpdateBoard(const CCommand &command)
{

    for(int keyNumber = 0; keyNumber < BkCount; ++keyNumber)
    {

        BoardKey bk = (BoardKey)keyNumber;
        const std::vector<int> &newMessage = command.GetCommandMessage(bk);

        switch(bk)
        {
        case BkQueenCommand:            
            m_Board.DeleteMessage(bk);
            m_Board.AddMessage(newMessage, bk);
            break;
        case BkLion:
        case BkTrap:
        case BkStick:
        case BkFood:
            for (size_t elementIndex = 0; elementIndex < newMessage.size(); elementIndex += 2)
            {
                if (!m_Board.FindMessage(bk, newMessage[elementIndex], newMessage[elementIndex + 1]))
                {
                    m_Board.AddValue(newMessage[elementIndex], bk);
                    m_Board.AddValue(newMessage[elementIndex + 1], bk);
                }
                // else std::cout << "Replay Message" << std::endl;
            }
            break;
        case BkIll:
            {
//                m_Board.AddMessage(newMessage, bk);

//                std::vector<int> oldMessage = m_Board.GetMessage(bk);
                m_Board.DeleteMessage(bk);

//                for (size_t elementIndex = 0; elementIndex < m_Board.GetMessage(bk).size(); elementIndex += 2)
//                {
//                    for (size_t antNumber = 0; antNumber < m_Map.GetNumberOfAnts(); ++antNumber)
//                    {
//                        CAnt &a = m_Map.GetAnt(antNumber);
//                        if (m_Map.GetAnt(antNumber).AntIsBanned() || m_Map.GetAnt(antNumber).AntIsWinner())
//                        {
//                            continue;
//                        }

//                        if((oldMessage[elementIndex] == a.GetAntPosX()) && (oldMessage[elementIndex + 1] == a.GetAntPosY()) && (a.GetAntStatus() == AsIll))
//                        {
//                            m_Board.AddValue(a.GetAntPosX(), bk);
//                            m_Board.AddValue(a.GetAntPosY(), bk);
//                        }
//                    }
//                }
                for (size_t antNumber = 0; antNumber < m_Map.GetNumberOfAnts(); ++antNumber)
                {
                    CAnt &a = m_Map.GetAnt(antNumber);
                    if (m_Map.GetAnt(antNumber).AntIsBanned() || m_Map.GetAnt(antNumber).AntIsWinner())
                    {
                        continue;
                    }
                    if(a.GetAntStatus() == AsIll)
                    {
                        m_Board.AddValue(a.GetAntPosX(), bk);
                        m_Board.AddValue(a.GetAntPosY(), bk);
                    }
                }
            }
            break;
        case BkLionTrace:
        case BkUnknown:
        case BkCount:
            break;
        }
    }
}


int CGameLoop::NumberOfPlayingAnts()
{
    int playingAnts = 0;

    for(size_t antNumber = 0; antNumber < m_Map.GetNumberOfAnts(); ++antNumber)
    {
        if  (m_Map.GetAnt(antNumber).AntIsBanned() || m_Map.GetAnt(antNumber).AntIsWinner())
        {
            continue;
        }
        else
        {
            ++playingAnts;
        }
    }

    return playingAnts;
}

bool CGameLoop::IsAntWinner(int antNumber)
{
    CAnt &a = m_Map.GetAnt(antNumber);

    // всем в муравейник, а завхозу на склад!

    switch (a.GetAntType())
    {
    case AtManager:
        {
            return m_Map.Cell(a.GetAntPosX(), a.GetAntPosY()) == McStock;
        }
    case AtWorker:
    case AtDoctor:
    case AtTutor:
    case AtFarmer:
    case AtCow:
    case AtScout:
    case AtQueen:
    case AtTracker:
    case AtSapper:
    case AtHunter:
    case AtCowboy:
    case AtLion:
        {
            return m_Map.Cell(a.GetAntPosX(), a.GetAntPosY()) == McHill;
        }
    case AtUnknown:
    case AtCount:
    default:
        return false;
    }

    //return (a.GetCountOfOpenedCells() == m_Map.GetMapSizeX() * m_Map.GetMapSizeY());
}

bool CGameLoop::ReadBlockFromStream(QTcpSocket* socket, CItemParser *itemParser)
{
    CPacketParser packetParser(itemParser);
    for (;;)
    {
        if (!socket->bytesAvailable())
        {
            socket->waitForReadyRead(-1);
        }

        char c;
        if (!socket->getChar(&c))
        {
            return false;
        }
        else
        {
            if(!packetParser.AddByte(c)) // выходим либо по ошибке, либо по пустой строке
            {
                return !itemParser->IsError();
            }
        }
    }
}

bool CGameLoop::ReadBlockFromStream(std::istream &s, CItemParser *itemParser)
{
    //создаем объект - парсер пакета.  При выходе из функции он уничтожится.
    CPacketParser parser(itemParser);

    for(;;)
    {
        char c;
        if(!s.get(c)) // стандартный метод класса std::istream для чтения одного байта из файла
        {
            return false;
        }
        else
        {
            if(!parser.AddByte(c))
            {
                if (parser.IsError())
                {
                    std::cerr << "Ошибка в PacketParser: " << parser.GetErrorMessage() <<"\n"<<  std::endl;
                }
                return !itemParser->IsError(); // если встретилась пустая строка,
                                    // возвращаем инвертированный признак ошибки
            }
        }
    }
}

void CGameLoop::ShowMap()
{
    system("clear");
    std::cout  << "Шаг: " << m_GameStep << " Еды: " << m_FoodInHill + m_FoodInStock
               << " Веточек: " << m_StickInHill
               << " Деток: "   << m_ChildrenGrownup
               <<  " Коровок: " << m_CowInHill
               <<  " Грибов: " << m_MushroomInHill
               << std::endl;

    for (int rowNumber = 0; rowNumber < m_Map.GetMapSizeY(); ++rowNumber)
    {
        for (int colNumber = 0; colNumber < m_Map.GetMapSizeX(); ++colNumber)
        {
            if(m_DynMap.Cell(colNumber, rowNumber) == AtUnknown)
            {
                std::cout << (char)m_Map.Cell(colNumber, rowNumber);
            }
            else
            {
                std::cout << AntTypeToChar(m_DynMap.Cell(colNumber, rowNumber));
            }
        }
        std::cout << std::endl;
    }

    for (size_t antNumber = 0; antNumber < m_Map.GetNumberOfAnts(); ++antNumber)
    {
        const CAnt &a = m_Map.GetAnt(antNumber);
        if (a.AntIsWinner())
        {
            std::cout  << "Муравей " << a.GetAntName()
                    << " по профессии " << AntTypeToString(a.GetAntType()) << " "
                    << AntStatusToString(a.GetAntStatus())
                    << " для победы собрал " << a.GetFoodResult() << " еды и "
                    << a.GetStickResult() << " веточек!" << std::endl;

        }
        else if(a.AntIsBanned())
        {
            std::cout  << "Муравей " << a.GetAntName()
                    << " по профессии " << AntTypeToString(a.GetAntType()) << " "
                    << AntStatusToString(a.GetAntStatus())
                    << " на шаге номер " << a.GetLastStepNumber() << "!" << std::endl;
        }
        else
        {
            std::cout  << "Муравей " << a.GetAntName()
                    << " по профессии " << AntTypeToString(a.GetAntType()) << " "
                    << AntStatusToString(a.GetAntStatus()) << "!" << std::endl
                    << "Находится в клетке X = " << a.GetAntPosX() << " Y = " << a.GetAntPosY() << std::endl
                    << "Несет " << a.GetAntLoadString() << "!"
                    << std::endl << std::flush;
//        std::cout << a.GetVisibleCells() << std::endl << std::flush;
//        std::cout << a.GetVisibleDynCells() << std::endl << std::flush;
//        std::cout << m_DynMap.Cell3D(a.GetAntPosX(), a.GetAntPosY()).size() << std::endl << std::flush;

        }
    }

    std::cout  << "Состояние доски объявлений:" << std::endl << std::flush;
    m_Board.PrintBoard();
}

void CGameLoop::WriteLog(std::ofstream &log)
{
    log << "Game_Step " << m_GameStep << "\n";
    log << "Map_Size " << m_Map.GetMapSizeX() << "\n";
    for(int yInGameStep = 0; yInGameStep < m_Map.GetMapSizeY();  yInGameStep++ )
    {
        log << "Map_Row_";
        if (yInGameStep < 10)
        {
           log << "0";
        }
        log << yInGameStep << " ";

        for(int xInGameStep = 0; xInGameStep < m_Map.GetMapSizeX();  xInGameStep++)
        {
            log << (char)m_Map.Cell(xInGameStep,yInGameStep);
        }
        log << "\n";
    }

    log << "Food_In_Hill " << m_FoodInHill << "\n";
    log << "Food_In_Stock " << m_FoodInStock << "\n";
    log << "Stick_In_Hill " << m_StickInHill << "\n";
    log << "Children_Grownup " << m_ChildrenGrownup << "\n";

    log << "Number_Of_Ants " << m_Map.GetNumberOfAnts() << "\n";

    for (size_t antNumber = 0; antNumber < m_Map.GetNumberOfAnts(); ++antNumber)
    {
        const CAnt &a = m_Map.GetAnt(antNumber);

        log << "Ant_Name " << a.GetAntName() << "\n";
        log << "Ant_Type " << AntTypeToString(a.GetAntType()) << "\n";
        log << "Ant_Pos_X " << a.GetAntPosX() << "\n";
        log << "Ant_Pos_Y " << a.GetAntPosY() << "\n";
        log << "Ant_Status " << a.GetAntStatus() << "\n";

    }

    log << "Number_Of_Messages " << BkCount << "\n";

        for(int numberMessageBoard = 0; numberMessageBoard < BkCount; numberMessageBoard++)
        {
            BoardKey bk = (BoardKey)numberMessageBoard;
            log << BoardKeyToString(bk) << " ";
            std::vector<int> messageBoard = m_Board.GetMessage(bk);
            for(size_t number = 0; number <  messageBoard.size(); ++number)
            {
                log << messageBoard[number] << " ";
            }
            log << "\n";
        }

    log << "\n";
    log.flush();
}
