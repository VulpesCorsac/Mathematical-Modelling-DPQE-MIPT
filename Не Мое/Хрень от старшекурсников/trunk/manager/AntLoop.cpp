//#define DEBUG
//#define ROAMING_ANT
//#define MY_PATHFINDING

#include "AntLoop.h"
#include "AntStatus.h"
#include "PacketParser.h"
#include "StateParser.h"
#include "MoveDirection.h"
#include "CommandWriter.h"
#include <QtCore>
#include <QTcpSocket>
#include <QString>
#include "stdlib.h"
#include <fstream>
#include <iostream>
#include <vector>

static MoveDirection FindPath(const CMap &map, int startX, int startY, int endX, int endY)
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
            break; // путь найти невозможно
        }
        step++;
    }

    return move;
}

CAntLoop::CAntLoop()
    :m_StockFound(false)
    ,m_HillFound(false)
    ,m_StockFound2(false)
    ,m_HillFound2(false)
    ,m_Swap(false)
    ,m_GoFromHillTakeFood(false)
    ,m_GoFromHillTakeStick(false)
    ,m_GoStock(false)
{
    srand (QTime::currentTime().msec()); // инициализируем ГСЧ
}

void CAntLoop::InitAnt(const std::string &name, const AntType type)
{
    CAnt ant;
    ant.SetAntName(name);
    ant.SetAntType(type);

    QTcpSocket *socket;
    socket = new QTcpSocket();
    ant.SetAntSocket(socket);

    m_Map.PushAnt(ant);
}

void CAntLoop::ConnectMap(const QString &ip, int port)
{

#ifdef DEBUG   //***тестируем алгоритм поиска пути**

    m_Map.SetMapSizeX(20);
    m_Map.SetMapSizeY(20);

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
    int x = rand() % m_Map.GetMapSizeX();
    int y = rand() % m_Map.GetMapSizeY();

    int water, p;
    for (water = 1; water <= 200; water++)
    {
        p = rand() % 4;
        if (p == 0)
        {
            x++;
        }
        else if (p == 1)
        {
            x--;
        }
        else if (p == 2)
        {
            y++;
        }
        else if (p == 3)
        {
            y--;
        }
        if (x == 0)
        {
            x = m_Map.GetMapSizeX() - 2;
        }
        else if (x == m_Map.GetMapSizeX() - 1)
        {
            x = 1;
        }
        else if (y == 0)
        {
            y = m_Map.GetMapSizeY() - 2;
        }
        else if (y == m_Map.GetMapSizeY() - 1)
        {
            y = 1;
        }
        m_Map.Cell(x, y) = McWater;
    }

    // устанавливаем муравейник
    m_Map.Cell(rand() % m_Map.GetMapSizeX(), rand() % m_Map.GetMapSizeY()) = McHill;

    // ставим ресурс с едой
    m_Map.Cell(rand() % m_Map.GetMapSizeX(), rand() % m_Map.GetMapSizeY()) = McFood;

    int startX = 3;
    int startY = 3;
    int endX = 15;
    int endY = 12;
    bool stop = false;

    m_Map.Cell(startX, startY) = McWay;
    while((startX != endX || startY != endY) && stop == false)
    {
        switch(FindPath(m_Map, startX, startY, endX, endY))
        {
        case MdRight:
            startX += 1;
            break;
        case MdLeft:
            startX -= 1;
            break;
        case MdUp:
            startY -= 1;
            break;
        case MdDown:
            startY += 1;
            break;
        default:
            std::cout << "Невозможно пройти\n" << std::endl;
            stop = true;
            break;
        }
        m_Map.Cell(startX, startY) = McWay;
    }

    // печатаем карту

    for (int rowNumber = 0; rowNumber < m_Map.GetMapSizeY(); ++rowNumber)
    {
        for (int colNumber = 0; colNumber < m_Map.GetMapSizeX(); ++colNumber)
        {
            std::cout << (char)m_Map.Cell(colNumber, rowNumber);
        }
        std::cout << std::endl;
    }

    return;

#endif // DEBUG ***тестируем алгоритм поиска пути**


    QTcpSocket *socket = m_Map.GetAnt(0).GetAntSocket();



    std::cout << "Пытаемся подключиться к серверу " << ip.toStdString()
              << "..." << std::endl << std::flush;

    for(;;)
    {
        socket->connectToHost(ip, port);
        if(socket->waitForConnected())
        {
            if (socket->state() == QAbstractSocket::ConnectedState)
            {
                std::cout << "Соединение установлено!" << std::endl << std::flush;
                break;
            }
        }
        else
            sleep(5);
        qDebug() << "SOCKET ERROR: " << socket->errorString();
    }
}
void CAntLoop::SetGoalToNearestMapCell(const MapCell mc, CAnt &ant)
{
    int minDistance = m_Map.GetMapSizeY() + m_Map.GetMapSizeX() + 1;// начальное минимальное расстояние должно быть равно максимальному расстоянию между точками нашей карты
    int distance;
    for (int y = 0; y <= m_Map.GetMapSizeY(); y++)
    {
        for (int x = 0; x <= m_Map.GetMapSizeX(); x++)
        {
            // Ищем, например, палочки
            if (m_Map.Cell(x, y) == mc)
            {
                distance =  abs(ant.GetAntPosX() - x) + abs(ant.GetAntPosY() - y);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    ant.SetAntGoalX(x);
                    ant.SetAntGoalY(y);
                }
            }
        }
    }
    //std::cout<< "target1 " << ant.GetAntGoalX() << "  " << ant.GetAntGoalY() << std::endl;
}
void CAntLoop::AntLoop()
{

    CAnt &myAnt = m_Map.GetAnt(0); // ссылка для сокращения последующего кода

    QTcpSocket *socket = myAnt.GetAntSocket();

    // посылаем первый командный пакет c именем и профессией муравья на сервер

    CCommandWriter *firstCommandWriter = new CCommandWriter(socket);

    if(!firstCommandWriter->SendFirstCommand(myAnt))
    {
        qDebug() << "SOCKET ERROR: " << socket->errorString();
        return;
    }

    delete firstCommandWriter;

    // основной цикл: прием пакета состояния от сервера, расчет команды перемещения, отправка команды серверу

    for(;;)
    {

        CStateParser stParser;

        if(!ReadBlockFromStream(socket, &stParser))
        {
            //тут обрабатываем ошибки

            if (stParser.IsError())
            {
                std::cerr << "Ошибка в StateParser: " << stParser.GetErrorMessage() <<  std::endl << std::flush;
            }
            else
            {
                qDebug() << "SOCKET ERROR: " << socket->errorString();
            }

            return;
        }

        // обновляем состояние муравья
        ApplyState(myAnt, stParser.GetState());

        //выдаем на печать
        ShowState(myAnt);

        //Проверяем не окончилась ли игра
        if(myAnt.AntIsWinner() || myAnt.AntIsBanned())
        {
            return;
        }

        // рассчитываем следующий шаг
        UpdateAnt(myAnt);

        // отправляем команду на сервер

        // отправляем команду
        CCommandWriter commandWriter(socket);

        if(!commandWriter.SendCommand(myAnt, m_Board))
        {
            qDebug() << "SOCKET ERROR: " << socket->errorString();
            return;
        }

        // std::cout << "Следующий ход муравья: " << MoveDirectionToString(myAnt.GetAntMoveCommand())
        //  << std::endl << std::flush;
    }
}
void CAntLoop::UpdateAnt(CAnt &ant)
{

    // ************!!!! ЗДЕСЬ ДОЛЖЕН РАСПОЛАГАТЬСЯ ИИ МУРАВЬЯ !!!!!**************

    // главная стратегическая задача  - поиск следующей цели

    // если цель достигнута или ее невозможно найти, ищем следующую цель



   if(((ant.GetAntPosX() == ant.GetAntGoalX()) && (ant.GetAntPosY() == ant.GetAntGoalY()))) //|| !ant.GetGoalReachable())
    {
//        // для поиска цели нам могут помочь:
        // 1) координаты предыдущей цели
        // ant.GetAntLastGoalX(), ant.GetAntLastGoalY()

        // 2) сообщения доски объявлений
        // например, читаем сообщения о расположении еды
        // std::vector<int> foodMessage = m_Board.GetMessage(BkFood);

        //3) символы, которые видит муравей на статической и динамической картах.
        // Эти символы можно получить из объектов m_Map и m_DynMap.
        // если нужны только видимые на данном шаге символы, их можно получить из полей обзора муравья:
        //std::string staticView = ant.GetVisibleCells();
        //std::string dynamicView = ant.GetVisibleDynCells();

        // для тестов устанавливаем случайную цель

//                ant.SetAntGoalX(rand() % (m_Map.GetMapSizeX() - 2) + 1);
//                ant.SetAntGoalY(rand() % (m_Map.GetMapSizeY() - 2) + 1);


        int HillX, HillY, FoodX, FoodY, x, y, direction;
        m_startConvoy = false;
        for (y = 0; y <= m_Map.GetMapSizeY(); y++)
        {
            for (x = 0; x <= m_Map.GetMapSizeX(); x++)
            {
                if (m_Map.Cell(x,y) == McHill)
                {
                    HillX = x;
                    HillY = y;
                }
                if (m_Map.Cell(x,y) == McFood)
                {
                    FoodX = x;
                    FoodY = y;
                    m_startConvoy = true;
                }
            }
        }



        if (m_startConvoy)
        {
            if ((ant.GetAntPosX() == HillX) && (ant.GetAntPosY() == HillY))
            {
                direction = 0;
            }
            else if ((ant.GetAntPosX() == FoodX) && (ant.GetAntPosY() == FoodY))
            {
                direction = 1;
            }

            if(direction == 0)
            {
                ant.SetAntGoalX(FoodX);
                ant.SetAntGoalY(FoodY);
            }
            else if(direction == 1)
            {
                ant.SetAntGoalX(HillX);
                ant.SetAntGoalY(HillY);
            }


       }



#if 0
        else if(m_Map.Cell(ant.GetAntPosX(), ant.GetAntPosY()) == McStock)
        {
            bool messageFind = false;
            size_t numberOfMessage;

            if(!m_Board.GetMessage(BkQueenCommand).empty())
            {
                std::vector<int> StickMessageQueen = m_Board.GetMessage(BkQueenCommand);

                for(numberOfMessage = 0; numberOfMessage < m_Board.GetMessage(BkQueenCommand).size();numberOfMessage += 3)
                {
                    if(StickMessageQueen[numberOfMessage] == 9)//если сообщение преднозначеено захвозу то
                    {
                        messageFind = true;
                        break;
                    }
                }
            }

            if (messageFind)
            {
                std::vector<int> StickMessageQueen;
                StickMessageQueen = m_Board.GetMessage(BkQueenCommand);

                if (StickMessageQueen[numberOfMessage + 1] == 1) //нести еду из склада
                {
                    for (int y = 0; y <= m_Map.GetMapSizeY(); y++)
                    {
                        for (int x = 0; x <= m_Map.GetMapSizeX(); x++)
                        {
                            if (m_Map.Cell(x, y) == McHill)
                            {
                                ant.SetAntGoalX(x);
                                ant.SetAntGoalY(y);
                            }
                        }
                    }
                }

                if (StickMessageQueen[numberOfMessage + 1] == 2)//нести палку со склада
                {
                    for (int y = 0; y <= m_Map.GetMapSizeY(); y++)
                    {
                        for (int x = 0; x <= m_Map.GetMapSizeX(); x++)
                        {
                            if (m_Map.Cell(x, y) == McHill)
                            {
                                ant.SetAntGoalX(x);
                                ant.SetAntGoalY(y);
                            }
                        }
                    }
                }

                if (StickMessageQueen[numberOfMessage + 2] == 1) //нести еду из муравейника
                {
                    m_GoFromHillTakeFood = true;
                    for (int y = 0; y <= m_Map.GetMapSizeY(); y++)
                    {
                        for (int x = 0; x <= m_Map.GetMapSizeX(); x++)
                        {
                            if (m_Map.Cell(x, y) == McHill)
                            {
                                ant.SetAntGoalX(x);
                                ant.SetAntGoalY(y);

                            }
                        }

                    }
                }

                if (StickMessageQueen[numberOfMessage + 2] == 2)//нести палку из муравейника
                {
                    m_GoFromHillTakeStick = true;
                    for (int y = 0; y <= m_Map.GetMapSizeY(); y++)
                    {
                        for (int x = 0; x <= m_Map.GetMapSizeX(); x++)
                        {
                            if (m_Map.Cell(x, y) == McHill)
                            {
                                ant.SetAntGoalX(x);
                                ant.SetAntGoalY(y);

                            }
                        }
                    }

                }

            }

            if (m_GoStock)
            {
                for (int y = 0; y <= m_Map.GetMapSizeY(); y++)
                {
                    for (int x = 0; x <= m_Map.GetMapSizeX(); x++)
                    {
                        if (m_Map.Cell(x, y) == McHill)
                        {
                            ant.SetAntGoalX(x);
                            ant.SetAntGoalY(y);
                        }
                    }

                }
                m_GoStock = false;
            }


            if(!messageFind)//отвечает за что делать когда нет сообщения. Просто сидим на складе.
            {
                std::vector<int> stickMessageGo;
                std::vector<int> foodMessageGo;
                stickMessageGo = m_Board.GetMessage(BkStick);
                foodMessageGo = m_Board.GetMessage(BkFood);
                if (m_Swap)
                {
                    m_Swap = false;
                    ant.SetAntGoalX(stickMessageGo[0]);
                    ant.SetAntGoalY(stickMessageGo[1]);
                }
                else
                {
                    m_Swap = true;
                    ant.SetAntGoalX(foodMessageGo[0]);
                    ant.SetAntGoalY(foodMessageGo[1]);
                }
            }


        }
        else if(m_Map.Cell(ant.GetAntPosX(), ant.GetAntPosY()) == McHill)
        {
            //по приходу в муравейник идем домой.
            for (int y = 0; y <= m_Map.GetMapSizeY(); y++)
            {
                for (int x = 0; x <= m_Map.GetMapSizeX(); x++)
                {
                    if (m_Map.Cell(x, y) == McStock)
                    {
                        ant.SetAntGoalX(x);
                        ant.SetAntGoalY(y);
                    }
                }
            }
            if(m_GoFromHillTakeFood)//пока не требуеттся т.к сервер сам выдает что нужно.
            {
            }
            if(m_GoFromHillTakeStick)
            {
            }
        }


        else
        {
            bool messageFind = false;
            size_t numberOfMessage;

            if(!m_Board.GetMessage(BkQueenCommand).empty())
            {
                std::vector<int> StickMessageQueen;
                StickMessageQueen = m_Board.GetMessage(BkQueenCommand);

                for(numberOfMessage = 0; numberOfMessage < m_Board.GetMessage(BkQueenCommand).size();numberOfMessage += 3)
                {
                    if(StickMessageQueen[numberOfMessage] == 9)//если сообщение преднозначеено захвозу то
                    {
                        messageFind = true;
                        break;
                    }
                }
                if(m_Map.Cell(ant.GetAntPosX(), ant.GetAntPosY()) != McStock)
                {
                    m_GoStock = true;
                }
            }

        }
   #endif
        // обновляем значения координат предыдущей цели
        ant.SetAntLastGoalX(ant.GetAntGoalX());
        ant.SetAntLastGoalY(ant.GetAntGoalY());
        // m_RandGoal = false;
    }

    // тактическая задача - поиск пути к цели
    MoveDirection m = FindPath(m_Map, ant.GetAntPosX(), ant.GetAntPosY(), ant.GetAntGoalX(), ant.GetAntGoalY());
    //  std::cout<< "target3" << ant.GetAntGoalX() << "  " << ant.GetAntGoalY() << std::endl;
    // если цель недостижима устанавливаем соответствующий флаг
    if (m == MdStop)
    {
        ant.SetAntGoalX(rand() % (m_Map.GetMapSizeX() - 2) + 1);
        ant.SetAntGoalY(rand() % (m_Map.GetMapSizeY() - 2) + 1);
        //m_RandGoal = true;
        // ant.SetGoalReachable(false);

    }

    ant.SetAntMoveCommand(m);
    m_Board.DeleteAllMessages();

    // и добавляем свои сообщения, если они есть:
    std::vector<int> stickMessage;

    for (int y = 0; y <= m_Map.GetMapSizeY(); y++)
    {
        for (int x = 0; x <= m_Map.GetMapSizeX(); x++)
        {
            // Ищем, например, палочки
            if (m_Map.Cell(x, y) == McStick)
            {
                stickMessage.push_back(x);
                stickMessage.push_back(y);
            }
        }
    }

    m_Board.AddMessage(stickMessage, BkStick);

    // логика сбора палочек и еды На самом деле этот код можно убрать,
    // потому что сбор палочек и еды учитывает сервер.
    // Здесь он используется только для вывода информации на экран

    switch (m_Map.Cell(ant.GetAntPosX(), ant.GetAntPosY()))
    {
    case McFood:
        if(ant.GetAntLoad() == AlEmpty)
        {
            ant.SetAntLoad(AlFood);
        }
        break;
    case McStick:
        if(ant.GetAntLoad() == AlEmpty)
        {
            ant.SetAntLoad(AlStick);
        }
        break;
    case McHill:
    {
        switch(ant.GetAntLoad())
        {
        case AlFood:
            ant.SetFoodResult(ant.GetFoodResult() + 1);
            ant.SetAntLoad(AlEmpty);
            break;
        case AlStick:
            ant.SetStickResult(ant.GetStickResult() + 1);
            ant.SetAntLoad(AlEmpty);
            break;
        case AlError:
        case AlEmpty:
        case AlWater:
        case AlChild:
        case AlCount:
            break;
        }
    }
    case McWay:
    case McGround:
    case McStock:
    case McUnknown:
        break;
    case McWater:
    case McWall:
    case McError:
        break;
    }
}

void CAntLoop::ApplyState(CAnt &ant, const CState &s)
{
    // устанавливаем размер карты
    m_Map.SetMapSizeX(s.GetMapSize());
    m_Map.SetMapSizeY(s.GetMapSize());
    m_DynMap.SetMapSizeX(s.GetMapSize());
    m_DynMap.SetMapSizeY(s.GetMapSize());

    // устанавливаем координаты муравья и его статус

    ant.SetAntPosX(s.GetPosX());
    ant.SetAntPosY(s.GetPosY());
    ant.SetAntStatus(s.GetAntStatus());
    ant.SetAntViewRadius(s.GetViewRadius());

    ant.SetVisibleCells(s.GetVisibleMap());
    ant.SetVisibleDynCells(s.GetVisibleDynMap());

    // копируем кусок статической и динамической карт
    m_DynMap.Clear();

    int x = ant.GetAntPosX();
    int y = ant.GetAntPosY();
    int r = ant.GetAntViewRadius();

    int index = 0;
    for (int row = y - r; row <= y + r; row++)
    {
        for (int col = x - r; col <= x + r; col++)
        {
            m_Map.Cell(col, row) = (MapCell)s.GetVisibleMap()[index];
            // m_DynMap.Cell(col, row) = CharToAntType(s.GetVisibleDynMap()[index]);
            index++;
        }
    }

    size_t maxAntsInCell = s.GetVisibleDynMap().size() / ((2 * r + 1) * (2 * r + 1));


    index = 0;
    for (size_t depth = 0; depth < maxAntsInCell; ++depth)
    {
        for (int row = y - r; row <= y + r; row++)
        {
            for (int col = x - r; col <= x + r; col++)
            {
                if (CharToAntType(s.GetVisibleDynMap()[index]) != AtUnknown)
                {
                    m_DynMap.Cell3D(col, row).push_back(CharToAntType(s.GetVisibleDynMap()[index]));
                }

                ++index;
            }
        }
    }


    for(int keyNumber = 0; keyNumber < BkCount; ++keyNumber)
    {

        BoardKey bk = (BoardKey)keyNumber;
        switch(bk)
        {
        case BkQueenCommand:
        case BkLion:
        case BkTrap:
        case BkStick:
        case BkFood:
        case BkIll:
            m_Board.ReplaceMessage(s.GetStateMessage(bk), bk);
            break;
        case BkLionTrace:
        case BkUnknown:
        case BkCount:
            break;
        }
    }

}

void CAntLoop::ShowState(CAnt &ant)
{
    system("clear");

    // печатаем карту
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

    // печатаем текущие данные

    std::cout << "Муравей " << ant.GetAntName()
              << " по профессии " << AntTypeToString(ant.GetAntType())
              << " пошел " << MoveDirectionToString(ant.GetAntMoveCommand()) << "." << std::endl
              << "И теперь находится в клетке с координатами:  X = "
              << ant.GetAntPosX() << " Y = " << ant.GetAntPosY() << "." << std::endl
              << "Следующая цель муравья: X = " << ant.GetAntGoalX()
              << " Y = " << ant.GetAntGoalY() << "." << std::endl
              << "Состояние муравья: " << AntStatusToString(ant.GetAntStatus()) << std::endl
              << "Несет " << ant.GetAntLoadString() << "!"
              << " Собрал " << ant.GetFoodResult() << " еды и " << ant.GetStickResult() << " веточек!" << std::endl;
    //              std::cout << "Состояние доски объявлений:" << std::endl;
    //              m_Board.PrintBoard();

    std::cout<< std::flush;
}


void CAntLoop::DisconnectMap()
{
    m_Map.GetAnt(0).GetAntSocket()->close();
    delete m_Map.GetAnt(0).GetAntSocket();
    std::cerr << "GAME OVER\n";
}


bool CAntLoop::ReadBlockFromStream(QTcpSocket* socket, CItemParser *itemParser)
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


bool CAntLoop::ReadBlockFromStream(std::istream &s, CItemParser *itemParser)
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
